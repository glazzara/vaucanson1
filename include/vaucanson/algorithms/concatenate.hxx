// concatenate.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_CONCATENATE_HXX
# define VCSN_ALGORITHMS_CONCATENATE_HXX

# include <vaucanson/algorithms/concatenate.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <map>

namespace vcsn {

  template <class Self, class Auto>
  void
  do_auto_in_concat(const AutomataBase<Self>&   ,
		    Auto&			lhs,
		    const Auto&			rhs)
  {
    AUTOMATON_TYPES(Auto);
    std::map<hstate_t, hstate_t>	trans;

    for_each_state(s, rhs)
      {
	hstate_t ns = lhs.add_state();
	trans[*s] = ns;
	if (rhs.is_initial(*s))
	  for_each_final_state(f, lhs)
	    lhs.add_series_edge(*f, ns,
				lhs.get_final(*f) * rhs.get_initial(*s));
      }
    for_each_edge(e, rhs)
      lhs.add_edge(trans[rhs.origin_of(*e)],
		   trans[rhs.aim_of(*e)],
		   rhs.label_of(*e));
    lhs.clear_final();
    for_each_final_state(f, rhs)
      lhs.set_final(trans[*f], rhs.get_final(*f));
  }


  template <class A, class T>
  Element<A, T>
  concatenate(const Element<A, T>& lhs, const Element<A, T>& rhs)
  {
    Element<A, T> ret(lhs);
    do_auto_in_concat(ret.structure(), ret, rhs);
    return ret;
  }

  template <class A, class T>
  void
  concatenate_here(Element<A, T>& lhs, const Element<A, T>& rhs)
  {
    do_auto_in_concat(lhs.structure(), lhs, rhs);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_CONCATENATE_HXX
