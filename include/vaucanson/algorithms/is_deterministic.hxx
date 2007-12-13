// is_deterministic.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
    typedef typename std::set<htransition_t>		delta_ret_t;
    delta_ret_t	delta_ret;

    input.deltac(delta_ret, *current_state, delta_kind::transitions());
    // FIXME : O(n^2) => O(nlog(n)) There is maybe an algorithm in O(nlog(n))
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
  template <typename A, typename input_t>
  bool
  do_is_deterministic(const AutomataBase<A>&	,
		      const input_t&		input)
  {
    precondition(is_realtime(input));

    AUTOMATON_TYPES(input_t);
    semiring_elt_t		  zero_semiring
      = input.structure().series().semiring()
      .zero(SELECT(typename semiring_elt_t::value_t));

    // Empty automaton is not deterministic
    if (input.states().size() == 0)
      return false;

    if (input.initial().size() != 1)
      return false;

    for_all_states(i, input)
      if (not is_state_deterministic (input, i, zero_semiring))
	return false;
    return true;
  }


  template<typename A, typename T>
  bool
  is_deterministic(const Element<A, T>& a)
  {
    TIMER_SCOPED("is_deterministic");
    return do_is_deterministic(a.structure(), a);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_IS_DETERMINISTIC_HXX
