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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
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

  /*---------------------.
  | GenRandomAutomataSet |
  `---------------------*/

  GenRandomAutomataSet::GenRandomAutomataSet()
  {}

  template <class AutoSet>
  AutoSet
  GenRandomAutomataSet::generate(SELECTOR(AutomataBase<AutoSet>),
				 unsigned nb_letter)
  {

    AUTO_SET_TYPES(AutoSet);

    alphabet_t		alpha;
    unsigned		nb = alea(nb_letter ?
				  nb_letter - 1 : alpha.max_size() - 1);
    for (unsigned i = 0; i < 2 + nb; ++i)
      alpha.insert(alpha.random_letter());

    monoid_t		monoid(alpha);
    semiring_t		semi;
    series_set_t	series(semi, monoid);
    automata_set_t	autoset(series);
    return autoset;
  }

  template <class AutoSet>
  AutoSet
  GenRandomAutomataSet::generate(SELECTOR(TransducerBase<AutoSet>),
				 unsigned input_nb_letter,
				 unsigned output_nb_letter)
  {
    AUTO_SET_TYPES(AutoSet);

    alphabet_t			input_alpha;
    alphabet_t			output_alpha;

    unsigned			nb = alea(input_nb_letter ?
					  input_nb_letter - 1 :
					  input_alpha.max_size() - 1);
    for (unsigned i = 0; i < 1 + nb; ++i)
      input_alpha.insert(input_alpha.random_letter());

    nb = alea(output_nb_letter ?
	      output_nb_letter - 1 : output_alpha.max_size() - 1);
    for (unsigned i = 0; i < 2 + nb; ++i)
      output_alpha.insert(output_alpha.random_letter());

    monoid_t			input_monoid(input_alpha);
    monoid_t			output_monoid(output_alpha);

    typename semiring_t::semiring_t	semi;
    semiring_t			output_series(semi, output_monoid);

    series_set_t		series(output_series, input_monoid);

    automata_set_t		auto_set(series);
    return auto_set;
  }

  unsigned GenRandomAutomataSet::alea(unsigned max)
  {
    return ((unsigned) floor(((float) rand() / (float) RAND_MAX) * (max-1)));
  }

  /*------------------.
  | GenRandomAutomata |
  `------------------*/

  template <class TAutomata>
  GenRandomAutomata<TAutomata>::GenRandomAutomata()
  {}

  template <class TAutomata>
  GenRandomAutomata<TAutomata>::GenRandomAutomata(unsigned init)
  {
    srand(init);
  }

	/*------.
	| empty |
	`------*/

  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  empty(unsigned nb_letter)
  {
    automata_set_t aset =
      GenRandomAutomataSet::generate(SELECT(automata_set_t), nb_letter);
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

	/*---------.
	| generate |
	`---------*/

  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate(unsigned nb_state, unsigned nb_edge_,
	   unsigned istate, unsigned fstate,
	   unsigned nb_letter)
  {
    automata_set_t aset =
      GenRandomAutomataSet::generate(SELECT(automata_set_t), nb_letter);
    return this->generate(aset, nb_state, nb_edge_, istate, fstate);
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

	/*---------------.
	| useful methods |
	`---------------*/

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


	/*----------------------.
	| generate with epsilon |
	`----------------------*/

  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate_with_epsilon(unsigned nb_state,
			unsigned nb_edge,
			unsigned nb_epsilon_min,
			unsigned nb_epsilon_max)
  {
    automata_set_t aset =
      GenRandomAutomataSet::generate(SELECT(automata_set_t));
    TAutomata a = this->generate_with_epsilon(aset, nb_state, nb_edge,
					      nb_epsilon_min, nb_epsilon_max);
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
    unsigned nb_eps = nb_epsilon_min +
      GenRandomAutomataSet::alea(nb_epsilon_max - nb_epsilon_min);

    for (unsigned i = 0; i < nb_eps; ++i)
      {
	hstate_t f = a.choose_state();
	hstate_t t = a.choose_state();
	a.add_spontaneous(f, t);
      }
    return a;
  }


	/*-------------.
	| generate dfa |
	`-------------*/

  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate_dfa(unsigned nb_state,
	       unsigned size_alphabet,
	       unsigned fstate)
  {
    // check for coherence
    if (size_alphabet > 26) size_alphabet = 26;
    if (nb_state < 1) size_alphabet = 1;

    automata_set_t aset =
      GenRandomAutomataSet::generate(SELECT(automata_set_t), size_alphabet);
    TAutomata a = this->generate_dfa(aset, nbstate, fstate);
    return a;
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


	/*--------------------.
	| generate normalized |
	`--------------------*/

  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate_normalized(unsigned nb_state, unsigned density)
  {
    automata_set_t aset =
      GenRandomAutomataSet::generate(SELECT(automata_set_t));
    TAutomata a = this->generate_normalized(aset, nb_state, density);
    return a;
  }

  template <class TAutomata>
  TAutomata GenRandomAutomata<TAutomata>::
  generate_normalized(const automata_set_t& set,
		      unsigned nb_state,
		      unsigned density)
  {
    typedef typename TAutomata::state_iterator state_iterator;
    typedef typename TAutomata::monoid_t::alphabets_elt_t alphabets_elt_t;

    if (density == 0)
      density = 1;

    TAutomata work = generate(set, nb_state,
			      nb_state +
			      GenRandomAutomataSet::alea(nb_state * density));

    for (state_iterator i = work.states().begin(); i != work.states().end();
	 i++)
      {
	if (work.is_initial(*i))
	  work.unset_initial(*i);
	if (work.is_final(*i))
	  work.unset_final(*i);
      }

    hstate_t init = work.add_state();
    hstate_t final = work.add_state();

    work.set_initial(init);
    work.set_final(final);

    const alphabets_elt_t&
      alpha = work.structure().series().monoid().alphabet();

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

} // vcsn

#endif // VCSN_TOOLS_GEN_RANDOM_HXX
