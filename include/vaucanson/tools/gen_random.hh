// gen_random.hh
// 
// $Id$
// VCSN_HEADER

#ifndef GEN_RANDOM_HH
# define GEN_RANDOM_HH

# include <vaucanson/fundamental/fundamental.hh>

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/misc/ref.hh>

namespace vcsn {

  using namespace algebra;

  template <class TAutomata> class GenRandomAutomata
  {
  public:
    typedef typename TAutomata::states_t		  states_t;
    typedef typename TAutomata::state_iterator		  state_iterator;
    typedef typename TAutomata::monoid_t::alphabet_t	  alphabet_t;
    typedef typename alphabet_t::iterator		  alphabet_iterator;
    typedef typename TAutomata::states_t		  states_t;
    typedef typename TAutomata::state_iterator		  state_iterator;
    typedef typename TAutomata::monoid_t::alphabets_elt_t alphabets_elt_t;
    
    GenRandomAutomata();
    GenRandomAutomata(unsigned init);

    TAutomata empty(unsigned nb_letter = 2); 

    TAutomata generate(unsigned nb_state, unsigned nb_edge, 
		       unsigned istate = 1, unsigned fstate = 1,
		       unsigned nb_letter = 2);
    TAutomata generate_dfa(unsigned nb_state, 
			   unsigned size_alphabet = 2, 
			   unsigned fstate = 1);
    TAutomata generate_with_epsilon(unsigned nb_state, unsigned nb_edge, 
				    unsigned nb_epsilon_min, 
				    unsigned nb_epsilon_max);

    TAutomata generate_normalized(unsigned nb_state, unsigned density = 3);

  private:

    unsigned alea(unsigned max);
    unsigned nb_edge_circle(TAutomata work, hstate_t state);
    void     del_edge_circle(TAutomata work, hstate_t state);
   
  };

  namespace tools {

    typedef GenRandomAutomata<usual_automaton_t> gen_auto_t;

  } // tools

} // vcsn

# include <vaucanson/tools/gen_random.hxx>

#endif
