// xml_loader.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_XML_XML_LOADER_HXX
# define VCSN_XML_XML_LOADER_HXX

# include <vaucanson/xml/xml_loader.hh>

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/xml/types.hh>

# include <vaucanson/tools/usual_macros.hh>

# include <iostream>

namespace vcsn
{
  namespace xml
  {
    template <typename Saver, typename Conv>
    void
    xml_loader::operator () (std::ostream& out,
			     const Saver& s,
			     const Conv&) const
    {
      out << xml_automaton_t (s.automaton());
    }

    template <typename Loader>
    void
    xml_loader::operator () (std::istream& in, Loader& l)
    {
      xml_automata_set_t	s;
      xml_automaton_t		a (s);
      in >> a;
      l.automaton() = a;
    }
  }
}

#endif // ! VCSN_XML_XML_LOADER_HXX
