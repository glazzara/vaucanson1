// complement.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#  include <vaucanson/algorithms/determinize.hh>
# endif // NDEBUG

# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/misc/contract.hh>

namespace vcsn {

  /*----------------.
  | Complement_here |
  `----------------*/

  template <typename A, typename T>
  void
  complement_here(Element<A, T>& e)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    precondition(is_complete(e) && is_deterministic(e));
    for_each_state(i, e)
      if (e.is_final(*i))
	e.unset_final(*i);
      else
	e.set_final(*i);
  }

  /*----------------.
  | Complement_here |
  `----------------*/

  template <typename A, typename T>
  Element<A, T>
  complement(const Element<A, T>& e)
  {
    Element<A, T> work(e);
    complement_here(work);
    return work;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_COMPLEMENT_HXX
