// fsm_dump.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_FSM_DUMP_HH
# define VCSN_TOOLS_FSM_DUMP_HH

/**
 * @file fsm_dump.hh
 *
 * @brief I/O with FSM format.
 */

# include <map>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  namespace tools {

    /*---------.
    | fsm_dump |
    `---------*/
    /** Basic and non configurable saver in the 'fsm' format.
     *
     * Every elements (series, state_content ...) must be printable.
     */
    template <typename St, typename auto_t>
    void fsm_dump(St& out, const auto_t& a);

    /*---------.
    | fsm_load |
    `---------*/
    /** Basic and non configurable loader in the 'fsm' format.
     */
    template <typename St, typename AutoType_>
    void fsm_load(St& in, AutoType_& a);

  } // tools

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/tools/fsm_dump.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_TOOLS_FSM_DUMP_HH
