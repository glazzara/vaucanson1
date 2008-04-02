// backward_realtime.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_BACKWARD_REALTIME_HXX
# define VCSN_ALGORITHMS_BACKWARD_REALTIME_HXX

# include <vaucanson/algorithms/backward_realtime.hh>
# include <vaucanson/algorithms/realtime.hh>

namespace vcsn {

  /*-------------------------.
  | backward_realtime_here.  |
  `-------------------------*/

  template <class A, typename AI>
  void
  do_backward_realtime_here(const AutomataBase<A>& b, Element<A, AI>& a)
  {
    do_realtime_here (b, a, misc::backward);
  }


  template<typename A, typename AI>
  void
  backward_realtime_here(Element<A, AI>& a)
  {
    do_backward_realtime_here(a.structure(), a);
  }

  /*--------------------.
  | backward_realtime.  |
  `--------------------*/

  template <class A, typename AI>
  Element<A, AI>
  do_backward_realtime(const AutomataBase<A>&b, const Element<A, AI>& a)
  {
    return do_realtime (b, a, misc::backward);
  }

  template<typename A, typename AI>
  Element<A, AI>
  backward_realtime(const Element<A, AI>& a)
  {
    return do_backward_realtime(a.structure(), a);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_BACKWARD_REALTIME_HXX
