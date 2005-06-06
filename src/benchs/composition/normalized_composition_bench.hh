#include <vaucanson/tools/bencher.hh>

#include <vaucanson/algorithms/normalized_composition.hh>
#include <vaucanson/algorithms/fmp_to_realtime.hh>
#include <vaucanson/algorithms/sub_normalize.hh>
#include <vaucanson/algorithms/realtime_to_fmp.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/fmp_transducer.hh>
#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/boolean_automaton.hh>

using namespace vcsn;
using namespace vcsn::boolean_transducer;

std::string
prefsuf(const std::string& u, const std::string& v)
{
  int	vs = v.size();
  int	s = std::min(u.size(), v.size());

  for (int n = s; n > 0; --n)
    {
      std::string tmp = u.substr(0, n);
      if (tmp == v.substr(vs - n, n))
	return tmp;
    }

  return "";
}

automaton_t
replace_left(const std::string& from,	const std::string& to,
	     const alphabet_t& A,	const alphabet_t& B)
{
  automaton_t	a = new_automaton(A, B);

  int		n = from.size();

  // Create a vector to handle all the states.
  std::vector<hstate_t>	s (n);

  // Create states and set them all final.
  for (int i = 0; i < n; ++i)
    {
      s[i] = a.add_state();
      a.set_o_final(s[i], from.substr(0, i));
    }

  // Set the first state initial.
  a.set_initial(s[0]);

  // Create all the edges of the type (ui | 1).
  for (int i = 0; i < n - 1; ++i)
    {
      const letter_t l[] = {from[i], 0 };
      a.add_io_edge(s[i], s[i + 1], l, "");
    }

  // Create the backward edges.
  for (int i = 0; i < n; ++i)
    for_each_letter(j, A)
      if (*j != from[i])
	{
	  const letter_t	l[] = {*j, 0};

	  const std::string	in = from.substr(0, i) + *j;
	  const std::string	factor = prefsuf(from, in);
	  const int		len = factor.size();

	  a.add_io_edge(s[i], s[len], l,
			in.substr(0, i - len + 1));
	}

  // Last state goes back to state i (length of w) with an edge
  // of the type : (un | y) (to = y.w)
  const letter_t	l[] = {from[n - 1], 0};

  std::string		f = prefsuf(from, to);
  int			f_len = f.size();

  a.add_io_edge(s[n - 1], s[f_len], l, to.substr(0, n - f_len));

  return a;
}

automaton_t
replace_right(const std::string& from,	const std::string& to,
	      const alphabet_t& A,	const alphabet_t& B)
{
  monoid_elt_t from_elt(A, from);
  monoid_elt_t to_elt(B, to);
  from_elt.mirror();
  to_elt.mirror();

  automaton_t left = replace_left(from_elt.value(), to_elt.value(), A, B);
  return transpose(left);
}

void normalized_composition_bench(int n_value)
{
  alphabet_t	A;
  A.insert('a');
  A.insert('b');

  alphabet_t	B;
  B.insert('a');
  B.insert('b');

  alphabet_t	C;
  C.insert('a');
  C.insert('b');

  std::string	from, to;

  from = "a";
  to = "b";

  for (int i = 0; i < n_value; ++i)
  {
    from += "b";
    to += "a";
  }


  VCSN_BENCH_START;
  automaton_t	left_auto = replace_left(from, to, A, B);

  fmp_transducer::automaton_t fmp_left_auto =
    fmp_transducer::new_automaton(A,B);
  fmp_transducer::automaton_t sub_left_auto =
    fmp_transducer::new_automaton(A,B);

  std::cerr << "Left sub-normalisation" << std::endl;
  VCSN_BENCH_START;
  realtime_to_fmp(left_auto, fmp_left_auto);
  sub_normalize(fmp_left_auto, sub_left_auto);
  std::cout << "nb states: " << sub_left_auto.states().size() << std::endl;
  std::cout << "nb edges: " << sub_left_auto.edges().size() << std::endl;
  VCSN_BENCH_STOP_AND_PRINT;

  automaton_t   right_auto = replace_right(from, to, B, C);

  fmp_transducer::automaton_t fmp_right_auto =
    fmp_transducer::new_automaton(B,C);
  fmp_transducer::automaton_t sub_right_auto =
    fmp_transducer::new_automaton(B,C);

  std::cerr << "Right sub-normalisation" << std::endl;
  VCSN_BENCH_START;
  realtime_to_fmp(right_auto, fmp_right_auto);
  sub_normalize(fmp_right_auto, sub_right_auto);
  std::cout << "nb states: " << sub_right_auto.states().size() << std::endl;
  std::cout << "nb edges: " << sub_right_auto.edges().size() << std::endl;
  VCSN_BENCH_STOP_AND_PRINT;

  std::cerr << "Normalized composition" << std::endl;
  VCSN_BENCH_START;

  fmp_transducer::automaton_t res_auto = fmp_transducer::new_automaton(A,C);

  normalized_composition(sub_left_auto, sub_right_auto, res_auto);

  std::cout << "nb states: " << res_auto.states().size() << std::endl;
  std::cout << "nb edges: " << res_auto.edges().size() << std::endl;

  VCSN_BENCH_STOP_AND_PRINT;
  VCSN_BENCH_STOP_AND_PRINT;
}
