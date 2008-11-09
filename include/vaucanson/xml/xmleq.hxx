// xmleq.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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

namespace vcsn
{
  namespace xml
  {
    XMLEq::XMLEq ()
    {
      /* tokens */

      fsmxml = xercesc::XMLString::transcode("fsmxml");

      valueType = xercesc::XMLString::transcode("valueType");
      semiring = xercesc::XMLString::transcode("semiring");
      monoid = xercesc::XMLString::transcode("monoid");
      genSort = xercesc::XMLString::transcode("genSort");
      genCompSort = xercesc::XMLString::transcode("genCompSort");
      genComp = xercesc::XMLString::transcode("genComp");
      monGen = xercesc::XMLString::transcode("monGen");
      monCompGen = xercesc::XMLString::transcode("monCompGen");

      drawing = xercesc::XMLString::transcode("drawingData");
      geometry = xercesc::XMLString::transcode("geometricData");
      data = xercesc::XMLString::transcode("data");

      automaton = xercesc::XMLString::transcode("automaton");
      content = xercesc::XMLString::transcode("automatonStruct");
      states = xercesc::XMLString::transcode("states");
      state = xercesc::XMLString::transcode("state");
      transitions = xercesc::XMLString::transcode("transitions");
      transition = xercesc::XMLString::transcode("transition");
      initial = xercesc::XMLString::transcode("initial");
      final = xercesc::XMLString::transcode("final");

      regExp = xercesc::XMLString::transcode("regExp");
      typedRegExp = xercesc::XMLString::transcode("typedRegExp");

      label = xercesc::XMLString::transcode("label");
      sum = xercesc::XMLString::transcode("sum");
      product = xercesc::XMLString::transcode("product");
      star = xercesc::XMLString::transcode("star");
      leftExtMul = xercesc::XMLString::transcode("leftExtMul");
      rightExtMul = xercesc::XMLString::transcode("rightExtMul");
      one = xercesc::XMLString::transcode("one");
      zero = xercesc::XMLString::transcode("zero");
      monElmt = xercesc::XMLString::transcode("monElmt");
      weight = xercesc::XMLString::transcode("weight");

      writingData = xercesc::XMLString::transcode("writingData");

      /* attributes */

      openPar = xercesc::XMLString::transcode("openPar");
      closePar = xercesc::XMLString::transcode("closePar");
      plus = xercesc::XMLString::transcode("plus");
      times = xercesc::XMLString::transcode("times");
      openWeight = xercesc::XMLString::transcode("openWeight");
      closeWeight = xercesc::XMLString::transcode("closeWeight");
      spaces = xercesc::XMLString::transcode("spaces");

      value = xercesc::XMLString::transcode("value");
      id = xercesc::XMLString::transcode("id");
      source = xercesc::XMLString::transcode("source");
      target = xercesc::XMLString::transcode("target");
      x = xercesc::XMLString::transcode("x");
      y = xercesc::XMLString::transcode("y");
    }

    XMLEq::~XMLEq ()
    {
      xercesc::XMLString::release(&fsmxml);

      xercesc::XMLString::release(&valueType);
      xercesc::XMLString::release(&semiring);
      xercesc::XMLString::release(&monoid);
      xercesc::XMLString::release(&genSort);
      xercesc::XMLString::release(&genCompSort);
      xercesc::XMLString::release(&genComp);
      xercesc::XMLString::release(&monGen);
      xercesc::XMLString::release(&monCompGen);

      xercesc::XMLString::release(&drawing);
      xercesc::XMLString::release(&geometry);
      xercesc::XMLString::release(&data);

      xercesc::XMLString::release(&automaton);
      xercesc::XMLString::release(&content);
      xercesc::XMLString::release(&states);
      xercesc::XMLString::release(&state);
      xercesc::XMLString::release(&transitions);
      xercesc::XMLString::release(&transition);
      xercesc::XMLString::release(&initial);
      xercesc::XMLString::release(&final);

      xercesc::XMLString::release(&regExp);
      xercesc::XMLString::release(&typedRegExp);

      xercesc::XMLString::release(&label);
      xercesc::XMLString::release(&sum);
      xercesc::XMLString::release(&product);
      xercesc::XMLString::release(&star);
      xercesc::XMLString::release(&leftExtMul);
      xercesc::XMLString::release(&rightExtMul);
      xercesc::XMLString::release(&one);
      xercesc::XMLString::release(&zero);
      xercesc::XMLString::release(&monElmt);
      xercesc::XMLString::release(&weight);

      xercesc::XMLString::release(&openPar);
      xercesc::XMLString::release(&closePar);
      xercesc::XMLString::release(&plus);
      xercesc::XMLString::release(&times);
      xercesc::XMLString::release(&openWeight);
      xercesc::XMLString::release(&closeWeight);
      xercesc::XMLString::release(&spaces);

      xercesc::XMLString::release(&value);
      xercesc::XMLString::release(&source);
      xercesc::XMLString::release(&target);
      xercesc::XMLString::release(&x);
      xercesc::XMLString::release(&y);
    }
  } // End of namespace xml.
} // End of namespace vcsn.

#endif // ! VCSN_XML_XMLEQ_HXX
