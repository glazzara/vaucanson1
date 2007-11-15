// gen_random.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TOOLS_GEN_RANDOM_HXX
# define VCSN_TOOLS_GEN_RANDOM_HXX

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <cstdlib>

namespace vcsn {

  using namespace algebra;

  /*---------------------.
  | GenRandomAutomataSet |
  `---------------------*/

  template <class AutoSet>
  AutoSet
  GenRandomAutomataSet::generate(SELECTOR(AutomataBase<AutoSet>),
				 unsigned nb_letter)
  {

    AUTOMATA_SET_TYPES(AutoSet);

    alphabet_t		alpha;
    unsigned		nb = alea(nb_letter ? nb_letter :
				  alpha.max_size());
    for (unsigned i = 0; i < nb; ++i)
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
    AUTOMATA_SET_TYPES(AutoSet);

    alphabet_t			input_alpha;
    alphabet_t			output_alpha;

    unsigned			nb = alea(input_nb_letter ? input_nb_letter :
					  input_alpha.max_size());
    for (unsigned i = 0; i < nb; ++i)
      input_alpha.insert(input_alpha.random_letter());

    nb = alea(output_nb_letter ? output_nb_letter :
	      output_alpha.max_size());
    for (unsigned i = 0; i < nb; ++i)
      output_alpha.insert(output_alpha.random_letter());

    monoid_t			input_monoid(input_alpha);
    monoid_t			output_monoid(output_alpha);

    typename semiring_t::semiring_t	semi;
    semiring_t			output_series(semi, output_monoid);

    series_set_t		series(output_series, input_monoid);

    automata_set_t		auto_set(series);
    return auto_set;
  }

  unsigned alea(unsigned max)
  {
    return int (1 + float (max) * rand() / (RAND_MAX + 1.0));
  }

  /*------------------.
  | GenRandomAutomata |
  `------------------*/

  template <class TAutomata, class AutomataSetGenerator>
  GenRandomAutomata<TAutomata, AutomataSetGenerator>::GenRandomAutomata()
  {}


  /*------.
  | empty |
  `------*/

  template <class TAutomata, class AutomataSetGenerator>
  TAutomata GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  empty(unsigned nb_letter)
  {
    automata_set_t aset =
      GenRandomAutomataSet::generate(SELECT(automata_set_t), nb_letter);
    TAutomata work(aset);
    return work;
  }

  template <class TAutomata, class AutomataSetGenerator>
  TAutomata GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  empty(const automata_set_t& set)
  {
    TAutomata work(set);
    return work;
  }

  /*---------.
  | generate |
  `---------*/

  template <class TAutomata, class AutomataSetGenerator>
  TAutomata GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  generate(unsigned nb_state, unsigned nb_transition_,
	   unsigned istate, unsigned fstate,
	   unsigned nb_letter)
  {
    automata_set_t aset =
      GenRandomAutomataSet::generate(SELECT(automata_set_t), nb_letter);
    return generate(aset, nb_state, nb_transition_, istate, fstate);
  }

  template <class TAutomata, class AutomataSetGenerator>
  TAutomata GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  generate(const automata_set_t& set,
	   unsigned nb_state, unsigned nb_transition_,
	   unsigned istate, unsigned fstate)
  {
    AUTOMATON_TYPES(TAutomata);
    AUTOMATON_FREEMONOID_TYPES(TAutomata);
    int nb_transition = nb_transition_;
    // check consistency of automaton
    if (nb_transition_ < nb_state - 1)
      nb_transition = nb_state - 1;
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
      nb_transition--;
      std::set<htransition_t> dst;
      letter_t e = set.series().monoid().alphabet().choose();
      work.letter_deltac(dst, *prev, e, delta_kind::transitions());
      if (dst.size() == 0)
	work.add_letter_transition(*prev, *i, e);
      prev = i;
    }

