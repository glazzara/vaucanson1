// gen_random.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003,2004 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_TOOLS_GEN_RANDOM_HXX
# define VCSN_TOOLS_GEN_RANDOM_HXX

# include <vaucanson/config/system.hh>
# include <vaucanson/tools/gen_random.hh>
# include <map>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <vaucanson/tools/usual_macros.hh>

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

    // alphabet construction 
    alphabets_elt_t alpha;
    
    unsigned nb = alea(nb_letter);
    for (unsigned i = 0; i < 2 + nb; ++i)
      alpha.insert(alpha.random_letter());
    monoid_t monoid(alpha);
    semiring_t semi;
    series_t series(semi, monoid);
    automata_set_t aset(series);
    TAutomata work(aset);
    return work;
  }

  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  empty(const automata_set_t& set) 
  {
    TAutomata work(set);
    return work;
  }

  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate(unsigned nb_state, unsigned nb_edge_, 
	   unsigned istate, unsigned fstate,
	   unsigned nb_letter)
  {
    int nb_edge = nb_edge_;
    AUTOMATON_TYPES(TAutomata);
    // check consistency of automaton
    if (nb_edge_ < nb_state - 1)
      nb_edge = nb_state - 1;
    if (fstate > nb_state) fstate = nb_state;
    if (fstate <= 0) fstate = 1;
    if (istate > nb_state) istate = nb_state;
    if (istate <= 0) istate = 1;
    
    // alphabet construction 
    alphabets_elt_t alpha;
        
    unsigned nb = alea(nb_letter);
    for (unsigned i = 0; i < 2 + nb; ++i)
      {
	letter_t l = alpha.random_letter();
	alpha.insert(l);
      }
    monoid_t monoid(alpha);
    semiring_t semi;
    series_t series(semi, monoid);
    automata_set_t aset(series);
    TAutomata work(aset);
    
    for (unsigned i = 0; i < nb_state; i++)
      work.add_state();

    // minimal construction
    state_iterator prev = work.states().begin();
    state_iterator i = prev;
    ++i;
    for (; i != work.states().end(); ++i)
      {
	nb_edge--;
	std::set<hedge_t> aim;
	letter_t e = alpha.choose();
	work.letter_deltac(aim, *prev, e, delta_kind::edges());
	if (aim.size() == 0)
	  work.add_letter_edge(*prev, *i, e);
	prev = i;
      }

    for (int i = 0; i < nb_edge; i++)
      {
	std::set<hstate_t> aim;
	letter_t e = alpha.choose();
	hstate_t s = work.choose_state();
	hstate_t a = work.choose_state();
	work.letter_deltac(aim, s, e, delta_kind::states());
	if (aim.find(a) == aim.end())
	  work.add_letter_edge(s, a, e);
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
  TAutomata GenRandomAutomata<TAutomata>::
  generate(const automata_set_t& set,
	   unsigned nb_state, unsigned nb_edge_, 
	   unsigned istate, unsigned fstate)
  {
    AUTOMATON_TYPES(TAutomata);
    int nb_edge = nb_edge_;
    // check consistency of automaton
    if (nb_edge_ < nb_state - 1)
      nb_edge = nb_state - 1;
    if (fstate > nb_state) fstate = nb_state;
    if (fstate <= 0) fstate = 1;
    if (istate > nb_state) istate = nb_state;
    if (istate <= 0) istate = 1;
    
    TAutomata work(set);
    
    for (unsigned i = 0; i < nb_state; i++)
      work.add_state();

    // minimal construction
    state_iterator prev = work.states().begin();
    state_iterator i = prev;
    ++i;
    for (; i != work.states().end(); ++i)
      {
	nb_edge--;
	std::set<hedge_t> aim;
	letter_t e = set.series().monoid().alphabet().choose();
	work.letter_deltac(aim, *prev, e, delta_kind::edges());
	if (aim.size() == 0)
	  work.add_letter_edge(*prev, *i, e);
	prev = i;
      }

    for (int i = 0; i < nb_edge; i++)
      {
	std::set<hstate_t> aim;
	letter_t e = set.series().monoid().alphabet().choose();
	hstate_t s = work.choose_state();
	hstate_t a = work.choose_state();
	work.letter_deltac(aim, s, e, delta_kind::states());
	if (aim.find(a) == aim.end())
	  work.add_letter_edge(s, a, e);
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
    AUTOMATON_TYPES(TAutomata);
    unsigned res = 0;
    
    for_each_edge(i, work)
      if ((work.origin_of(*i) == state) && (work.aim_of(*i) == state))
	res++;

    return res;
  }
  
  template <class TAutomata>
  void GenRandomAutomata<TAutomata>::
  del_edge_circle(TAutomata& work, hstate_t state)
  {    
    AUTOMATON_TYPES(TAutomata);

    std::list<hedge_t> to_remove;
    for_each_edge(i, work)
      {
	if ((work.origin_of(*i) == state) && (work.aim_of(*i) == state))
	  to_remove.push_back(*i);
      }
    for_each_const_(std::list<hedge_t>, e, to_remove)
      work.del_edge(*e);
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
  generate_with_epsilon(const automata_set_t& set,
			unsigned nb_state, 
			unsigned nb_edge,
			unsigned nb_epsilon_min,
			unsigned nb_epsilon_max)
  {
    TAutomata a = this->generate(set, nb_state, nb_edge);
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
    AUTOMATON_TYPES(TAutomata);

    // check for coherence 
    if (size_alphabet > 26) size_alphabet = 26;
    if (nb_state < 1) size_alphabet = 1;
    

    // alphabet construction 
    alphabet_t alpha;

    for (unsigned i = 0; i < size_alphabet; i++)
      alpha.insert(alpha.random_letter());

    monoid_t m(alpha);
    semiring_t s;
    series_t series(s, m);
    automata_set_t as(series);
    automaton_t work(as);

    for (unsigned i = 0; i < nb_state; i++)
      work.add_state();
    
    for_each_state(i, work)
      {
	for_each_letter(j, alpha)
	  work.add_letter_edge(*i,work.choose_state(),*j);
	while (nb_edge_circle(work, *i) == alpha.size())
	  {
	    del_edge_circle(work, *i);
	    for_each_letter(j, alpha)
	      {
		std::set<hstate_t> ret;
		work.letter_deltac(ret, *i, *j, delta_kind::states());
		if (ret.size() == 0)
		  {
		    hstate_t s;
		    while ((s = work.choose_state()) == *i);
		    work.add_letter_edge(*i, s, *j);
		  }
	      }
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
  generate_dfa(const automata_set_t& set,
	       unsigned nb_state, 
	       unsigned fstate)
  {
    AUTOMATON_TYPES(TAutomata);

    automaton_t work(set);

    for (unsigned i = 0; i < nb_state; i++)
      work.add_state();
    
    for_each_state(i, work)
      {
	for_each_letter(j, set.series().monoid().alphabet())
	  work.add_letter_edge(*i,work.choose_state(),*j);
	while (nb_edge_circle(work, *i) == set.series().monoid().alphabet().size())
	  {
	    del_edge_circle(work, *i);
	    for_each_letter(j, set.series().monoid().alphabet())
	      {
		std::set<hstate_t> ret;
		work.letter_deltac(ret, *i, *j, delta_kind::states());
		if (ret.size() == 0)
		  {
		    hstate_t s;
		    while ((s = work.choose_state()) == *i);
		    work.add_letter_edge(*i, s, *j);
		  }
	      }
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

    const alphabets_elt_t& alpha = work.set().series().monoid().alphabet();

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
  TAutomata GenRandomAutomata<TAutomata>::
  generate_normalized(const automata_set_t& set, unsigned nb_state, unsigned density)
  {
    typedef typename TAutomata::state_iterator state_iterator;
    typedef typename TAutomata::monoid_t::alphabets_elt_t alphabets_elt_t;

    if (density == 0) density = 1;

    TAutomata work = generate(set, nb_state, nb_state + alea(nb_state * density));
    
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

    const alphabets_elt_t& alpha = work.set().series().monoid().alphabet();

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

#endif // VCSN_TOOLS_GEN_RANDOM_HXX
