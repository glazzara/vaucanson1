// xml_set.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XML_SET_HXX
# define VCSN_XML_XML_SET_HXX

# include <vaucanson/xml/xml_set.hh>

# include <vaucanson/xml/strings.hh>

namespace vcsn
{
  namespace xml
  {
    inline
    const DOMNode*
    XmlStructure::monoid_alphabet() const
    {
      if (monoid_node_)
	return monoid_node_->getFirstChild();
      return NULL;
    }

    inline
    const DOMNode*
    XmlStructure::semiring_alphabet() const
    {
      if (semiring_node_)
	return semiring_node_->getFirstChild();
      return NULL;
    }

    inline
    int
    XmlStructure::semiring_type() const
    {
      if (semiring_node_) {
	if (semiring_node_->hasAttribute(str_operations)) {
	  const XMLCh* v = semiring_node_->getAttribute(str_operations);
	  if (!XMLString::compareIString(v, str_boolean))
	    return BOOLEAN;
	  if (!XMLString::compareIString(v, str_numerical))
	    return NUMERICAL;
	  if (!XMLString::compareIString(v, str_tropicalMin))
	    return TROPICAL_MIN;
	  if (!XMLString::compareIString(v, str_tropicalMax))
	    return TROPICAL_MAX;
	  if (!XMLString::compareIString(v, str_function))
	    return FUNCTION;
	  if (!XMLString::compareIString(v, str_hadamard))
	    return HADAMARD;
	  if (!XMLString::compareIString(v, str_shuffle))
	    return SHUFFLE;
	  return UNKNOWN;
	}
      }
      return UNSET;
    }

    inline
    int
    XmlStructure::semiring_structure() const
    {
      if (semiring_node_) {
	if (semiring_node_->hasAttribute(str_set)) {
	  const XMLCh* v = semiring_node_->getAttribute(str_set);
	  if (!XMLString::compareIString(v, str_Z))
	    return Z;
	  if (!XMLString::compareIString(v, str_B))
	    return B;
	  if (!XMLString::compareIString(v, str_R))
	    return R;
	  if (!XMLString::compareIString(v, str_ratseries))
	    return RATSERIES;
	  return UNKNOWN;
	}
      }
      return UNSET;
    }

    inline
    int
    XmlStructure::monoid_type() const
    {
      if (monoid_node_) {
	if (monoid_node_->hasAttribute(str_generators)) {
	  const XMLCh* v = monoid_node_->getAttribute(str_generators);
	  if (!XMLString::compareIString(v, str_letters))
	    return LETTERS;
	  if (!XMLString::compareIString(v, str_pairs))
	    return PAIRS;
	  if (!XMLString::compareIString(v, str_weighted))
	    return WEIGHTED;
	  if (!XMLString::compareIString(v, str_integers))
	    return INTEGERS;
	  return UNKNOWN;
	}
      }
      return UNSET;
    }

    inline
    int
    XmlStructure::monoid_structure() const
    {
      if (monoid_node_) {
	if (monoid_node_->hasAttribute(str_type)) {
	  const XMLCh* v = monoid_node_->getAttribute(str_type);
	  if (!XMLString::compareIString(v, str_free))
	    return WORDS;
	  if (!XMLString::compareIString(v, str_unit))
	    return UNIT;
	  if (!XMLString::compareIString(v, str_CPFM))
	    return CPFM;
	  if (!XMLString::compareIString(v, str_FCM))
	    return FCM;
	  if (!XMLString::compareIString(v, str_FC))
	    return FC;
	  return UNKNOWN;
	}
      }
      return UNSET;
    }

    inline
    XmlStructure::XmlStructure(DOMElement* elt)
    {
      monoid_node_ = NULL;
      semiring_node_ = NULL;
      DOMNode* child = elt->getFirstChild();
      while (child) {
	if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	  if (!XMLString::compareIString(child->getNodeName(), str_type))
	    break ;
	}
	child = child->getNextSibling();
      }
      if (!child)
	return ;
      child = child->getFirstChild();
      while (child) {
	if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	  if (!XMLString::compareIString(child->getNodeName(), str_monoid))
	    monoid_node_ = static_cast<DOMElement*>(child);
	  if (!XMLString::compareIString(child->getNodeName(), str_semiring))
	    semiring_node_ = static_cast<DOMElement*>(child);
	}
	child = child->getNextSibling();
      }
    }

    inline
    XmlStructure::XmlStructure()
    {
      monoid_node_ = NULL;
      semiring_node_ = NULL;
    }

    inline
    XmlStructure
    XmlStructure::get_subset()
    {
      XmlStructure set;

      if (semiring_node_) {
	DOMNode* child = semiring_node_->getFirstChild();
	while (child) {
	  if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	    if (!XMLString::compareIString(child->getNodeName(), str_monoid))
	      set.monoid_node_ = static_cast<DOMElement*>(child);
	    if (!XMLString::compareIString(child->getNodeName(), str_semiring))
	      set.semiring_node_ = static_cast<DOMElement*>(child);
	  }
	  child = child->getNextSibling();
	}
      }
      return set;
    }

    inline
    XmlStructure::XmlStructure(const XmlStructure& other)
      : Structure<vcsn::xml::XmlStructure>(other)
    {
      monoid_node_ = other.monoid_node_;
      semiring_node_ = other.semiring_node_;
    }
  }
}

#endif // VCSN_XML_XML_SET_HXX
