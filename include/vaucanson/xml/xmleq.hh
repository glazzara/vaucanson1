// xmleq.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2008 The Vaucanson Group.
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

# include <xercesc/util/XMLUniDefs.hpp>
# include <xercesc/util/XMLString.hpp>

namespace vcsn
{
  namespace xml
  {
    /**
     * Help to improve performances on comparaison
     * Since transcode(string) is more expensive than transcode(XMLCh)
     * We transcode and store all the tokens we might need to compare
     * while parsing a document.
     */
    class XMLEq
    {
      public:
	XMLCh* fsmxml;

	XMLCh* valueType;
	XMLCh* semiring;
	XMLCh* monoid;
	XMLCh* genSort;
	XMLCh* genCompSort;
	XMLCh* genComp;
	XMLCh* monGen;
	XMLCh* monCompGen;

	XMLCh* drawing;
	XMLCh* geometry;
	XMLCh* data;

	XMLCh* automaton;
	XMLCh* content;
	XMLCh* states;
	XMLCh* state;
	XMLCh* transitions;
	XMLCh* transition;
	XMLCh* initial;
	XMLCh* final;

	XMLCh* regExp;
	XMLCh* typedRegExp;

	XMLCh* label;
	XMLCh* sum;
	XMLCh* product;
	XMLCh* star;
	XMLCh* leftExtMul;
	XMLCh* rightExtMul;
	XMLCh* one;
	XMLCh* zero;
	XMLCh* monElmt;
	XMLCh* weight;

	XMLCh* writingData;

	XMLEq ();
	~XMLEq ();
    };

  } // End of namespace xml.

} // End of namespace vcsn.

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/xmleq.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_XMLEQ_HH
