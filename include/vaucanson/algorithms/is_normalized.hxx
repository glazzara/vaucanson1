// is_normalized.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_IS_NORMALIZED_HXX
# define VCSN_ALGORITHMS_IS_NORMALIZED_HXX

# include <vaucanson/algorithms/is_normalized.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  template<typename S, typename A>
  bool
  do_is_normalized_transducer(const AutomataBase<S>& trans_set,
			      const A& trans)
  {
    AUTOMATON_TYPES(A);
    bool is_normalized = false;
    for_all_const_transitions(e, trans)
    {
      is_normalized ^= is_letter_support(trans.series_of(*e));
      for_all_const_(series_set_elt_t::support_t,
		     i,
		     trans.series_of(*e).supp())
      {
	is_normalized ^= is_letter_support(trans.series_of(*e).get(*i));
	if (!is_normalized)
	  return false;
      }
    }
    return true;
  }

  template<typename S, typename A>
  bool
  is_normalized_transducer(const Element<S, A>& a)
  {
    TIMER_SCOPED("is_normalized_transducer");
    return do_is_normalized_transducer(a.structure(), a);
  }
}

#endif // ! VCSN_ALGORITHMS_IS_NORMALIZED_HXX
