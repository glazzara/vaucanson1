// is_letterized.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_IS_LETTERIZED_HXX
# define VCSN_ALGORITHMS_IS_LETTERIZED_HXX

# include <vaucanson/algorithms/is_letterized.hh>

# include <vaucanson/misc/usual_macros.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>

namespace vcsn
{
  template<typename S, typename A, typename B, typename T>
  bool
  do_is_letterized_transducer(// t must be an automaton ...
			      const AutomataBase<S>&,
			      // ... over a free monoid product.
			      const algebra::FreeMonoidProduct<A, B>&,
			      const T& t)
  {
    TIMER_SCOPED("is_letterized_transducer");

    // Type helper.
    AUTOMATON_TYPES(T);

# define CHECK_LTL_CONDITION \
    for_all_const_(series_set_elt_t::support_t, it, label.supp()) \
    { \
      if (!(((*it).first.size() == ((*it).second.size())) && \
	    ((*it).second.size() <= 1))) \
      return false; \
    }

    for_all_const_initial_states(i, t)
    {
      series_set_elt_t label = t.get_initial(*i);
      CHECK_LTL_CONDITION
    }

    for_all_const_transitions(e, t)
    {
      series_set_elt_t label = t.series_of(*e);
      CHECK_LTL_CONDITION
    }

    for_all_const_final_states(f, t)
    {
      series_set_elt_t label = t.get_final(*f);
      CHECK_LTL_CONDITION
    }

# undef CHECK_CONDITION

    return true;
  }

  /*----------------------.
  | is_letterized facades |
  `----------------------*/

  template <typename S, typename A>
  bool
  is_letterized_transducer(const Element<S, A>& t)
  {
    return do_is_letterized_transducer(t.structure(),
				       t.structure().series().monoid(), t);
  }

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_IS_LETTERIZED_HXX
