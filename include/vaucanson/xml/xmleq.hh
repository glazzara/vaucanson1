// xmleq.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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

#ifndef VCSN_XML_XMLEQ_HH
# define VCSN_XML_XMLEQ_HH

/**
 * @file xmleq.hh
 *
 * XML String conversion class.
 *
 * @see vcsn::xml::*Handler
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <string>

# include <xercesc/util/XMLUniDefs.hpp>
# include <xercesc/util/XMLString.hpp>

namespace vcsn
{
  namespace xml
  {
    /// Help to improve performances on comparaison
    class XMLEq
    {
      public:
	XMLCh* fsmxml;
	XMLCh* automaton;
	XMLCh* drawing;
	XMLCh* geometry;
	XMLCh* type;
	XMLCh* monoid;
	XMLCh* generator;
	XMLCh* semiring;
	XMLCh* nsemiring;
	XMLCh* content;
	XMLCh* states;
	XMLCh* state;
	XMLCh* transitions;
	XMLCh* transition;
	XMLCh* initial;
	XMLCh* final;

	XMLCh* label;
	XMLCh* sum;
	XMLCh* product;
	XMLCh* star;
	XMLCh* word;
	XMLCh* zero;
	XMLCh* identity;

	XMLEq ();
	~XMLEq ();
    };
  } // End of namespace xml.

} // End of namespace vcsn.

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/xmleq.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_XMLEQ_HH