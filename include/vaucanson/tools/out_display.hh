// out_display.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_OUT_DISPLAY_HH
# define VCSN_TOOLS_OUT_DISPLAY_HH

/**
 * @file out_display.hh
 *
 * Out display method, useful for xml_display and dot_display.
 *
 * @author Florent Terrones <florent.terrones@lrde.epita.fr>
 */

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  namespace tools {

    template <class S, class T>
    bool
    out_display(const AutomataBase<S>&,
		const T&,
		const Element<S, T>& a,
		const std::string& name,
		const bool bg,
		char *const argv[],
		void (*function)(std::ostream& o,
				 const Element<S, T>& a,
				 const std::string& name));

  } // End of namespace tools.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/tools/out_display.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_TOOLS_OUT_DISPLAY_HH
