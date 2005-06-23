#include <vaucanson/fmp_transducer.hh>
#include <vaucanson/tools/xml_dump.hh>

int main()
{
  using namespace vcsn;
  using namespace vcsn::fmp_transducer;

  first_alphabet_t A;
  A.insert('a');
  A.insert('b');

  automaton_t t1 = new_automaton(A, A);


  hstate_t p = t1.add_state();
  hstate_t q = t1.add_state();
  hstate_t r = t1.add_state();

  t1.set_initial(q);
  t1.set_final(q);
  t1.set_final(p);

  t1.add_weighted_edge(p, q, true, make_couple(A, A, "1", "b").value());
  t1.add_weighted_edge(q, p, true, make_couple(A, A, "a", "1").value());
  t1.add_weighted_edge(q, r, true, make_couple(A, A, "1", "a").value());
  t1.add_weighted_edge(r, q, true, make_couple(A, A, "b", "1").value());

  std::ofstream file("t1.xml");

  tools::xml_dump(file, t1, "t1");

  std::cout << "File t1.xml has been created." << std::endl;
}
