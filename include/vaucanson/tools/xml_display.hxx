// xml_display.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_XML_DISPLAY_HXX
# define VCSN_TOOLS_XML_DISPLAY_HXX

/**
 * @file xml_display.hxx
 *
 * Calls out_display with xml_dump as the function to launch by out_display.
 *
 * @author Florent Terrones <florent.terrones@lrde.epita.fr>
 */

# include <ostream>
# include <string>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/xml_dump.hh>
# include <vaucanson/tools/out_display.hh>

namespace vcsn {

  namespace tools {

    template <class S, class T>
    bool
    xml_display(const Element<S, T>& a,
		const std::string& name,
		const bool bg,
		char *const argv[])
    {
      return out_display(a.structure(), a.value(),
			 a, name, bg, argv,
			 xml_dump<Element<S, T> >);
    }

  } // End of namespace tools.

} // End of namespace vcsn.

#endif // ! VCSN_TOOLS_XML_DISPLAY_HXX
