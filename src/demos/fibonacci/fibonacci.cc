#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/boolean_transducer.hh>

#include <vaucanson/algorithms/evaluation.hh>
#include <vaucanson/algorithms/krat_exp_expand.hh>
#include <vaucanson/algorithms/realtime_composition.hh>

#include <vaucanson/tools/dot_display.hh>

void
eval_an_expression(const vcsn::boolean_transducer::automaton_t& t)
{
  using namespace vcsn::boolean_transducer;

  const alphabet_t&	alphabet = t.structure().series().monoid().alphabet();
  std::string		user_string;

  do
    {
      std::cout << "Enter your expression over " << alphabet
		<<" (\"next\", otherwise): ";
      std::getline(std::cin, user_string);
      if (user_string != "next")
	{
	  using namespace vcsn::boolean_automaton;
	  using namespace vcsn::rat; // For setpm and MODE_STAR.

	  rat_exp_t exp = new_rat_exp(alphabet, user_string);
	  std::cout << setpm (MODE_STAR) << expand(evaluation(t, exp))
		    << std::endl;
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
  C.insert('u');
  C.insert('v');

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
  fibd.add_io_edge(t, s, "x", "uu");
  fibd.add_io_edge(t, u, "y", "");
  fibd.add_io_edge(u, t, "x", "uv");
  fibd.add_io_edge(u, u, "x", "u");

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
