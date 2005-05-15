// xml_chooser.hxx: this file is part of the Vaucanson project.
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

#endif // VCSN_XML_XML_CHOOSER_HXX
