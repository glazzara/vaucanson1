// gen_random.hh
// 
// VCSN_HEADER

#ifndef GEN_RANDOM_HH
# define GEN_RANDOM_HH

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
    
    GenRandomAutomata();
    GenRandomAutomata(unsigned init);
  

    TAutomata generate(unsigned nb_state, unsigned nb_edge, 
		       unsigned istate = 1, unsigned fstate = 1);

    TAutomata generate_afd(unsigned nb_state, 
			   unsigned size_alphabet = 2, 
			   unsigned fstate = 1);
  private:

    unsigned alea(unsigned max);

    unsigned nb_edge_circle(TAutomata work, hstate_t state);

    void del_edge_circle(TAutomata work, hstate_t state);

  };


  typedef Element
  <
    Automata, 
    utility::ref< 
    AutomatonImpl<labels_are_series,
		  Series<NumericalSemiring, Words>,
		  polynom<std::string, int>,
		  ManyLinks<polynom<std::string, int>, NoTag, NoTag>,
		  NoTag,
		  std::map> >
  >
  usual_automaton_t;

  typedef GenRandomAutomata<usual_automaton_t> gen_auto_t;


} // vcsn

# include <automata/implementation_check/gen_random.hxx>

#endif
