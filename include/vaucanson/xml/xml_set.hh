// xml_set.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XML_SET_HH
# define VCSN_XML_XML_SET_HH

# include <vaucanson/design_pattern/structure.hh>

# include <xercesc/dom/DOM.hpp>

/** @addtogroup xml *//** @{ */
/**
 * @file xml_set.hh
 *
 * XML automaton set tools.
 *
 * @author Valentin David <valentin@lrde.epita.fr>
 */
/** @} */

namespace vcsn
{

  namespace xml
  {

    using xercesc::DOMDocument;
    using xercesc::DOMElement;
    using xercesc::DOMNode;

    /** @addtogroup xml *//** @{ */

    /// XML automaton set. Just for loading.
    class XmlStructure : public Structure<XmlStructure>
    {
    public:
      /// Type values.
      enum
	{
	  UNSET, UNKNOWN,
	  // Semiring structures.
	  BOOLEAN, NUMERICAL, TROPICAL_MIN, TROPICAL_MAX,
	  FUNCTION, HADAMARD, SHUFFLE,
	  // Semiring values.
	  B, Z, R, RATSERIES,
	  // Monoid structures.
	  CPFM, FCM, FC,
	  // Monoid values.
	  LETTERS, PAIRS, WEIGHTED, INTEGERS, WORDS, UNIT
	};
      /**
       * @brief Read constructor.
       * @param root XML automaton root node.
       */
      XmlStructure(DOMElement* root);
      /// Default constructor.
      XmlStructure();
      XmlStructure(const XmlStructure&);

      XmlStructure&
      operator = (const XmlStructure& rhs);

      bool
      operator == (const XmlStructure& rhs);

      /**
       * Get the semiring structure type.
       *
       * The  result may  be one  of  BOOLEAN,NUMERICAL, TROPICAL_MIN,
       * TROPICAL_MAX, FUNCTION, HADAMARD, SHUFFLE).
       */
      int semiring_structure() const;
      /// Get the semiring value implementation type (B, Z, R, RATSERIES).
      int semiring_value() const;
      /**
       * Get monoid structure type.
       *
       * The result is one of LETTERS, PAIRS, WEIGHTED, INTEGERS.
       */
      int monoid_structure() const;
      /// Check monoid value implementation type (WORDS, UNIT, CPFM, FCM, FC).
      int monoid_value() const;

      XmlStructure get_subset();

      const DOMDocument*	doc() const;
      DOMDocument*		doc();

      DOMElement*	root();
      const DOMElement*	root() const;

      DOMElement*	type();
      const DOMElement*	type() const;

      DOMElement*	monoid();
      const DOMElement*	monoid() const;

      DOMElement*	semiring();
      const DOMElement*	semiring() const;

    private:
      DOMDocument*	doc_;

      DOMElement*	root_;
      DOMElement*	type_;
      DOMElement*	monoid_;
      DOMElement*	semiring_;
    };

    /** @} */

  } // End of namespace xml.

  /** @addtogroup xml *//** @{ */

  template <typename T>
  struct MetaElement<xml::XmlStructure, T>
    : public MetaElement<Structure<xml::XmlStructure>, T>
  {
  };

  template <>
  struct dynamic_traits<xml::XmlStructure>
  {
    static const bool ret = true;
  };

  /** @} */
}

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/xml_set.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_XML_SET_HH
