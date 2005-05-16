// session.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_SESSION_HH
# define VCSN_XML_SESSION_HH

/**
 * @file session.hh
 *
 * XML session management.
 *
 *
 * @see vcsn::xml::XML, vcsn::xml::xerces_parser
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */

# include <iostream>
# include <xercesc/dom/DOM.hpp>

# include <vaucanson/xml/xml_converter.hh>


namespace vcsn
{
  namespace xml
  {
    /**
     * @brief Session mangement class. Use stream operators to use.
     * For example :
     *
     * xml_session s;
     * std::cin >> s;
     * s >> automaton;
     * s << automaton2;
     * std::cout << s;
     *
     */
    struct xml_session
    {
      xml_session();
      ~xml_session();

      xercesc::DOMImplementation*			impl;
      xercesc::DOMDocument*				doc;
      xercesc::DOMElement*				root;
    };

  } // ! xml

  template<typename S, typename T>
  xml::xml_session& op_rin(S&, xml::xml_session&, T&);

  template<typename S, typename T>
  xml::xml_session& op_rout(const S&, xml::xml_session&, const T&);

  template <class IStream>
  IStream& operator >> (IStream&, xml::xml_session&);

  template <class OStream>
  OStream& operator << (OStream&, const xml::xml_session&);


} // !vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/session.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_XML_SESSION_HH
