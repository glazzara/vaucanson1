#ifndef VCSN_XML_XML_SET_HH
# define VCSN_XML_XML_SET_HH

# include <vaucanson/design_pattern/structure.hh>

# include <xercesc/dom/DOM.hpp>

/** @addtogroup xml XML tools for Vaucanson *//** @{ */
/**
 * @file xml_set.hh
 * @brief XML automaton set tools.
 * @author Valentin David <valentin@lrde.epita.fr>
 */

namespace vcsn
{
  namespace xml
  {
    using namespace xercesc;

    /// XML automaton set. Just for loading.
    class XmlSet : public Structure<XmlSet>
    {
    public:
      /// Type values.
      enum { UNSET, UNKNOWN,
	     LETTERS, B, Z, R, WORDS,
	     NUMERICAL, TROPICAL_MIN, TROPICAL_MAX };
      /**
       * @brief Read constructor.
       * @param elt XML automaton root node.
       */
      XmlSet(DOMElement* elt);
      /// Default constructor.
      XmlSet();
      XmlSet(const XmlSet&);

      /// Check semiring type (NUMERICAL, TROPICAL_MIN, TROPICAL_MAX).
      int semiring_type() const;
      /// Check semiring set (B, Z, R, WORDS).
      int semiring_set() const;
      /// Check monoid type (LETTERS).
      int monoid_type() const;
      /// Check monoid set (WORDS).
      int monoid_set() const;

      const DOMNode*	monoid_alphabet() const;
      const DOMNode*	semiring_alphabet() const;
    private:
      DOMElement*	monoid_node_;
      DOMElement*	semiring_node_;
    };
  }

  template <typename T>
  struct MetaElement<xml::XmlSet, T>
    : public MetaElement<Structure<xml::XmlSet>, T>
  { };

  template <>
  struct dynamic_traits<xml::XmlSet> {
    static const bool ret = true;
  };
}

/** @} */

# include <vaucanson/xml/xml_set.hxx>

#endif // VCSN_XML_XML_SET_HH
