#ifndef VCSN_XML_TYPES_HH
# define VCSN_XML_TYPES_HH

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concrete/graph.hh>

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
