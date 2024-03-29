// build_pattern.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_BUILD_PATTERN_HXX
# define VCSN_ALGORITHMS_INTERNAL_BUILD_PATTERN_HXX

namespace vcsn
{
  namespace algorithm_patterns
  {

    // The ordered function called by maps
    template <typename Self, typename Etiq>
    bool
    Comparator<Self, Etiq>::operator()(const Etiq& e1, const Etiq& e2) const
    {
      return Self::compare(e1, e2);
    }

    /*-----------------------.
    | IncAutomataConstructor |
    `-----------------------*/

    // The constructor
    template <typename Self, typename T_auto, typename Etiq>
    IncAutomataConstructor<Self, T_auto, Etiq>::IncAutomataConstructor
    (
      const series_set_t& series, const Etiq& etiq
      )
    {
      automata_set_t a_set(series);
      auto_p = new T_auto(a_set);
      unvisited = 0;
      auto_p->set_initial(add_state(etiq));
      current_state = states_map.end();
    }

    // The constructor with list
    template <typename Self, typename T_auto, typename Etiq>
    IncAutomataConstructor<Self, T_auto, Etiq>::IncAutomataConstructor
    (
      const series_set_t& series, const std::list<Etiq>& listexp
      )
    {
      automata_set_t a_set(series);
      auto_p = new T_auto(a_set);
      unvisited = 0;

      for (typename std::list<Etiq>::const_iterator it = listexp.begin();
	   it != listexp.end(); ++it)
	auto_p->set_initial(add_state(*it));

      current_state = states_map.end();
    }


    // To get the result
    template <typename Self, typename T_auto, typename Etiq>
    T_auto*
    IncAutomataConstructor<Self, T_auto, Etiq>::get() const
    {
      return auto_p;
    }

    // To run the algorithm
    template <typename Self, typename T_auto, typename Etiq>
    void
    IncAutomataConstructor<Self, T_auto, Etiq>::run()
    {
      while (unvisited > 0)
      {
	for (current_state = states_map.begin();
	     current_state != states_map.end();
	     ++current_state)
	{
	  if (!(current_state->second.second))
	  {
	    on_state_caller(current_state->first);
	    unvisited -= 1;
	    current_state->second.second = true;
	  }
	}
      }
    }

    // Link current state to another, which can be created
    template <typename Self, typename T_auto, typename Etiq>
    void
    IncAutomataConstructor<Self, T_auto, Etiq>::link_to
    (
      const Etiq& etiq, const letter_t& l
      )
    {
      typename T_auto::hstate_t	s;
      iterator	i = states_map.find(etiq);

      if (i == states_map.end())
	s = add_state(etiq);
      else
	s = i->second.first;
      auto_p->add_letter_transition(current_state->second.first, s, l);
    }

    template <typename Self, typename T_auto, typename Etiq>
    void
    IncAutomataConstructor<Self, T_auto, Etiq>::link_to
    (
      const Etiq& etiq, const series_set_elt_t& el
      )
    {
      typename T_auto::hstate_t	s;
      iterator	i = states_map.find(etiq);

      if (i == states_map.end())
	s = add_state(etiq);
      else
	s = i->second.first;
      auto_p->add_series_transition(current_state->second.first, s, el);
    }

    // A tool to add a state in the set and the automaton
    template <typename Self, typename T_auto, typename Etiq>
    typename T_auto::hstate_t
    IncAutomataConstructor<Self, T_auto, Etiq>::add_state(const Etiq& etiq)
    {
      typename T_auto::hstate_t	res = auto_p->add_state();
      states_map[etiq] = std::pair<typename T_auto::hstate_t, bool>(res, false);
      unvisited += 1;
      return res;
    }

    // To make the current state final
    template <typename Self, typename T_auto, typename Etiq>
    void
    IncAutomataConstructor<Self, T_auto, Etiq>::set_final()
    {
      auto_p->set_final(current_state->second.first);
    }

