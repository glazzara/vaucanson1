// xmleq.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2007 The Vaucanson Group.
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

#ifndef VCSN_XML_XMLEQ_HXX
# define VCSN_XML_XMLEQ_HXX

/**
 * @file xmleq.hxx
 *
 * XML String conversion class.
 *
 * @see vcsn::xml::*Handler
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <vaucanson/misc/contract.hh>

namespace vcsn
{
  namespace xml
  {
    XMLEq::XMLEq ()
    {
      fsmxml = xercesc::XMLString::transcode("fsmxml");
      automaton = xercesc::XMLString::transcode("automaton");
      geometry = xercesc::XMLString::transcode("geometry");
      drawing = xercesc::XMLString::transcode("drawing");
      type = xercesc::XMLString::transcode("labelType");
      monoid = xercesc::XMLString::transcode("monoid");
      generator = xercesc::XMLString::transcode("generator");
      semiring = xercesc::XMLString::transcode("semiring");
      nsemiring = xercesc::XMLString::transcode("numericalSemiring");
      content = xercesc::XMLString::transcode("content");
      states = xercesc::XMLString::transcode("states");
      state = xercesc::XMLString::transcode("state");
      transitions = xercesc::XMLString::transcode("transitions");
      transition = xercesc::XMLString::transcode("transition");
      initial = xercesc::XMLString::transcode("initial");
      final = xercesc::XMLString::transcode("final");

      label = xercesc::XMLString::transcode("label");
      sum = xercesc::XMLString::transcode("sum");
      product = xercesc::XMLString::transcode("product");
      star = xercesc::XMLString::transcode("star");
      word = xercesc::XMLString::transcode("word");
      zero = xercesc::XMLString::transcode("zero");
      identity = xercesc::XMLString::transcode("identity");
    }

    XMLEq::~XMLEq ()
    {
      xercesc::XMLString::release(&fsmxml);
      xercesc::XMLString::release(&automaton);
      xercesc::XMLString::release(&geometry);
      xercesc::XMLString::release(&drawing);
      xercesc::XMLString::release(&type);
      xercesc::XMLString::release(&monoid);
      xercesc::XMLString::release(&generator);
      xercesc::XMLString::release(&semiring);
      xercesc::XMLString::release(&nsemiring);
      xercesc::XMLString::release(&content);
      xercesc::XMLString::release(&states);
      xercesc::XMLString::release(&state);
      xercesc::XMLString::release(&transitions);
      xercesc::XMLString::release(&transition);
      xercesc::XMLString::release(&initial);
      xercesc::XMLString::release(&final);
      xercesc::XMLString::release(&label);
      xercesc::XMLString::release(&sum);
      xercesc::XMLString::release(&product);
      xercesc::XMLString::release(&star);
      xercesc::XMLString::release(&word);
      xercesc::XMLString::release(&zero);
      xercesc::XMLString::release(&identity);
    }
  } // End of namespace xml.

} // End of namespace vcsn.

#endif // ! VCSN_XML_XMLEQ_HXX
