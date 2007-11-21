// copy.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_COPY_HXX
# define VCSN_AUTOMATA_CONCEPT_COPY_HXX

# include <map>
# include <vaucanson/automata/concept/handlers.hh>


namespace vcsn
{

  template<typename lhs_t, typename rhs_t>
  void auto_copy(lhs_t& dst_,
		 const rhs_t& from)
  {
    lhs_t dst(dst_.structure());
    typedef typename lhs_t::series_set_elt_t dst_series_set_elt_t;

    std::map<typename rhs_t::hstate_t, typename lhs_t::hstate_t> stmap;

    for (typename rhs_t::state_iterator i = from.states().begin();
	 i != from.states().end();
	 ++i)
    {
      typename lhs_t::hstate_t s = dst.add_state();
      dst_series_set_elt_t s_(from.get_final(*i));
      dst.set_final(s, s_);
      dst_series_set_elt_t s__(from.get_initial(*i));
      dst.set_initial(s, s__);
      stmap[*i] = s;
    }

    for (typename rhs_t::transition_iterator i = from.transitions().begin();
	 i != from.transitions().end();
	 ++i)
    {
      dst_series_set_elt_t s(from.series_of(*i));
      dst.add_series_transition(stmap[from.src_of(*i)], stmap[from.dst_of(*i)], s);
    }
    dst_.swap(dst);
  }

  template<typename auto_t>
  auto_t auto_copy(const auto_t& from)
  {
    auto_t dst;
    auto_copy(dst, from);
    return dst;
  }

}


#endif // ! VCSN_AUTOMATA_CONCEPT_COPY_HXX
