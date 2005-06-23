#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/algorithms/realtime_composition.hh>
#include <vaucanson/tools/xml_dump.hh>


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


  /*----------------------.
  | Creation of fibleft.  |
  `----------------------*/

  automaton_t		fibleft = new_automaton(A, A);

  hstate_t p = fibleft.add_state();
  hstate_t q = fibleft.add_state();
  hstate_t r = fibleft.add_state();

  fibleft.add_io_edge(p, p, "b", "b");
  fibleft.add_io_edge(p, q, "a", "");
  fibleft.add_io_edge(q, q, "a", "a");
  fibleft.add_io_edge(q, r, "b", "");
  fibleft.add_io_edge(r, q, "a", "ab");
  fibleft.add_io_edge(r, q, "b", "ba");

  fibleft.set_o_final(q, "a");

  fibleft.set_o_final(r, "ab");

  fibleft.set_final(p);
  fibleft.set_initial(p);

  /*-----------------------.
  | Creation of fibright.  |
  `-----------------------*/

  automaton_t fibright = new_automaton(A, A);

  hstate_t s = fibright.add_state();
  hstate_t t = fibright.add_state();
  hstate_t u = fibright.add_state();

  fibright.add_io_edge(s, s, "b", "b");
  fibright.add_io_edge(s, t, "b", "");
  fibright.add_io_edge(t, s, "a", "aa");
  fibright.add_io_edge(t, u, "b", "");
  fibright.add_io_edge(u, t, "a", "ab");
  fibright.add_io_edge(u, u, "a", "a");

  fibright.set_o_initial(s, "bb");

  fibright.set_o_initial(t, "b");

  fibright.set_initial(u);
  fibright.set_final(u);


  /*----------.
  | Compose.  |
  `----------*/

  automaton_t	fiblr = new_automaton(A, A);
  realtime_composition(fibleft, fibright, fiblr);

  automaton_t	fibrl = new_automaton(A, A);
  realtime_composition(fibright, fibleft, fibrl);

  std::ofstream left_fibo("fibo_left.xml");
  std::ofstream right_fibo("fibo_right.xml");
  std::ofstream left_right_fibo("fibo_left_right.xml");
  std::ofstream right_left_fibo("fibo_right_left.xml");

  tools::xml_dump(left_fibo, fibleft, "left_fibo");
  tools::xml_dump(right_fibo, fibright, "right_fibo");
  tools::xml_dump(left_right_fibo, fiblr, "left_right_fibo");
  tools::xml_dump(right_left_fibo, fibrl, "right_left_fibo");

  std::cout << "Cautious left sequential transducer: fibo_left.xml"
	    << std::endl
	    << "Cautious right sequential transducer: fibo_right.xml"
	    << std::endl
	    << "Left transducer composed by right transducer: "
	    << "fibo_left_right.xml"
	    << std::endl
	    << "Right transducer composed by left transducer: "
	    << "fibo_right_left.xml"
	    << std::endl;
}
