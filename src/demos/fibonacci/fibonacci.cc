#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/boolean_transducer.hh>

#include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
#include <vaucanson/algebra/implementation/series/krat_exp_verbalization.hh>

#include <vaucanson/tools/dot_display.hh>
#include <vaucanson/algorithms/standard_of.hh>
#include <vaucanson/algorithms/evaluation.hh>
#include <vaucanson/algorithms/realtime_composition.hh>

void
eval_an_expression(const vcsn::boolean_transducer::automaton_t& t)
{
  std::string user_string;

  do
    {
      using namespace vcsn;
      using namespace vcsn::boolean_transducer;

      const series_set_t&	series_set = t.structure().series();
      const monoid_t&		monoid     = series_set.monoid();
      const semiring_t&		semiring   = series_set.semiring();
      const alphabet_t&		alphabet   = monoid.alphabet();

      const monoid_t&		o_monoid   = semiring.monoid();
      const output_semiring_t&	o_semiring = semiring.semiring();
      const alphabet_t&		o_alphabet = o_monoid.alphabet();

      std::cout << "Enter your expression over " << alphabet
		<<" (\"next\", otherwise): ";
      std::cin >> user_string;

      output_series_set_t	series (o_semiring, monoid);
      output_series_set_elt_t	exp (series);

      parse(user_string, exp);

      {
	using boolean_automaton::automaton_t;

	using boolean_automaton::aut_to_exp;
	using boolean_automaton::standard_of;
	using boolean_automaton::new_automaton;

	automaton_t	result = new_automaton(o_alphabet);
	evaluation(standard_of(exp), t, result);
	std::cout << verbalize(aut_to_exp(result)) << std::endl;
      }
    }
  while (user_string != "next");
}

int main()
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::boolean_transducer;

  /*-------------------------------.
  | Instanciation of the objects.  |
  `-------------------------------*/

  alphabet_t	A;
  A.insert('a');
  A.insert('b');

  alphabet_t	B;
  B.insert('x');
  B.insert('y');

  alphabet_t	C;
  C.insert('z');
  C.insert('t');

  /*-------------------.
  | Creation of fibg.  |
  `-------------------*/

  automaton_t		fibg = new_automaton(A, B);

  hstate_t p = fibg.add_state();
  hstate_t q = fibg.add_state();
  hstate_t r = fibg.add_state();

  fibg.add_io_edge(p, p, "b", "y");
  fibg.add_io_edge(p, q, "a", "");
  fibg.add_io_edge(q, q, "a", "x");
  fibg.add_io_edge(q, r, "b", "");
  fibg.add_io_edge(r, q, "a", "xy");
  fibg.add_io_edge(r, q, "b", "yx");

  fibg.set_o_final(q, "x");

  fibg.set_o_final(r, "xy");

  fibg.set_final(p);
  fibg.set_initial(p);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_display(fibg, "fibg", true);
  eval_an_expression(fibg);

  /*-------------------.
  | Creation of fibd.  |
  `-------------------*/

  automaton_t fibd = new_automaton(B, C);

  hstate_t s = fibd.add_state();
  hstate_t t = fibd.add_state();
  hstate_t u = fibd.add_state();

  fibd.add_io_edge(s, s, "y", "v");
  fibd.add_io_edge(s, t, "y", "");
  fibd.add_io_edge(t, s, "x", "zz");
  fibd.add_io_edge(t, u, "y", "");
  fibd.add_io_edge(u, t, "x", "zv");
  fibd.add_io_edge(u, u, "x", "z");

  fibd.set_o_initial(s, "vv");

  fibd.set_o_initial(t, "v");

  fibd.set_initial(u);
  fibd.set_final(u);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_display(fibd, "fibd", true);
  eval_an_expression(fibd);

  /*----------.
  | Compose.  |
  `----------*/

  automaton_t	fibgd = new_automaton(A, C);
  realtime_composition(fibg, fibd, fibgd);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_display(fibgd, "fibgd", true);
  eval_an_expression(fibgd);
}
