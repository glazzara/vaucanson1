// session.hh: this file is part of the Vaucanson project.
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

#include <vaucanson/config/system.hh>

#if not defined (VCSN_XML_SESSION_HH) and VCSN_INCLUDE_XML()
# define VCSN_XML_SESSION_HH

# ifndef VCSN_USE_XML
#  error Vaucanson XML support is disabled.
# endif

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

#endif // ! VCSN_XML_SESSION_HH && VCSN_INCLUDE_XML()
