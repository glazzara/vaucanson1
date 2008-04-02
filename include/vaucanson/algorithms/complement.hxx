// complement.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_COMPLEMENT_HXX
# define VCSN_ALGORITHMS_COMPLEMENT_HXX

# include <vaucanson/algorithms/complement.hh>

# ifndef NDEBUG
#  include <vaucanson/algorithms/complete.hh>
#  include <vaucanson/algorithms/is_deterministic.hh>
# endif // NDEBUG

# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/misc/contract.hh>

namespace vcsn {

  /*------------------.
  | complement_here.  |
  `------------------*/

  template <typename A, typename AI>
  void
  complement_here(Element<A, AI>& a)
  {
    TIMER_SCOPED("complement");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    precondition(is_complete(a));
    precondition(is_deterministic(a));
    for_all_const_states(i, a)
      if (a.is_final(*i))
	a.unset_final(*i);
      else
	a.set_final(*i);
  }

  /*-------------.
  | complement.  |
  `-------------*/

  template <typename A, typename AI>
  Element<A, AI>
  complement(const Element<A, AI>& a)
  {
    Element<A, AI> res(a);
    complement_here(res);
    return res;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_COMPLEMENT_HXX
