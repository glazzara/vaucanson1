// types.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_TYPES_HH
# define VCSN_XML_TYPES_HH

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/implementation/graph.hh>

# include <vaucanson/xml/xml_automaton.hh>
# include <vaucanson/xml/xml_set.hh>

/** @addtogroup xml *//** @{ */
/**
 * @file types.hh
 *
 * Utilities for XML Vaucanson types.
 *
 * @author Valentin David <valentin@lrde.epita.fr>
 */

/// Get the corresponding Xml implementation.
# define XML_OF(X...) ::vcsn::xml::XmlOf< X >::ret

/// Attach XML infos on Vaucanson graph.
# define ATTACH_XML_INFOS(X...) ::vcsn::xml::AttachXmlInfos< X >::ret

/** @} */

namespace vcsn
{

  namespace xml
  {

    /** @addtogroup xml *//** @{ */
    template <class I>
    struct XmlOf;

    template <typename I, typename J>
    struct XmlOf<Element<I, J> > {
      typedef Element<I, XmlAutomaton> ret;
    };

    template <class I>
    struct AttachXmlInfos;

    template <typename I, typename J, typename K,
	      typename L, typename M, typename N,
	      typename O>
    struct AttachXmlInfos<Element<I, Graph<J, K, L, M, N, O> > > {
      typedef Element<I, Graph<J, K, L, M, N, XmlInfosTag> > ret;
    };

    /// Dynamic XML automaton type.
    typedef Element<XmlSet, XmlAutomaton> xml_automaton_t;

    /** @} */

  } // End of namespace xml.

} // End of namespace vcsn.

#endif // VCSN_XML_TYPES_HH
