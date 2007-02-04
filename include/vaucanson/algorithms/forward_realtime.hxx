// forward_realtime.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_FORWARD_REALTIME_HXX
# define VCSN_ALGORITHMS_FORWARD_REALTIME_HXX

# include <vaucanson/algorithms/forward_realtime.hh>
# include <vaucanson/algorithms/realtime.hh>

namespace vcsn {

  /*------------------------.
  | forward_realtime_here.  |
  `------------------------*/

  template <class A_, typename Auto_>
  void
  do_forward_realtime_here(const AutomataBase<A_>&b, Auto_& a)
  {
    do_realtime_here (b, a, misc::forward);
  }

  template<typename A, typename T>
  void
  forward_realtime_here(Element<A, T>& a)
  {
    do_forward_realtime_here(a.structure(), a);
  }

  /*-------------------.
  | forward_realtime.  |
  `-------------------*/

  template<typename A_, typename Auto_>
  Auto_
  do_forward_realtime(const AutomataBase<A_>&b, const Auto_& a)
  {
    return do_realtime (b, a, misc::forward);
  }


  template<typename A, typename T>
  Element<A, T>
  forward_realtime(const Element<A, T>& a)
  {
    return do_forward_realtime(a.structure(), a);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_FORWARD_REALTIME_HXX
