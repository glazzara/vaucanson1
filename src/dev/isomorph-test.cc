
# include <vaucanson/tools/usual.hh>
# include <check/tests_stuff.hh>
# include <time.h>
# include <map>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/misc/dot_dump.hh>

# include <vaucanson/algorithms/isomorph.hh>

int main(int argc, char **argv)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef GenRandomAutomata<usual_automaton_t>  gen_auto_t;
  typedef usual_automaton_t	                automaton_t;

  //  tests::Tester t(tg.verbose());
  gen_auto_t    gen(42);
  
  const unsigned nb_test    = 20;

  automaton_t a = gen.generate(10, 15);
  automaton_t b = gen.generate(10, 15);

  std::cout << is_isomorph(a,b) << std::endl;
  
  automaton_t c = gen.empty(1);

  hstate_t x = c.add_state();
  hstate_t y = c.add_state();
  hstate_t z = c.add_state();

  if (!c.series().monoid().alphabet().contains('a'))
    c.series().monoid().alphabet().insert('a');
  
  c.set_initial(x);

  c.add_letter_edge(x,y,'a');
  c.add_letter_edge(y,z,'a');

  c.set_final(z);


  automaton_t d = gen.empty(1);

  x = d.add_state();
  z = d.add_state();
  y = d.add_state();

  if (!d.series().monoid().alphabet().contains('a'))
    d.series().monoid().alphabet().insert('a');
  
  d.set_initial(x);

  d.add_letter_edge(x,y,'a');
  d.add_letter_edge(y,z,'a');

  d.set_final(z);

  std::cout << is_isomorph(c,d) << std::endl;

  //  SAVE_AUTOMATON_DOT2(a, "a");

  return 0;
}
