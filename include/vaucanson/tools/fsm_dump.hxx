// fsm_dump.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_FSM_DUMP_HXX
# define VCSN_TOOLS_FSM_DUMP_HXX

# include <vaucanson/tools/fsm_dump.hh>
# include <map>
# include <set>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  namespace tools {

    /*---------.
    | fsm_dump |
    `---------*/
    // Description :
    //	 - Basic and non configurable pretty-printer in the 'fsm' format
    //
    // Constraints :
    //	 - Every elements (series, state_content ...) must be printable
    //
    template <typename St, typename auto_t>
    void fsm_dump(St& out, const auto_t& a)
    {
      AUTOMATON_TYPES(auto_t);
      if (a.initial().size() > 1)
      {
	auto_t b(a);
	hstate_t i = b.add_state();
	for_all_initial_states(j, b)
	  b.add_spontaneous(i, *j);
	b.clear_initial();
	b.set_initial(i);
	fsm_dump(out, b);
	return ;
      }
      if (a.states().size() == 0)
	return;

      typename auto_t::initial_iterator initial = a.initial().begin();

      for (delta_iterator e(a.value(), *initial); ! e.done(); e.next())
	out << *initial << "\t" << a.dst_of(*e) << "\t"
	    << a.series_of(*e) << "\t 0"
	    << std::endl;
      for_all_states(s, a)
	if (!a.is_initial(*s))
	{
          for (delta_iterator e(a.value(), *s); ! e.done(); e.next())
	    out << *s << "\t" << a.dst_of(*e) << "\t"
		<< a.series_of(*e) << "\t 0"
		<< std::endl;
	}
      for_all_final_states(f, a)
	out << *f << "\t 0" << std::endl;
    }

  } // tools

} // vcsn

#endif // ! VCSN_TOOLS_FSM_DUMP_HXX
