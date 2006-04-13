// algorithm.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_BENCHS_COMMON_ALGORITHM_HH
# define VCSN_BENCHS_COMMON_ALGORITHM_HH

template <typename St, typename auto_t>
void fsm_dump(St& out, const auto_t& a)
{
  AUTOMATON_TYPES(auto_t);

  typename auto_t::initial_iterator initial = a.initial().begin();
  std::set<htransition_t> succ;

  a.deltac(succ, *initial, delta_kind::transitions());
  for_all_const_(std::set<htransition_t>, e, succ)
    out << *initial << "\t" << a.dst_of(*e) << "\t"
	<< a.series_of(*e) << "\t 0"
	<< std::endl;
  for_each_state(s, a)
    if (!a.is_initial(*s))
    {
      succ.clear();
      a.deltac(succ, *s, delta_kind::transitions());
      for_all_const_(std::set<htransition_t>, e, succ)
	out << *s << "\t" << a.dst_of(*e) << "\t"
	    << a.series_of(*e) << "\t 0"
	    << std::endl;
    }
  for_each_final_state(f, a)
    out << *f << "\t 0" << std::endl;
}
#endif // ! VCSN_BENCHS_COMMON_ALGORITHM_HH
