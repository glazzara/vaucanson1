// realtime_decl.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_REALTIME_DECL_HXX
# define VCSN_ALGORITHMS_REALTIME_DECL_HXX

# include <vaucanson/algorithms/realtime_decl.hh>

namespace vcsn {

  template<typename S, typename T>
  Element<S, T>
  realtime(const Element<S, T>& e)
  {
    return do_realtime(e.structure(), e);
  }

  template <typename S, typename T>
  void
  realtime_here(Element<S, T>& e)
  {
    return do_realtime_here(e.structure(), e);
  }

  template<typename S, typename T>
  bool
  is_realtime(const Element<S, T>& e)
  {
    return do_is_realtime(e.structure(), e);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_REALTIME_DECL_HXX
