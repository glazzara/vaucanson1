// translate.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSLATE_HXX
# define VCSN_AUTOMATA_CONCEPT_TRANSLATE_HXX

# include <vaucanson/automata/concept/translate.hh>
# include <vaucanson/automata/concept/handlers.hh>
# include <map>

namespace vcsn {

  template<typename lhs_t, typename rhs_t, typename F>
  void auto_translate_transitions(lhs_t& dst_,
				  const rhs_t& from,
				  const F& translate_fun)
  {
    lhs_t dst;
    std::map<hstate_t, hstate_t> stmap;

    dst.create();
    dst.series() = from.series();
    for (typename rhs_t::state_iterator i = from.states().begin();
	 i != from.states().end();
	 ++i)
    {
      hstate_t s = dst.add_state();
      dst.set_final(s, from.get_final(*i));
      dst.set_initial(s, from.get_initial(*i));
      stmap[*i] = s;
    }
    for (typename rhs_t::transition_iterator i = from.transitions().begin();
	 i != from.transitions().end();
	 ++i)
      dst.add_series_transition(stmap[i.origin()], stmap[i.aim()],
				translate_fun(from.series_of(*i)));
    dst_.swap(dst);
  }

  template<typename auto_t, typename F>
  auto_t auto_translate_transitions(const auto_t& from, const F& translate_fun)
  {
    auto_t dst;
    auto_translate_transitions(dst, from, translate_fun);
    return dst;
  }

} // vcsn

#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSLATE_HXX
