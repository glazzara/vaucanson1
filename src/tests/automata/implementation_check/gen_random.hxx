// gen_random.hxx
// 
// VCSN_HEADER

#ifndef GEN_RANDOM_HXX
# define GEN_RANDOM_HXX

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


  template <class TAutomata>
  GenRandomAutomata<TAutomata>::GenRandomAutomata() {}

  template <class TAutomata>
  GenRandomAutomata<TAutomata>::GenRandomAutomata(unsigned init) 
  { srandom(init); }
  
  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate(unsigned nb_state, unsigned nb_edge, 
	   unsigned istate = 1, unsigned fstate = 1)
  {
    // check coherence of automaton
    if (nb_edge < nb_state - 1)
      nb_edge = nb_state - 1;
    if (fstate > nb_state) fstate = nb_state;
    if (fstate <= 0) fstate = 1;
    if (istate > nb_state) istate = nb_state;
    if (istate <= 0) istate = 1;
    
    // file for output format (graphwiz)
    std::filebuf fb;
    fb.open ("automaton.dot", std::ios::out);
    std::ostream os(&fb);

    TAutomata work;
    work.create();

    typedef typename TAutomata::states_t states_t;
    typedef typename TAutomata::state_iterator state_iterator;
    typedef typename TAutomata::monoid_t::alphabets_elt_t alphabets_elt_t;
    
    for (unsigned i = 0; i < nb_state; i++)
      work.add_state();

    // alphabet construction 
    alphabets_elt_t& alpha = work.series().monoid().alphabet();
    alpha.insert('a');
    alpha.insert('b');

    // minimal construction
    state_iterator prev = work.states().begin();

    //    std::cout << nb_state << std::endl;
    //    std::cout << work.states().size() << std::endl;
    for (state_iterator i = ++work.states().begin();
	 i != work.states().end(); i++)
      {
	nb_edge--;
	work.add_letter_edge(*i, *prev, alpha.choose());
	prev = i;
      }

    for (unsigned i = 0; i < nb_edge; i++)
      work.add_letter_edge(work.select_state(alea(work.states().size())), 
			   work.select_state(alea(work.states().size())), 
			   alpha.choose());

    // set initial states
    for (unsigned i = 0; i < istate; i++)
      {
	hstate_t tmp = work.select_state(alea(work.states().size()));
	while (work.is_initial(tmp))
	  tmp = work.select_state(alea(work.states().size()));
	work.set_initial(tmp);
      }

    // set final states
    for (unsigned i = 0; i < fstate; i++)
      {
	hstate_t tmp = work.select_state(alea(work.states().size()));
	while (work.is_final(tmp))
	  tmp = work.select_state(alea(work.states().size()));
	work.set_final(tmp);
      }

    // generation of output file
    // misc::dot_dump(os, work, "test");
    
    return work;
  }
  
  template <class TAutomata>
  unsigned GenRandomAutomata<TAutomata>::
  nb_edge_circle(TAutomata work, hstate_t state)
  {    
    typedef typename TAutomata::edges_t edges_t;
    typedef typename TAutomata::edge_iterator edge_iterator;
    unsigned res = 0;
    
    for (edge_iterator i = work.edges().begin(); i != work.edges().end(); i++)
      if ((work.origin_of(*i) == state) && (work.aim_of(*i) == state))
	res++;

    return res;
  }
  
  template <class TAutomata>
  void GenRandomAutomata<TAutomata>::
  del_edge_circle(TAutomata work, hstate_t state)
  {    
    typedef typename TAutomata::edges_t edges_t;
    typedef typename TAutomata::edge_iterator edge_iterator;
    
    for (edge_iterator i = work.edges().begin(); i != work.edges().end(); i++)
      if ((work.origin_of(*i) == state) && (work.aim_of(*i) == state))
	work.del_edge(*i);
  }
  
  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate_afd(unsigned nb_state, 
	       unsigned size_alphabet, 
	       unsigned fstate = 1)
  {
    // check for coherence 
    if (size_alphabet > 26) size_alphabet = 26;
    if (nb_state < 1) size_alphabet = 1;
    

    // file for output format (graphwiz)
    std::filebuf fb;
    fb.open ("automaton.dot", std::ios::out);
    std::ostream os(&fb);

    TAutomata work;
    work.create();

    typedef typename TAutomata::states_t states_t;
    typedef typename TAutomata::state_iterator state_iterator;
    typedef typename TAutomata::monoid_t::alphabet_t alphabet_t;
    typedef typename alphabet_t::iterator alphabet_iterator;


    for (unsigned i = 0; i < nb_state; i++)
      work.add_state();

    // alphabet construction 
    alphabet_t& alpha = work.series().monoid().alphabet();

    for (unsigned i = 0; i < size_alphabet; i++)
      alpha.insert('a' + i);
     
    
    for (state_iterator i = work.states().begin();
	 i != work.states().end(); i++)
      {
	for (alphabet_iterator j = alpha.begin(); j != alpha.end(); j++)
	  work.add_letter_edge(*i, 
			       work.select_state(alea(work.states().size())), 
			       *j);
	while (nb_edge_circle(work, *i) == alpha.size())
	  {
	    del_edge_circle(work, *i);
	    for (alphabet_iterator j = alpha.begin(); j != alpha.end(); j++)
	      work.add_letter_edge(*i, 
				   work.select_state(alea(work.states().size())), 
				   *j);
	  }
      }

    // set initial states
    work.set_initial(work.select_state(alea(work.states().size())));
    
    // set final states
    for (unsigned i = 0; i < fstate; i++)
      {
	hstate_t tmp = work.select_state(alea(work.states().size()));
	while (work.is_final(tmp))
	  tmp = work.select_state(alea(work.states().size()));
	work.set_final(tmp);
      }

    // generation of output file
    misc::dot_dump(os, work, "test");
    
    return work;
  }


  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate_normalized(unsigned nb_state, unsigned density)
  {
    typedef typename TAutomata::state_iterator state_iterator;
    typedef typename TAutomata::monoid_t::alphabets_elt_t alphabets_elt_t;

    if (density == 0) density = 1;

    TAutomata work = generate(nb_state, nb_state + alea(nb_state * density));
    
    // file for output format (graphwiz)
    std::filebuf fb;
    fb.open ("automaton.dot", std::ios::out);
    std::ostream os(&fb);

    for (state_iterator i = work.states().begin(); i != work.states().end(); i++)
      {
	if (work.is_initial(*i)) work.unset_initial(*i);
	if (work.is_final(*i)) work.unset_final(*i);
      }
    hstate_t init = work.add_state();
    hstate_t final = work.add_state();

    work.set_initial(init);
    work.set_final(final);

    alphabets_elt_t& alpha = work.series().monoid().alphabet();

    hstate_t tmp;

    for (unsigned i = 0; i < density; i++)
      if ((tmp = work.select_state(alea(work.states().size()))) != init)
	work.add_letter_edge(init, tmp, 
			     alpha.choose());
    
    for (unsigned i =0; i < density; i++)
      if ((tmp = work.select_state(alea(work.states().size()))) != final)
	work.add_letter_edge(tmp, final,
			     alpha.choose());
    
    misc::dot_dump(os, work, "test");
    
    return work;
  }


  template <class TAutomata>
  unsigned GenRandomAutomata<TAutomata>::alea(unsigned max)
  {
    return ((unsigned) trunc(((float) random() / (float) RAND_MAX) * max));
  }


} // vcsn


#endif
