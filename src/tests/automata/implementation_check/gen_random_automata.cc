// gen_random_automata.cc
// 
// VCSN_HEADER

# include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>


# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>

# include <vaucanson/automata/concept/kinds.hh>

# include <vaucanson/automata/concept/tags.hh>

# include <vaucanson/automata/concrete/manylinks.hh>

# include <check/tests_stuff.hh>
# include <map>

# include <stdlib.h>
# include <math.h>
# include <iostream>
# include <fstream>

# include <vaucanson/misc/ref.hh>
# include <vaucanson/misc/dot_dump.hh>


namespace vcsn 
{

  using namespace algebra;

template <class TAutomata> class GenRandomAutomata
{
public:
  
  GenRandomAutomata() : _nb_state(0), _nb_edge(0) {}
  GenRandomAutomata(unsigned nb_state) 
    : _nb_state(nb_state), _nb_edge(nb_state - 1) {}
  GenRandomAutomata(unsigned nb_state, unsigned nb_edge) 
    : _nb_state(nb_state) 
  {
    if (nb_edge >= nb_state - 1)
      _nb_edge = nb_edge;
    else
      _nb_edge = nb_state - 1;
  }
  

  TAutomata generate()
  {
//     Alphabet a;
//     a.insert('a');
//     a.insert('b');
//     Words w(a);
//     Series<NumericalSemiring, Words> s();

    std::filebuf fb;
    fb.open ("automaton.dot", std::ios::out);
    std::ostream os(&fb);

    TAutomata work;
    work.create();
    //    work.series() = s;

    typedef typename TAutomata::states_t states_t;
    typedef typename TAutomata::state_iterator state_iterator;
    typedef typename TAutomata::monoid_t::alphabets_elt_t alphabets_elt_t;
    
    for (unsigned i = 0; i < _nb_state; i++)
      work.add_state();

    // alphabet construction 
    alphabets_elt_t& alpha = work.series().monoid().alphabet();
    alpha.insert('a');
    alpha.insert('b');

    // minimal construction

    state_iterator prev = work.states().begin();

    std::cout << _nb_state << std::endl;
    std::cout << work.states().size() << std::endl;
    for (state_iterator i = work.states().begin();
	 i != work.states().end(); i++)
      {
	//std::cout << *i << std::endl;
	_nb_edge--;
	work.add_letter_edge(*prev, *i, alpha.select_letter(alea(alpha.size())));
	prev = i;
      }

    misc::dot_dump(os, work, "test");

      return work;
  }
  

private:

  unsigned _nb_state;
  unsigned _nb_edge;

  unsigned alea(unsigned max)
  {
    return ((unsigned) trunc(((float) random() / (float) RAND_MAX) * max));
  }
  
};

}

using namespace vcsn;

typedef Element
<
  Automata, 
  utility::ref< AutomatonImpl<labels_are_series,
		Series<NumericalSemiring, Words>,
		polynom<std::string, int>,
		ManyLinks<polynom<std::string, int>, NoTag, NoTag>,
		NoTag,
		std::map> >
>
usual_automaton_t;

typedef GenRandomAutomata<usual_automaton_t> gen_auto_t;



int main(int argc, char **argv)
{
  gen_auto_t gen(10);
  
  gen.generate();

  return EXIT_SUCCESS;
}
