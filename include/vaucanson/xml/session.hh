#ifndef VCSN_XML_SESSION_HH
# define VCSN_XML_SESSION_HH

# include <vaucanson/xml/dynamic.hh>
# include <vaucanson/xml/error_handler.hh>
# include <vaucanson/xml/xml_automaton.hh>
# include <vaucanson/xml/xml_set.hh>
# include <vaucanson/automata/concept/automata_base.hh>

# include <xercesc/util/PlatformUtils.hpp>
# include <xercesc/dom/DOM.hpp>

# include <list>

/** @addtogroup xml XML tools for Vaucanson *//** @{ */
/**
 * @file session.hh
 * @brief XML sessions tools.
 * @author Valentin David <valentin@lrde.epita.fr>
 */

namespace vcsn
{
  namespace xml
  {
    using namespace xercesc;

    /// Session handler.
    class XmlSession
    {
    public:
      DOMDocument* doc_;
      myDOMErrorHandler* err_;
      DOMBuilder* parser_;
      std::list<DOMElement*> roots_;
    public:
      /// Default constructor.
      XmlSession();
      ~XmlSession();

      //      template <typename T>
      /// Pop operator.
      void operator<<(const XmlAutomaton&);
      /// Queue operator.
      void operator>>(Element<XmlSet, XmlAutomaton>&);
    };

  }

  template<typename S>
  xml::XmlSession& op_rout(const AutomataBase<S>&,
			   xml::XmlSession&,
			   const xml::XmlAutomaton&);

  /// Read operator.
  std::ostream&
  operator<<(std::ostream&, const xml::XmlSession&);
  /// Write operator.
  std::istream&
  operator>>(std::istream&, xml::XmlSession&);
}

/** @} */

# include <vaucanson/xml/session.hxx>

#endif // VCSN_XML_SESSION_HH
