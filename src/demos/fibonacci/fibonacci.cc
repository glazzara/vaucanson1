#include <vaucanson/tools/usual.hh>
#include <vaucanson/automata/concept/transducer.hh>
#include <vaucanson/tools/dot_dump.hh>
#include <vaucanson/algorithms/standard_of.hh>
#include <vaucanson/algorithms/evaluation.hh>
#include <vaucanson/algorithms/aut_to_exp.hh>
#include <vaucanson/algorithms/krat_exp_print.hh>
#include <vaucanson/algorithms/realtime_composition.hh>
#include <vaucanson/automata/implementation/generalized.hh>
#include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
#include <vaucanson/algebra/implementation/series/krat_exp_verbalization.hh>
#include <vaucanson/algebra/implementation/series/krat.hh>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::algebra::char_letter;
using namespace vcsn::tools;

//
// Type definitions header
//
typedef Series<NumericalSemiring, Words> output_series_pt;
typedef Element<output_series_pt, rat::exp<WordValue, bool> > exp_t;
typedef Series<output_series_pt, Words>  tr_bhv_pt;
typedef rat::exp<WordValue, bool> output_series_value_t;
typedef Element<output_series_pt, output_series_value_t> output_series_elt_t;
typedef polynom<WordValue, output_series_value_t> tr_bhv_value_t;

typedef Graph
<
  labels_are_series,
  WordValue,
  output_series_value_t,
  tr_bhv_value_t,
  char,
  NoTag>
transducer_impl_t;

typedef Transducer<tr_bhv_pt> tr_pt;

typedef Element<tr_pt, transducer_impl_t>
transducer_pt;

AUTOMATON_TYPES_EXACT(transducer_pt);


void eval_an_expression(const transducer_pt& t)
{
  exp_t e(t.structure().series().semiring());
  std::string user_string;

  do {
    std::cout << "Enter your expression over {a,b}* (\"next\", otherwise): ";
    std::cin >> user_string;
    parse(user_string, e);
    usual_automaton_t w = new_automaton(t.series().monoid().alphabet());
    generalized_traits<usual_automaton_t>::automaton_t result(w.structure());
    standard_of(w, e.value());
    evaluation(w, t, result);
    krat_exp_print(verbalize(aut_to_exp(generalized(result))).value());
  } while (user_string != "next");
}

int main()
{
  //
  // Instanciation of the objects.
  //
  alphabet_t A, B;
  A.insert('a');
  A.insert('b');
  A.insert('c');
  B.insert('x');
  B.insert('y');
  B.insert('z');
  monoid_t A_star (A), B_star (B);

  NumericalSemiring Boole;
  typedef Element<NumericalSemiring, bool> mult_t;

  output_series_pt OSA(Boole, A_star);
  tr_bhv_pt OSA_A_star(OSA, A_star);
  tr_pt A_A_transducer(OSA_A_star);
  transducer_pt fibg(A_A_transducer);

  hstate_t p = fibg.add_state();
  hstate_t q = fibg.add_state();
  hstate_t r = fibg.add_state();

  monoid_elt_t empty = identity_as<monoid_elt_value_t>::of(A_star);
  monoid_elt_t a_l(A_star, "a");
  monoid_elt_t b_l(A_star, "b");

  fibg.add_io_edge(p, p, b_l, b_l);
  fibg.add_io_edge(p, q, a_l, empty);
  fibg.add_io_edge(q, q, a_l, a_l);
  fibg.add_io_edge(q, r, b_l, empty);
  fibg.add_io_edge(r, q, a_l, a_l * b_l);
  fibg.add_io_edge(r, q, b_l, b_l * a_l);

  output_series_elt_t os_q(OSA);
  os_q.assoc(a_l, true);
  series_elt_t s_q(OSA_A_star);
  s_q.assoc(empty, os_q);

  fibg.set_final(q, s_q);

  output_series_elt_t os_r(OSA);
  os_r.assoc(a_l * b_l, true);
  series_elt_t s_r(OSA_A_star);
  s_r.assoc(empty, os_r);
  fibg.set_final(r, s_r);

  fibg.set_final(p);
  fibg.set_initial(p);

  eval_an_expression(fibg);
  tools::dot_dump(std::cerr, fibg, "transducer");

  transducer_pt fibd(A_A_transducer);

  hstate_t s = fibd.add_state();
  hstate_t t = fibd.add_state();
  hstate_t u = fibd.add_state();

  fibd.add_io_edge(s, s, b_l, b_l);
  fibd.add_io_edge(s, t, b_l, empty);
  fibd.add_io_edge(t, s, a_l, a_l * a_l);
  fibd.add_io_edge(t, u, b_l, empty);
  fibd.add_io_edge(u, t, a_l, a_l * b_l);
  fibd.add_io_edge(u, u, a_l, a_l);

  output_series_elt_t os_s(OSA);
  os_s.assoc(b_l * b_l, true);
  series_elt_t s_s(OSA_A_star);
  s_s.assoc(empty, os_s);
  fibd.set_initial(s, s_s);

  output_series_elt_t os_t(OSA);
  os_t.assoc(b_l, true);
  series_elt_t s_t(OSA_A_star);
  s_t.assoc(empty, os_t);
  fibd.set_initial(t, s_t);
  fibd.set_initial(u);
  fibd.set_final(u);
  tools::dot_dump(std::cerr, fibd, "fibd");
  eval_an_expression(fibd);

  transducer_pt fibgd(A_A_transducer);
  realtime_composition(fibg, fibd, fibgd);
  tools::dot_dump(std::cerr, fibgd, "fibgd");
  eval_an_expression(fibgd);
}
