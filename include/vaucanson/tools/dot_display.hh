// dot_display.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_TOOLS_DOT_DISPLAY_HH
# define VCSN_TOOLS_DOT_DISPLAY_HH

/**
 * @file dot_display.hxx
 *
 * Calls out_display with dot_dump as the function to launch by out_display.
 *
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 */

# include <vaucanson/design_pattern/element.hh>

# include <string>

namespace vcsn
{
  namespace tools
  {
    static char *const dotty_argv[] = { "dotty", "-", 0 };

    template <class S, class T>
    bool
    dot_display(const Element<S, T>& a,
		const std::string& name,
		const bool bg = false,
		char *const argv[] = dotty_argv);

  }
}

# ifndef VCSN_USE_INTERFACE_ONLY
# include <vaucanson/tools/dot_display.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_TOOLS_DOT_DISPLAY_HH
