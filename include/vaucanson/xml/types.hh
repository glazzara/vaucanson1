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
#ifndef VCSN_XML_TYPES_HH
# define VCSN_XML_TYPES_HH

/** @addtogroup xml *//** @{ */
/**
 * @file types.hh
 *
 * Utilities for XML Vaucanson types.
 *
 * @author Valentin David <valentin@lrde.epita.fr>
 */
/** @} */

namespace vcsn
{

  // Forward declarations.
  template <class S, class T>
  struct Element;

  template <class Kind, class Word, class Weight,
	    class Series, class Letter, class Tag>
  struct Graph;

  namespace xml
  {
    /** @addtogroup xml *//** @{ */

    // Forward declarations.
    class XmlInfosTag;
    class XmlValue;
    class XmlStructure;
    class XmlAutomaton;
    class XmlSession;

    template <class I>
    struct AttachXmlInfos;

    template <typename S,
	      typename Kind,
	      typename Word,
	      typename Weight,
	      typename Series,
	      typename Letter,
	      typename Tag>
    struct AttachXmlInfos< Element<S, Graph< Kind,
					     Word,
					     Weight,
					     Series,
					     Letter,
					     Tag > > >
    {
      typedef
        Element<S, Graph< Kind, Word, Weight, Series, Letter, XmlInfosTag > >
        ret;
    };

/// Attach XML infos on Vaucanson graph.
# define ATTACH_XML_INFOS(X...) ::vcsn::xml::AttachXmlInfos< X >::ret

    /// Dynamic XML value type.
    typedef XmlValue				xml_value_t;
    /// Dynamic XML structure type.
    typedef XmlStructure			xml_automata_set_t;
    /// Dynamic XML automaton implementation type.
    typedef XmlAutomaton			xml_automaton_impl_t;
    /// Dynamic XML automaton type.
    typedef Element<XmlStructure, XmlAutomaton>	xml_automaton_t;

    /// Dynamic XML session type.
    typedef XmlSession				xml_session_t;

    /** @} */

  } // End of namespace xml.

} // End of namespace vcsn.

#endif // ! VCSN_XML_TYPES_HH
