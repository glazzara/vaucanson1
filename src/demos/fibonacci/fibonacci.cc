#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/boolean_transducer.hh>

#include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
#include <vaucanson/algebra/implementation/series/krat_exp_verbalization.hh>

#include <vaucanson/tools/dot_dump.hh>
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

      std::cout << "Enter your expression over {a,b}* (\"next\", otherwise): ";
      std::cin >> user_string;

      monoid_t		m = t.structure().series().monoid();
      output_semiring_t	s = t.structure().series().semiring().semiring();

      output_series_set_t	series (s, m);
      output_series_set_elt_t	exp (series);

      parse(user_string, exp);

      {
	using boolean_automaton::automaton_t;

	using boolean_automaton::aut_to_exp;
	using boolean_automaton::standard_of;
	using boolean_automaton::new_automaton;

	automaton_t	w = standard_of(exp);
	automaton_t	result =
	  new_automaton(t.structure().series().semiring().monoid().alphabet());
	evaluation(w, t, result);
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

  monoid_t		A_star (A);
  monoid_t		B_star (B);
  monoid_t		C_star (C);

  monoid_elt_t		A_empty = identity_as<monoid_elt_value_t>::of(A_star);
  monoid_elt_t		B_empty = identity_as<monoid_elt_value_t>::of(B_star);
  monoid_elt_t		C_empty = identity_as<monoid_elt_value_t>::of(C_star);

  monoid_elt_t a (A_star, "a");
  monoid_elt_t b (A_star, "b");

  monoid_elt_t x (B_star, "x");
  monoid_elt_t y (B_star, "y");

  monoid_elt_t z (C_star, "z");
  monoid_elt_t v (C_star, "v");

  /*-------------------.
  | Creation of fibg.  |
  `-------------------*/

  automaton_t		fibg = new_automaton(A, B);

  hstate_t p = fibg.add_state();
  hstate_t q = fibg.add_state();
  hstate_t r = fibg.add_state();



  fibg.add_io_edge(p, p, b, y);
  fibg.add_io_edge(p, q, a, B_empty);
  fibg.add_io_edge(q, q, a, x);
  fibg.add_io_edge(q, r, b, B_empty);
  fibg.add_io_edge(r, q, a, x * y);
  fibg.add_io_edge(r, q, b, y * x);

  output_series_set_elt_t os_q (fibg.structure().series().semiring());
  os_q.assoc(x, true);
  series_set_elt_t s_q (fibg.structure().series());
  s_q.assoc(A_empty, os_q);
  fibg.set_final(q, s_q);

  output_series_set_elt_t os_r (fibg.structure().series().semiring());
  os_r.assoc(x * y, true);
  series_set_elt_t s_r (fibg.structure().series());
  s_r.assoc(A_empty, os_r);
  fibg.set_final(r, s_r);

  fibg.set_final(p);
  fibg.set_initial(p);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_dump(std::cerr, fibg, "fibg");
  eval_an_expression(fibg);

  /*-------------------.
  | Creation of fibd.  |
  `-------------------*/

  automaton_t fibd = new_automaton(B, C);

  hstate_t s = fibd.add_state();
  hstate_t t = fibd.add_state();
  hstate_t u = fibd.add_state();

  fibd.add_io_edge(s, s, y, v);
  fibd.add_io_edge(s, t, y, C_empty);
  fibd.add_io_edge(t, s, x, z * z);
  fibd.add_io_edge(t, u, y, C_empty);
  fibd.add_io_edge(u, t, x, z * v);
  fibd.add_io_edge(u, u, x, z);

  output_series_set_elt_t os_s (fibd.structure().series().semiring());
  os_s.assoc(v * v, true);
  series_set_elt_t s_s (fibd.structure().series());
  s_s.assoc(B_empty, os_s);
  fibd.set_initial(s, s_s);

  output_series_set_elt_t os_t (fibd.structure().series().semiring());
  os_t.assoc(v, true);
  series_set_elt_t s_t(fibd.structure().series());
  s_t.assoc(B_empty, os_t);
  fibd.set_initial(t, s_t);

  fibd.set_initial(u);
  fibd.set_final(u);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_dump(std::cerr, fibd, "fibd");
  eval_an_expression(fibd);

  /*----------.
  | Compose.  |
  `----------*/

  automaton_t	fibgd = new_automaton(A, C);
  realtime_composition(fibg, fibd, fibgd);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_dump(std::cerr, fibgd, "fibgd");
  eval_an_expression(fibgd);
}
