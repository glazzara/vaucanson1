// realtime.hxx: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_REALTIME_HXX
# define VCSN_ALGORITHMS_REALTIME_HXX

# include <vaucanson/algorithms/realtime.hh>

# include <vaucanson/algorithms/forward_realtime.hh>
# include <vaucanson/algorithms/backward_realtime.hh>

namespace vcsn {

  /*------------.
  | is_realtime |
  `------------*/
  template <class A_, typename Auto_>
  bool
  do_is_realtime(const AutomataBase<A_>&,
		 const Auto_&		   a)
  {
    for (typename Auto_::edge_iterator e = a.edges().begin();
	 e != a.edges().end();
	 ++e)
      if (a.series_of(*e) ==
	  a.structure().series().
	  identity(SELECT(typename Auto_::series_set_elt_value_t)))
	return false;
    return true;
  }


  /*--------------.
  | realtime_here |
  `--------------*/

  template<typename Auto_, typename A_>
  void
  do_realtime_here(const AutomataBase<A_>&,
		   Auto_& a,
		   realtime_type type = forward)
  {
    if (type == forward)
      return forward_realtime_here(a);
    else
      return backward_realtime_here(a);
  }


  template<typename A, typename T>
  void
  realtime_here(Element<A, T>& a, realtime_type type)
  {
    return do_realtime_here(a.structure(), a, type);
  }

  /*---------.
  | realtime |
  `---------*/

  template<typename Auto_, typename A_>
  Auto_
  do_realtime(const AutomataBase<A_>&,
	      const Auto_& a,
	      realtime_type type = forward)
  {
    if (type == forward)
      return forward_realtime(a);
    else
      return backward_realtime(a);
  }

  template<typename A, typename T>
  Element<A, T>
  realtime(const Element<A, T>& a, realtime_type type)
  {
    return do_realtime(a.structure(), a, type);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_REALTIME_HXX