    // To make the current state final
    template <typename Self, typename T_auto, typename Etiq>
    void
    IncAutomataConstructor<Self, T_auto, Etiq>::set_final
    (const series_set_elt_t& el)
    {
      auto_p->set_final(current_state->second.first, el);
    }


    // The function called on each state :
    // it just call the on_each_state function, which must be defined
    // by user.
    template <typename Self, typename T_auto, typename Etiq>
    void
    IncAutomataConstructor<Self, T_auto, Etiq>::on_state_caller(const Etiq& e)
    {
      static_cast<Self&>(*this).on_state(e);
    }

    // The default function which will compare 2 Etiq
    template <typename Self, typename T_auto, typename Etiq>
    bool
    IncAutomataConstructor<Self, T_auto, Etiq>::compare
    (
      const Etiq& e1, const Etiq& e2
      )
    {
      return e1 < e2;
    }

    /*------------------------.
    | MathAutomataConstructor |
    `------------------------*/

    // The constructor.
    // It takes a container, which must contain the labels of states
    template <typename Self, typename T_auto, typename Etiq>
    template <typename Container>
    MathAutomataConstructor<Self, T_auto, Etiq>::MathAutomataConstructor
    (
      const series_set_t& series, const Container container
      )
    {
      typedef typename Container::iterator	c_iterator;

      automata_set_t a_set(series);
      auto_p = new T_auto(a_set);

      for (c_iterator i = container.begin(); i != container.end(); ++i)
	states_map[*i] = auto_p->add_state();
    }

    // The function used to get the result
    template <typename Self, typename T_auto, typename Etiq>
    T_auto*
    MathAutomataConstructor<Self, T_auto, Etiq>::get() const
    {
      return auto_p;
    }

    // The building function.
    // It calls the templated function link_to() in order to
    // allow user not to declare the return type of delta()
    // (That's why delta_caller() does not exist)
    template <typename Self, typename T_auto, typename Etiq>
    void
    MathAutomataConstructor<Self, T_auto, Etiq>::run()
    {
      alphabet_t alpha = get()->series().monoid().alphabet();
      for (iterator i = states_map.begin(); i != states_map.end(); ++i)
      {
	if (is_initial_caller(i->first))
	  auto_p->set_initial(i->second);
	if (is_final_caller(i->first))
	  auto_p->set_final(i->second);
	for (alphabet_iterator a = alpha.begin(); a != alpha.end(); ++a)
	  link_to(i->second, *a, static_cast<Self&>(*this).delta(i->first, *a));
      }
    }

    // The two following funtions just call the appropriate function
    // of daughter class
    template <typename Self, typename T_auto, typename Etiq>
    bool
    MathAutomataConstructor<Self, T_auto, Etiq>::is_initial_caller
    (
      const Etiq& e
      )	const
    {
      return static_cast<const Self&>(*this).is_initial(e);
    }

    template <typename Self, typename T_auto, typename Etiq>
    bool
    MathAutomataConstructor<Self, T_auto, Etiq>::is_final_caller
    (
      const Etiq& e
      )	const
    {
      return static_cast<const Self&>(*this).is_final(e);
    }

    // Function which build transitions between a state
    // and a set of states
    template <typename Self, typename T_auto, typename Etiq>
    template <typename Container>
    void
    MathAutomataConstructor<Self, T_auto, Etiq>::link_to
    (
      const typename T_auto::hstate_t& state, const letter_t& letter, const Container container
      )
    {
      typedef typename Container::iterator	c_iterator;
      for (c_iterator j = container.begin(); j != container.end(); ++j)
      {
	iterator tmp = states_map.find(*j);
	if (tmp != states_map.end())
	  auto_p->add_letter_transition(state, tmp->second, letter);
      }
    }

    // The default function which will compare 2 Etiq
    template <typename Self, typename T_auto, typename Etiq>
    bool
    MathAutomataConstructor<Self, T_auto, Etiq>::compare
    (
      const Etiq& e1, const Etiq& e2
      )
    {
      return e1 < e2;
    }

  }
}

#endif // ! VCSN_ALGORITHMS_INTERNAL_BUILD_PATTERN_HXX
