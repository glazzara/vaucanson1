// xml_chooser.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XML_CHOOSER_HXX
# define VCSN_XML_XML_CHOOSER_HXX

/**
 * @file xml_chooser.hxx
 *
 * XML specialized class, providing methods to create <type> tag and to
 * create labels in the XML document.
 *
 * @see vcsn::xml::xml_converter, vcsn::xml::Node
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */


namespace vcsn
{
  namespace xml
  {
    /*-------------.
    | Base chooser |
    `-------------*/

    template <class S, class T>
    const char*
    xml_chooser_base<S, T>::choose_start_tag()
    { return "automaton"; }

    template <class S, class T>
    void
    xml_chooser_base<S, T>::create_type_tag(const Element<S, T>& aut,
					    xercesc::DOMDocument* doc,
					    xercesc::DOMElement* root)
    {
      xercesc::DOMElement* type = doc->createElement(STR2XML("type"));
      xercesc::DOMElement* monoid =
	tools::create_monoid(aut.structure().series().monoid(), doc, type);
      tools::create_alphabet(aut.structure().series().monoid().alphabet(),
			     doc, monoid);
      tools::create_semiring(aut, aut.structure().series().semiring(),
			     doc, type);
      root->appendChild(type);
    }


    template <class S, class T>
    void
    xml_chooser_base<S, T>::create_label(hedge_t e,
					 const Element<S, T>& aut,
					 xercesc::DOMElement* elt)

    {
      tools::add_label(elt, aut, aut.series_of(e));
    }


    template <class S, class T>
    void
    xml_chooser_base<S, T>::create_initial_label(hstate_t s,
						 const Element<S, T>& aut,
						 xercesc::DOMElement* elt)
    {
      tools::add_label(elt, aut, aut.get_initial(s));
    }

    template <class S, class T>
    void
    xml_chooser_base<S, T>::create_final_label(hstate_t s,
					       const Element<S, T>& aut,
					       xercesc::DOMElement* elt)
    {
      tools::add_label(elt, aut, aut.get_final(s));
    }


    /*---------------------.
    | Transducers on P(B*) |
    `---------------------*/

    template <class S, class T>
    const char*
    xml_chooser<Transducer<S>, T>::choose_start_tag()
    { return "transducer"; }

    template <class S, class T>
    void
    xml_chooser<Transducer<S>, T>
    ::create_type_tag(const Element<Transducer<S>, T>& aut,
		      xercesc::DOMDocument* doc,
		      xercesc::DOMElement* root)
    {
      xercesc::DOMElement* type = doc->createElement(STR2XML("type"));
      xercesc::DOMElement* in_monoid =
	tools::create_monoid(aut.structure().series().monoid(), doc, type);
      tools::create_alphabet(aut.structure().series().monoid().alphabet(),
			     doc, in_monoid);
      xercesc::DOMElement* semiring =
	tools::create_semiring(aut, aut.structure().series().semiring(),
			       doc, type);
      xercesc::DOMElement* out_monoid =
	tools::create_monoid(aut.structure().series().semiring().monoid(),
			     doc, semiring);
      tools::create_alphabet(aut.structure().series().semiring()
			     .monoid().alphabet(), doc, out_monoid);
      tools::create_semiring(aut,
			     aut.structure().series().semiring().semiring(),
			     doc, semiring);
      root->appendChild(type);
    }


    /*----------------.
    | FMP Transducers |
    `----------------*/

    TParmFMP
    const char*
    xml_chooser<FMPtype>::choose_start_tag()
    { return "transducer"; }


    TParmFMP
    void
    xml_chooser<FMPtype>
    ::create_type_tag(const Element<FMPtype>& aut,
		      xercesc::DOMDocument* doc,
		      xercesc::DOMElement* root)
    {
      xercesc::DOMElement* type = doc->createElement(STR2XML("type"));
      xercesc::DOMElement* monoid =
	tools::create_monoid(aut.structure().series().monoid(), doc, type);

      xercesc::DOMElement* first_monoid =
	tools::create_monoid(aut.structure().series().monoid().first_monoid(),
			     doc, monoid);
      tools::create_alphabet(aut.structure().series().monoid()
			     .first_monoid().alphabet(),
			     doc, first_monoid);

      xercesc::DOMElement* second_monoid =
	tools::create_monoid(aut.structure().series().monoid().second_monoid(),
			     doc, monoid);
      tools::create_alphabet(aut.structure().series().monoid()
			     .second_monoid().alphabet(),
			     doc, second_monoid);

      tools::create_semiring(aut, aut.structure().series().semiring(),
			     doc, type);
      root->appendChild(type);
    }


  } // !xml

} // !vcsn


# undef TParmFMP
# undef FMPtype

#endif // ! VCSN_XML_XML_CHOOSER_HXX
