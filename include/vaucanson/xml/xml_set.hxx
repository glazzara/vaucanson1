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
    XmlSet::monoid_alphabet() const
    {
      if (monoid_node_)
	return monoid_node_->getFirstChild();
      return NULL;
    }

    inline
    const DOMNode*
    XmlSet::semiring_alphabet() const
    {
      if (semiring_node_)
	return semiring_node_->getFirstChild();
      return NULL;
    }

    inline
    int
    XmlSet::semiring_type() const
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
    XmlSet::semiring_set() const
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
    XmlSet::monoid_type() const
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
    XmlSet::monoid_set() const
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
    XmlSet::XmlSet(DOMElement* elt)
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
    XmlSet::XmlSet()
    {
      monoid_node_ = NULL;
      semiring_node_ = NULL;
    }

    inline
    XmlSet
    XmlSet::get_subset()
    {
      XmlSet set;

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
    XmlSet::XmlSet(const XmlSet& other)
      : Structure<vcsn::xml::XmlSet>(other)
    {
      monoid_node_ = other.monoid_node_;
      semiring_node_ = other.semiring_node_;
    }
  }
}

#endif // VCSN_XML_XML_SET_HXX