    for (int i = 0; i < nb_transition; i++)
    {
      std::set<hstate_t> dst;
      letter_t e = set.series().monoid().alphabet().choose();
      hstate_t s = work.choose_state();
      hstate_t a = work.choose_state();
      work.letter_deltac(dst, s, e, delta_kind::states());
      if (dst.find(a) == dst.end())
	work.add_letter_transition(s, a, e);
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

  template <class TAutomata, class AutomataSetGenerator>
  unsigned GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  nb_transition_circle(TAutomata work, hstate_t state)
  {
    AUTOMATON_TYPES(TAutomata);
    unsigned res = 0;

    for_all_transitions(i, work)
      if ((work.src_of(*i) == state) && (work.dst_of(*i) == state))
	res++;

    return res;
  }

  template <class TAutomata, class AutomataSetGenerator>
  void GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  del_transition_circle(TAutomata& work, hstate_t state)
  {
    AUTOMATON_TYPES(TAutomata);

    std::list<htransition_t> to_remove;
    for_all_transitions(i, work)
    {
      if ((work.src_of(*i) == state) && (work.dst_of(*i) == state))
	to_remove.push_back(*i);
    }
    for_all_const_(std::list<htransition_t>, e, to_remove)
      work.del_transition(*e);
  }


  /*----------------------.
  | generate with epsilon |
  `----------------------*/

  template <class TAutomata, class AutomataSetGenerator>
  TAutomata GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  generate_with_epsilon(unsigned nb_state,
			unsigned nb_transition,
			unsigned nb_epsilon_min,
			unsigned nb_epsilon_max)
  {
    automata_set_t aset =
      GenRandomAutomataSet::generate(SELECT(automata_set_t));
    TAutomata a = generate_with_epsilon(aset, nb_state, nb_transition,
					nb_epsilon_min, nb_epsilon_max);
    return a;
  }



  template <class TAutomata, class AutomataSetGenerator>
  TAutomata GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  generate_with_epsilon(const automata_set_t& set,
			unsigned nb_state,
			unsigned nb_transition,
			unsigned nb_epsilon_min,
			unsigned nb_epsilon_max)
  {
    TAutomata a = generate(set, nb_state, nb_transition);
    unsigned nb_eps = nb_epsilon_min + alea(nb_epsilon_max - nb_epsilon_min);

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

  template <class TAutomata, class AutomataSetGenerator>
  TAutomata GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  generate_dfa(unsigned nb_state,
	       unsigned size_alphabet,
	       unsigned fstate)
  {
    automata_set_t aset =
      GenRandomAutomataSet::generate(SELECT(automata_set_t), size_alphabet);
    TAutomata a = generate_dfa(aset, nb_state, fstate);
    return a;
  }



  template <class TAutomata, class AutomataSetGenerator>
  TAutomata GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  generate_dfa(const automata_set_t& set,
	       unsigned nb_state,
	       unsigned fstate)
  {
    AUTOMATON_TYPES(TAutomata);
    AUTOMATON_FREEMONOID_TYPES(TAutomata);
    automaton_t work(set);

    for (unsigned i = 0; i < nb_state; i++)
      work.add_state();

    for_all_states(i, work)
    {
      for_all_letters(j, set.series().monoid().alphabet())
	work.add_letter_transition(*i,work.choose_state(),*j);
      while (nb_transition_circle(work, *i) == set.series().monoid().alphabet().size())
      {
	del_transition_circle(work, *i);
	for_all_letters(j, set.series().monoid().alphabet())
	{
	  std::set<hstate_t> ret;
	  work.letter_deltac(ret, *i, *j, delta_kind::states());
	  if (ret.size() == 0)
	  {
	    hstate_t s;
	    while ((s = work.choose_state()) == *i);
	    work.add_letter_transition(*i, s, *j);
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

  template <class TAutomata, class AutomataSetGenerator>
  TAutomata GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  generate_normalized(unsigned nb_state, unsigned density)
  {
    automata_set_t aset =
      AutomataSetGenerator::generate(SELECT(automata_set_t));
    TAutomata a = generate_normalized(aset, nb_state, density);
    return a;
  }

  template <class TAutomata, class AutomataSetGenerator>
  TAutomata GenRandomAutomata<TAutomata, AutomataSetGenerator>::
  generate_normalized(const automata_set_t& set,
		      unsigned nb_state,
		      unsigned density)
  {
    typedef typename TAutomata::state_iterator state_iterator;
    typedef typename TAutomata::monoid_t::alphabets_elt_t alphabets_elt_t;

    if (density == 0)
      density = 1;

    TAutomata work = generate(set, nb_state,
			      nb_state + alea(nb_state * density));

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
      if ((tmp = work.choose_state()) != init)
	work.add_letter_transition(init, tmp,
				   alpha.choose());

    for (unsigned i =0; i < density; i++)
      if ((tmp = work.choose_state()) != final)
	work.add_letter_transition(tmp, final,
				   alpha.choose());

    return work;
  }

} // vcsn

#endif // ! VCSN_TOOLS_GEN_RANDOM_HXX
