#include <vaucanson/fmp_transducer.hh>
#include <vaucanson/tools/xml_dump.hh>

int main()
{
  using namespace vcsn;
  using namespace vcsn::fmp_transducer;

  first_alphabet_t A;
  A.insert('a');
  A.insert('b');

  automaton_t u1 = new_automaton(A, A);

  hstate_t s = u1.add_state();
  hstate_t t = u1.add_state();
  hstate_t u = u1.add_state();

  u1.set_initial(t);
  u1.set_final(s);
  u1.set_final(t);

  u1.add_weighted_edge(s, t, true, make_couple(A, A, "a", "1").value());
  u1.add_weighted_edge(t, s, true, make_couple(A, A, "1", "b").value());
  u1.add_weighted_edge(t, u, true, make_couple(A, A, "b", "1").value());
  u1.add_weighted_edge(u, t, true, make_couple(A, A, "1", "a").value());

  std::ofstream file("u1.xml");

  tools::xml_dump(file, u1, "u1");

  std::cout << "File u1.xml has been created." << std::endl;
}
