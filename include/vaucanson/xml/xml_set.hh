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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
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

    using namespace xercesc;

    /** @addtogroup xml *//** @{ */

    /// XML automaton set. Just for loading.
    class XmlSet : public Structure<XmlSet>
    {
    public:
      /// Type values.
      enum { UNSET, UNKNOWN,
	     BOOLEAN, NUMERICAL, TROPICAL_MIN, TROPICAL_MAX,
	     FUNCTION, HADAMARD, SHUFFLE,
	     LETTERS, PAIRS, WEIGHTED, INTEGERS,
	     WORDS, UNIT, CPFM, FCM, FC,
	     B, Z, R, RATSERIES };
      /**
       * @brief Read constructor.
       * @param elt XML automaton root node.
       */
      XmlSet(DOMElement* elt);
      /// Default constructor.
      XmlSet();
      XmlSet(const XmlSet&);

      /**
       * Check semiring type (BOOLEAN,NUMERICAL, TROPICAL_MIN, TROPICAL_MAX,
       * FUNCTION, HADAMARD, SHUFFLE).
       */
      int semiring_type() const;
      /// Check semiring set (B, Z, R, RATSERIES).
      int semiring_set() const;
      /// Check monoid type (LETTERS, PAIRS, WEIGHTED, INTEGERS).
      int monoid_type() const;
      /// Check monoid set (WORDS, UNIT, CPFM, FCM, FC).
      int monoid_set() const;

      XmlSet get_subset();

      const DOMNode*	monoid_alphabet() const;
      const DOMNode*	semiring_alphabet() const;
    private:
      DOMElement*	monoid_node_;
      DOMElement*	semiring_node_;
    };

    /** @} */

  } // End of namespace xml.

  /** @addtogroup xml *//** @{ */

  template <typename T>
  struct MetaElement<xml::XmlSet, T>
    : public MetaElement<Structure<xml::XmlSet>, T>
  { };

  template <>
  struct dynamic_traits<xml::XmlSet>
  {
    static const bool ret = true;
  };

  /** @} */
}

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/xml_set.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_XML_XML_SET_HH
