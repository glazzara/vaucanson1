// is_realtime.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_IS_REALTIME_HXX
# define VCSN_ALGORITHMS_IS_REALTIME_HXX

# include <vaucanson/algorithms/is_realtime.hh>

# include <vaucanson/automata/concept/transducer_base.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  template<typename S, typename A>
  bool
  do_is_realtime(const TransducerBase<S>&,
		 const A& trans)
  {
    AUTOMATON_TYPES(A);
    for_each_edge(e, trans)
      {
        if (!is_letter_support(trans.series_of(*e)))
	  return false;
      }
    return true;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_IS_REALTIME_HXX
