// if_tag.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_IF_TAG_HH
# define VCSN_XML_IF_TAG_HH

# include <xercesc/dom/DOM.hpp>

# include <vaucanson/automata/concept/handlers.hh>

# include <vaucanson/xml/types.hh>
# include <vaucanson/xml/infos.hh>

// FIXME:  This file lacks  documentation.

namespace vcsn
{

  namespace xml
  {

    using xercesc::DOMElement;
    using xercesc::DOMNode;

    /*---------------.
    | Generic if_tag |
    `---------------*/

# define XML_IF_TAG_DECLARE_SET(Name, Args...)	\
      static					\
      void					\
      set_ ## Name (DOMElement*, Args)		\
      {						\
      }
# define XML_IF_TAG_DECLARE_GET(Name, Args...)	\
      static					\
      void					\
      get_ ## Name(const DOMElement*, Args)	\
      {						\
      }

    template <typename Tag>
    struct if_tag
    {
      XML_IF_TAG_DECLARE_SET(root,	Tag)
      XML_IF_TAG_DECLARE_SET(structure,	Tag)
      XML_IF_TAG_DECLARE_SET(states,	Tag)
      XML_IF_TAG_DECLARE_SET(edges,	Tag)
      XML_IF_TAG_DECLARE_SET(initials,	Tag)
      XML_IF_TAG_DECLARE_SET(finals,	Tag)
      XML_IF_TAG_DECLARE_SET(state,	hstate_t,	Tag)
      XML_IF_TAG_DECLARE_SET(edge,	hedge_t,	Tag)
      XML_IF_TAG_DECLARE_SET(initial,	hstate_t,	Tag)
      XML_IF_TAG_DECLARE_SET(final,	hstate_t,	Tag)

      XML_IF_TAG_DECLARE_GET(root,	Tag&)
      XML_IF_TAG_DECLARE_GET(structure,	Tag&)
      XML_IF_TAG_DECLARE_GET(states,	Tag&)
      XML_IF_TAG_DECLARE_GET(edges,	Tag&)
      XML_IF_TAG_DECLARE_GET(initials,	Tag&)
      XML_IF_TAG_DECLARE_GET(finals,	Tag&)
      XML_IF_TAG_DECLARE_GET(state,	hstate_t,	Tag&)
      XML_IF_TAG_DECLARE_GET(edge,	hedge_t,	Tag&)
      XML_IF_TAG_DECLARE_GET(initial,	hstate_t,	Tag&)
      XML_IF_TAG_DECLARE_GET(final,	hstate_t,	Tag&)

      static
      DOMElement*
      add_state(xml_automaton_impl_t& x, hstate_t s, const Tag&);
    }; // End of class template if_tag<Tag>.

# undef XML_IF_TAG_DECLARE_GET
# undef XML_IF_TAG_DECLARE_SET

    /*-------------------------------.
    | Special if_tag for XmlInfosTag |
    `-------------------------------*/

# define XML_IF_TAG_DECLARE_SET1(Name)			\
      static						\
      void						\
      set_ ## Name (DOMElement* node, XmlInfosTag tag)	\
      {							\
	set_default(node, tag.get_ ## Name ());		\
      }
# define XML_IF_TAG_DECLARE_SET2(Name, Arg2)			\
      static							\
      void							\
      set_ ## Name (DOMElement* node, Arg2 s, XmlInfosTag tag)	\
      {								\
	set_default(node, tag.get_ ## Name ## s()[s]);		\
      }
# define XML_IF_TAG_DECLARE_GET1(Name)				\
      static							\
      void							\
      get_ ## Name (const DOMElement* node, XmlInfosTag& tag)	\
      {								\
	get_default(node, tag.get_ ## Name ());			\
      }
# define XML_IF_TAG_DECLARE_GET2(Name, Arg2)			\
      static							\
      void							\
      get_ ## Name (DOMElement* node, Arg2 s, XmlInfosTag& tag)	\
      {								\
	get_default(node, tag.get_ ## Name ## s()[s]);		\
      }

    template <>
    struct if_tag<XmlInfosTag>
    {
      XML_IF_TAG_DECLARE_SET1(root)
      XML_IF_TAG_DECLARE_SET1(structure)
      XML_IF_TAG_DECLARE_SET1(states)
      XML_IF_TAG_DECLARE_SET1(edges)
      XML_IF_TAG_DECLARE_SET1(initials)
      XML_IF_TAG_DECLARE_SET1(finals)

      static
      void
      set_default(DOMElement* n, const XmlInfosTag::Geometry& g);

      static
      void
      set_state(DOMElement* n, hstate_t s, XmlInfosTag tag);

      XML_IF_TAG_DECLARE_SET2(edge,	hedge_t)
      XML_IF_TAG_DECLARE_SET2(initial,	hstate_t)
      XML_IF_TAG_DECLARE_SET2(final,	hstate_t)

      static
      DOMElement*
      add_state(xml_automaton_impl_t& x, hstate_t s, const XmlInfosTag& tag);

      static
      void
      get_default(const DOMElement* n, XmlInfosTag::Geometry& g);

      XML_IF_TAG_DECLARE_GET1(root)
      XML_IF_TAG_DECLARE_GET1(structure)
      XML_IF_TAG_DECLARE_GET1(states)
      XML_IF_TAG_DECLARE_GET1(edges)
      XML_IF_TAG_DECLARE_GET1(initials)
      XML_IF_TAG_DECLARE_GET1(finals)

      static
      void
      get_state(const DOMElement* n, hstate_t s, XmlInfosTag& tag);


      XML_IF_TAG_DECLARE_GET2(edge,	hedge_t)
      XML_IF_TAG_DECLARE_GET2(initial,	hstate_t)
      XML_IF_TAG_DECLARE_GET2(final,	hstate_t)

    }; // End of specialized class if_tag<XmlInfosTag>.

# undef XML_IF_TAG_DECLARE_SET1
# undef XML_IF_TAG_DECLARE_SET2
# undef XML_IF_TAG_DECLARE_GET1
# undef XML_IF_TAG_DECLARE_GET2

  } // End of namespace xml.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/if_tag.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_IF_TAG_HH
