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
#ifndef VCSN_XML_XML_SET_HXX
# define VCSN_XML_XML_SET_HXX

# include <vaucanson/xml/xml_set.hh>

# include <vaucanson/xml/strings.hh>

namespace vcsn
{
  namespace xml
  {

    inline
    XmlStructure::XmlStructure(DOMElement* root)
      : doc_ (root->getOwnerDocument()),
	root_ (root),
	type_ (0),
	monoid_ (0),
	semiring_ (0)
    {
      // Get the <type> node.
      DOMNode*	child = root_->getFirstChild();
      while (child and
	     (child->getNodeType() != DOMNode::ELEMENT_NODE or
	      XMLString::compareIString(child->getNodeName(), str_type)))
	child = child->getNextSibling();
      if (child)
	{
	  type_ = static_cast<DOMElement*> (child);
	  // Extract <monoid> and <semiring>.
	  child = type_->getFirstChild();
	  while (child)
	    {
	      if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
		  // <monoid> node.
		  if (not XMLString::compareIString(child->getNodeName(),
						    str_monoid))
		    monoid_ = static_cast<DOMElement*> (child);
		  // <semiring> node.
		  else if (not XMLString::compareIString(child->getNodeName(),
							 str_semiring))
		    semiring_ = static_cast<DOMElement*> (child);
		}
	      child = child->getNextSibling();
	    }
	}

      if (not type_)
	{
	  type_ = doc_->createElement(str_type);
	  root_->appendChild(type_);
	}
      if (not semiring_)
	{
	  semiring_ = doc_->createElement(str_semiring);
	  type_->appendChild(semiring_);
	}
      if (not monoid_)
	{
	  monoid_ = doc_->createElement(str_monoid);
	  type_->insertBefore(monoid_, semiring_);
	}
    }

    inline
    XmlStructure::XmlStructure()
      : doc_ (0),
	root_ (0),
	type_ (0),
	monoid_ (0),
	semiring_ (0)
    {
      DOMImplementation* impl =
	xercesc::DOMImplementationRegistry::getDOMImplementation(str_LS);

      DOMDocumentType* doctype =
	impl->createDocumentType(str_automaton, 0, str_vaucanson_pdtd);

      doc_ =
	impl->createDocument(str_http_c_s_swww_plrde_pepita_pfr_svaucanson,
			     str_automaton, doctype);

      root_	= doc_->getDocumentElement();
      type_	= doc_->createElement(str_type);
      monoid_	= doc_->createElement(str_monoid);
      semiring_	= doc_->createElement(str_semiring);

      type_->appendChild(monoid_);
      type_->appendChild(semiring_);

      root_->appendChild(type_);
    }

    inline
    XmlStructure::XmlStructure(const XmlStructure& other)
      : Structure<XmlStructure> (other),
	doc_ (other.doc_),
	root_ (other.root_),
	type_ (other.type_),
	monoid_ (other.monoid_),
	semiring_ (other.semiring_)
    {
    }

    inline
    XmlStructure&
    XmlStructure::operator = (const XmlStructure& rhs)
    {
      doc_ = rhs.doc_;
      root_ = rhs.root_;
      type_ = rhs.type_;
      monoid_ = rhs.monoid_;
      semiring_ = rhs.semiring_;

      return *this;
    }

    inline
    bool
    XmlStructure::operator == (const XmlStructure& rhs)
    {
      return rhs.root_ == root_;
    }

    inline
    int
    XmlStructure::semiring_structure() const
    {
      if (semiring_)
	{
	  if (semiring_->hasAttribute(str_operations))
	    {
	      const XMLCh* v = semiring_->getAttribute(str_operations);
	      if (not XMLString::compareIString(v, str_boolean))
		return BOOLEAN;
	      if (not XMLString::compareIString(v, str_numerical))
		return NUMERICAL;
	      if (not XMLString::compareIString(v, str_tropicalMin))
		return TROPICAL_MIN;
	      if (not XMLString::compareIString(v, str_tropicalMax))
		return TROPICAL_MAX;
	      if (not XMLString::compareIString(v, str_function))
		return FUNCTION;
	      if (not XMLString::compareIString(v, str_hadamard))
		return HADAMARD;
	      if (not XMLString::compareIString(v, str_shuffle))
		return SHUFFLE;
	      return UNKNOWN;
	    }
	}
      return UNSET;
    }

