// is_deterministic.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_IS_DETERMINISTIC_HXX
# define VCSN_ALGORITHMS_IS_DETERMINISTIC_HXX

# include <vaucanson/algorithms/is_deterministic.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <set>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*-------------------------.
  | is_state_deterministic.  |
  `-------------------------*/

  template <typename input_t>
  static bool
  is_state_deterministic (input_t& input,
			  typename input_t::state_iterator& current_state,
			  typename input_t::series_set_elt_t::semiring_elt_t&
								 zero_semiring)
  {
    AUTOMATON_TYPES(input_t);

    typedef typename series_set_elt_t::support_t	support_t;
    typedef typename std::list<htransition_t>		delta_ret_t;
    delta_ret_t	delta_ret;

    // FIXME : O(n^2) => O(nlog(n)) There is maybe an algorithm in O(nlog(n))
    for (typename input_t::delta_transition_iterator j(input.value(), *current_state);
         ! j.done();
         j.next())
      delta_ret.push_back(*j);
    for_all_const_(delta_ret_t, j, delta_ret)
    {
      series_set_elt_t s = input.series_of(*j);
      typename delta_ret_t::const_iterator k = j;
      ++k;
      for (; k != delta_ret.end(); ++k)
      {
	series_set_elt_t s_ = input.series_of(*k);
	for_all_(support_t, supp, s.supp())
	  if (s_.get(*supp) != zero_semiring)
	    return false;
      }
    }
    return true;
  }




  /*-------------------.
  | is_deterministic.  |
  `-------------------*/
  template <typename A, typename AI>
  bool
  do_is_deterministic(const AutomataBase<A>&,
		      const Element<A, AI>&  input)
  {
    precondition(is_realtime(input));

    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    semiring_elt_t		  zero_semiring
      = input.structure().series().semiring()
      .zero(SELECT(typename semiring_elt_t::value_t));


    if (input.initial().size() > 1)
      return false;

    for_all_const_states(i, input)
      if (not is_state_deterministic (input, i, zero_semiring))
	return false;
    return true;
  }


  template<typename A, typename AI>
  bool
  is_deterministic(const Element<A, AI>& a)
  {
    TIMER_SCOPED("is_deterministic");
    return do_is_deterministic(a.structure(), a);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_IS_DETERMINISTIC_HXX
