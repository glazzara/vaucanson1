#ifndef VCSN_XML_TYPES_HH
# define VCSN_XML_TYPES_HH

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concrete/graph.hh>

# include <vaucanson/xml/xml_automaton.hh>
# include <vaucanson/xml/xml_set.hh>

namespace vcsn
{
  namespace xml
  {
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

    typedef Element<XmlSet, XmlAutomaton> xml_automaton_t;
  }
}

#endif // VCSN_XML_TYPES_HH
