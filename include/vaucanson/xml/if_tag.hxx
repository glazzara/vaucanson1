// if_tag.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_IF_TAG_HXX
# define VCSN_XML_IF_TAG_HXX

# include <sstream>

# include <vaucanson/xml/if_tag.hh>

# include <vaucanson/xml/strings.hh>
# include <vaucanson/xml/xml_automaton.hh>

namespace vcsn
{

  namespace xml
  {

    /*---------------.
    | Generic if_tag |
    `---------------*/

    template <class Tag>
    DOMElement*
    if_tag<Tag>::add_state(xml_automaton_impl_t& x, hstate_t s, const Tag&)
    {
      x.add_state(s);
      return 0;
    }

    /*-------------------------------.
    | Special if_tag for XmlInfosTag |
    `-------------------------------*/

# define SET_ATTR(Section, Attr)					\
      if ( Section (). get_##Attr ().is_set())				\
      {									\
	std::ostringstream strs;					\
	strs << (Section (). get_##Attr() ());				\
	node->removeAttribute(str_##Attr);				\
	XMLCh* value = XMLString::transcode(strs.str().c_str());	\
	if (node->hasAttribute(str_##Attr))				\
	  {								\
	    if (XMLString::compareIString(node->			\
					  getAttribute(str_##Attr),	\
					  value))			\
	      node->setAttribute(str_##Attr, value);			\
	  }								\
	else								\
	  node->setAttribute(str_##Attr, value);			\
	XMLString::release(&value);					\
      }

# define OPTION_ATTR(Field, Attr, Do)		\
      if ( Field() . get_##Attr() .is_set())	\
      {						\
	Do					\
      }

# define OPTION(Section, Attr, Value, Str)		\
      if ( Section (). get_##Attr ()() == Value )	\
	node->setAttribute(str_##Attr, str_##Str);

    inline
    void
    if_tag<XmlInfosTag>::set_default(DOMElement* n,
				     const XmlInfosTag::Geometry& g)
    {
      DOMElement* node = 0;
      DOMNode* child = n->getFirstChild();
      while (child)
	{
	  if (child->getNodeType() == DOMNode::ELEMENT_NODE and
	      not XMLString::compareIString(child->getNodeName(),
					    str_geometry))
	    {
	      node = static_cast<DOMElement*> (child);
	    }
	  child = child->getNextSibling();
	}

      if (not node)
	{
	  if (g.is_set())
	    {
	      node = n->getOwnerDocument()->createElement(str_geometry);
	      if (n->hasChildNodes())
		n->insertBefore(node, n->getFirstChild());
	      else
		n->appendChild(node);
	    }
	  else
	    return ;
	}

      if (not g.is_set())
	n->removeChild(node);

# include <vaucanson/xml/loadgeometry.inc>

    }

# undef SET_ATTR
# undef OPTION_ATTR
# undef OPTION

    inline
    void
    if_tag<XmlInfosTag>::set_state(DOMElement* n, hstate_t s, XmlInfosTag tag)
    {
      if (tag.get_states().get_label()[s].is_set())
	{
	  XMLCh* label = XMLString::transcode(tag.get_states()
					      .get_label()[s]().c_str());
	  n->setAttribute(str_label, label);
	  XMLString::release(&label);
	  }

      set_default(n, tag.get_states()[s]);
    }

    inline
    DOMElement*
    if_tag<XmlInfosTag>::add_state(xml_automaton_impl_t& x,
				   hstate_t s, const XmlInfosTag& tag)
    {
      if (tag.get_states().get_name().find(s) ==
	  tag.get_states().get_name().end())
	return x.add_state_elt(s);
      else if (tag.get_states().get_name().find(s)->second == "")
	return x.add_state_elt(s);
      else
	return x.add_state_elt(s,
			       tag.get_states().get_name().find(s)->second);
    }

# define SET_ATTR(Section, Attr)					    \
      if (node->hasAttribute(str_##Attr ))				    \
      {									    \
	std::istringstream strs (xml2str(node->getAttribute(str_##Attr ))); \
	strs >> Section () . get_##Attr ()();				    \
      }									    \
      else								    \
      Section (). get_##Attr() .is_set() = false;

# define OPTION_ATTR(Field, Attr, Do)		\
      if (node->hasAttribute(str_##Attr ))	\
      {						\
	Do					\
      }

# define OPTION(Section, Attr, Value, Str)				  \
      if (not XMLString::compareIString(str_##Str,			  \
					node->getAttribute(str_##Attr ))) \
      {									  \
	Section (). get_##Attr ()() = Value;				  \
      }

    inline
    void
    if_tag<XmlInfosTag>::get_default(const DOMElement* n,
				     XmlInfosTag::Geometry& g)
    {
      const DOMNode* child = n->getFirstChild();
      while (child)
	{
	  if (child->getNodeType() == DOMNode::ELEMENT_NODE and
	      not XMLString::compareIString(child->getNodeName(),
					    str_geometry))
	    {
	      const DOMElement* node =
		static_cast<const DOMElement*> (child);

	      g.is_set() = true;

# include <vaucanson/xml/loadgeometry.inc>

	      return ;
	    }
	  child = child->getNextSibling();
	}

      g.is_set() = false;
    }

# undef SET_ATTR
# undef OPTION_ATTR
# undef OPTION

    inline
    void
    if_tag<XmlInfosTag>::get_state(const DOMElement* n,
				   hstate_t s,
				   XmlInfosTag& tag)
    {
      tag.get_states().get_name()[s] = xml2str(n->getAttribute(str_name));
      if (n->hasAttribute(str_label))
	{
	  tag.get_states().get_label()[s]() =
	    xml2str(n->getAttribute(str_label));
	}
      else
	tag.get_states().get_label()[s].is_set() = false;

      get_default(n, tag.get_states()[s]);
    }

  } // End of namespace xml.

} // End of namespace vcsn.

#endif // ! VCSN_XML_IF_TAG_HXX
