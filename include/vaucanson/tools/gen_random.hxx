// gen_random.hxx
// 
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#ifndef GEN_RANDOM_HXX
# define GEN_RANDOM_HXX

# include <vaucanson/config/system.hh>
# include <vaucanson/tools/gen_random.hh>
# include <map>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <vaucanson/tools/usual.hh>

namespace vcsn {

  using namespace algebra;

  template <class TAutomata>
  GenRandomAutomata<TAutomata>::GenRandomAutomata() 
  {}

  template <class TAutomata>
  GenRandomAutomata<TAutomata>::GenRandomAutomata(unsigned init) 
  { 
    srand(init); 
  }
  
  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  empty(unsigned nb_letter) 
  {
    AUTOMATON_TYPES(TAutomata);
    TAutomata work;
    work.create();

    // alphabet construction 
    alphabets_elt_t alpha;
    
    unsigned nb = alea(nb_letter);
    for (unsigned i = 0; i < 2 + nb; ++i)
      {
	letter_t l = alpha.random_letter();
	alpha.insert(alpha.random_letter());
      }
    monoid_t monoid(alpha);
    weights_t semi;
    series_t series(semi, monoid);
    
    work.series() = series;
    return work;
  }

  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate(unsigned nb_state, unsigned nb_edge, 
	   unsigned istate, unsigned fstate,
	   unsigned nb_letter)
  {
    AUTOMATON_TYPES(TAutomata);
    // check consistency of automaton
    if (nb_edge < nb_state - 1)
      nb_edge = nb_state - 1;
    if (fstate > nb_state) fstate = nb_state;
    if (fstate <= 0) fstate = 1;
    if (istate > nb_state) istate = nb_state;
    if (istate <= 0) istate = 1;
    
    TAutomata work;
    work.create();

    // alphabet construction 
    alphabets_elt_t alpha;
        
    unsigned nb = alea(nb_letter);
    for (unsigned i = 0; i < 2 + nb; ++i)
      {
	letter_t l = alpha.random_letter();
	alpha.insert(l);
      }
    monoid_t monoid(alpha);
    weights_t semi;
    series_t series(semi, monoid);
    
    work.series() = series;

    for (unsigned i = 0; i < nb_state; i++)
      work.add_state();

    // minimal construction
    state_iterator prev = work.states().begin();

    for (state_iterator i = ++work.states().begin();
	 i != work.states().end(); i++)
      {
	nb_edge--;
	work.add_letter_edge(*prev, *i, alpha.choose());
	prev = i;
      }

    for (unsigned i = 0; i < nb_edge; i++)
      {
	unsigned from = alea(work.states().size());
	unsigned to = alea(work.states().size());
	work.add_letter_edge(work.choose_state(),
			     work.choose_state(), 
			     alpha.choose());
      }
	
    work.set_initial(*work.states().begin());
    // set initial states
    for (unsigned i = 1; i < istate; i++)
      {
	hstate_t tmp = work.choose_state();
	while (work.is_initial(tmp))
	  tmp = work.choose_state();
	work.set_initial(tmp);
      }

    work.set_final(*--work.states().end());
    // set final states
    for (unsigned i = 1; i < fstate; i++)
      {
	hstate_t tmp = work.choose_state();
	while (work.is_final(tmp))
	  tmp = work.choose_state();
	work.set_final(tmp);
      }

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
  generate_with_epsilon(unsigned nb_state, 
			unsigned nb_edge,
			unsigned nb_epsilon_min,
			unsigned nb_epsilon_max)
  {
    TAutomata a = this->generate(nb_state, nb_edge);
    unsigned nb_eps = nb_epsilon_min + alea(nb_epsilon_max - nb_epsilon_min);
    
    for (unsigned i = 0; i < nb_eps; ++i)
      {
	hstate_t f = a.choose_state();
	hstate_t t = a.choose_state();
	a.add_spontaneous(f, t);
      }
    return a;
  }
  
  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate_dfa(unsigned nb_state, 
	       unsigned size_alphabet, 
	       unsigned fstate)
  {
    // check for coherence 
    if (size_alphabet > 26) size_alphabet = 26;
    if (nb_state < 1) size_alphabet = 1;
    

    // file for output format (graphviz)
    TAutomata work;
    work.create();

    for (unsigned i = 0; i < nb_state; i++)
      work.add_state();

    // alphabet construction 
    alphabet_t& alpha = work.series().monoid().alphabet();

    for (unsigned i = 0; i < size_alphabet; i++)
      alpha.insert(alpha.random_letter());
    
    for (state_iterator i = work.states().begin();
	 i != work.states().end(); i++)
      {
	for (alphabet_iterator j = alpha.begin(); j != alpha.end(); j++)
	  work.add_letter_edge(*i, 
			       work.choose_state(),
			       *j);
	while (nb_edge_circle(work, *i) == alpha.size())
	  {
	    del_edge_circle(work, *i);
	    for (alphabet_iterator j = alpha.begin(); j != alpha.end(); j++)
	      work.add_letter_edge(*i, 
				   work.choose_state(), 
				   *j);
	  }
      }

    // set initial states
    work.set_initial(work.choose_state());
    
    // set final states
    for (unsigned i = 0; i < fstate; i++)
      {
	hstate_t tmp = work.choose_state();
	while (work.is_final(tmp))
	  tmp = work.choose_state();
	work.set_final(tmp);
      }

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
    
    for (state_iterator i = work.states().begin(); i != work.states().end(); 
	 i++)
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
      if (tmp = work.choose_state() != init)
	work.add_letter_edge(init, tmp, 
			     alpha.choose());
    
    for (unsigned i =0; i < density; i++)
      if (tmp = work.choose_state() != final)
	work.add_letter_edge(tmp, final,
			     alpha.choose());
    
    return work;
  }

  template <class TAutomata>
  unsigned GenRandomAutomata<TAutomata>::alea(unsigned max)
  {
    return ((unsigned) floor(((float) rand() / (float) RAND_MAX) * (max-1)));
  }

} // vcsn

#endif // GEN_RANDOM_HXX