    inline
    int
    XmlStructure::semiring_value() const
    {
      if (semiring_)
	{
	  if (semiring_->hasAttribute(str_set))
	    {
	      const XMLCh* v = semiring_->getAttribute(str_set);
	      if (not XMLString::compareIString(v, str_Z))
		return Z;
	      if (not XMLString::compareIString(v, str_B))
		return B;
	      if (not XMLString::compareIString(v, str_R))
		return R;
	      if (not XMLString::compareIString(v, str_ratseries))
		return RATSERIES;
	      return UNKNOWN;
	    }
	}
      return UNSET;
    }

    inline
    int
    XmlStructure::monoid_structure() const
    {
      if (monoid_)
	{
	  if (monoid_->hasAttribute(str_generators))
	    {
	      const XMLCh* v = monoid_->getAttribute(str_generators);
	      if (not XMLString::compareIString(v, str_letters))
		return LETTERS;
	      if (not XMLString::compareIString(v, str_pairs))
		return PAIRS;
	      if (not XMLString::compareIString(v, str_weighted))
		return WEIGHTED;
	      if (not XMLString::compareIString(v, str_integers))
		return INTEGERS;
	      return UNKNOWN;
	    }
	}
      return UNSET;
    }

    inline
    int
    XmlStructure::monoid_value() const
    {
      if (monoid_)
	{
	  if (monoid_->hasAttribute(str_type))
	    {
	      const XMLCh* v = monoid_->getAttribute(str_type);
	      if (not XMLString::compareIString(v, str_free))
		return WORDS;
	      if (not XMLString::compareIString(v, str_unit))
		return UNIT;
	      if (not XMLString::compareIString(v, str_CPFM))
		return CPFM;
	      if (not XMLString::compareIString(v, str_FCM))
		return FCM;
	      if (not XMLString::compareIString(v, str_FC))
		return FC;
	      return UNKNOWN;
	    }
	}
      return UNSET;
    }

    // FIXME: <Thomas Claveirole> What is the purpose of that method?
    inline
    XmlStructure
    XmlStructure::get_subset()
    {
      XmlStructure xs;

      if (semiring_)
	{
	  DOMNode* child = semiring_->getFirstChild();
	  while (child)
	    {
	      if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
		  if (not XMLString::compareIString(child->getNodeName(),
						    str_monoid))
		    xs.monoid_ = static_cast<DOMElement*> (child);
		  if (not XMLString::compareIString(child->getNodeName(),
						    str_semiring))
		    xs.semiring_ = static_cast<DOMElement*> (child);
		}
	      child = child->getNextSibling();
	    }
	}
      return xs;
    }

    inline
    DOMDocument*
    XmlStructure::doc()
    {
      return doc_;
    }

    inline
    const DOMDocument*
    XmlStructure::doc() const
    {
      return doc_;
    }

# define XML_STRUCTURE_DEFINE_ACCESSOR(Name, Const)	\
    inline						\
    Const DOMElement*					\
    XmlStructure:: Name () Const			\
    {							\
      return Name ## _;					\
    }
# define XML_STRUCTURE_DEFINE_ACCESSOR_BOTH(Name)	\
    XML_STRUCTURE_DEFINE_ACCESSOR(Name,)		\
    XML_STRUCTURE_DEFINE_ACCESSOR(Name, const)

    XML_STRUCTURE_DEFINE_ACCESSOR_BOTH(root)
    XML_STRUCTURE_DEFINE_ACCESSOR_BOTH(type)
    XML_STRUCTURE_DEFINE_ACCESSOR_BOTH(monoid)
    XML_STRUCTURE_DEFINE_ACCESSOR_BOTH(semiring)
# undef XML_STRUCTURE_DEFINE_ACCESSOR_BOTH
# undef XML_STRUCTURE_DEFINE_ACCESSOR

  } // End of namespace xml.

} // End of namespace vcsn.

#endif // ! VCSN_XML_XML_SET_HXX
