// fsm_dump.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef MISC_FSM_DUMP_HH
# define MISC_FSM_DUMP_HH

# include <map>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {
  
  namespace misc {

    /*---------.
    | fsm_dump |
    `---------*/
    // Description :
    //   - Basic and non configurable pretty-printer in the 'fsm' format
    //   
    // Constraints :
    //   - Every elements (series, state_content ...) must be printable
    //
    template <typename St, typename auto_t>
    void fsm_dump(St& out, const auto_t& a);
	 
    /*---------.
    | fsm_load |
    `---------*/
    template <typename St, typename AutoType_>
    void fsm_load(St& in, AutoType_& a);

  } // misc 
  
} // vcsn

#endif // MISC_FSM_DUMP_HH
