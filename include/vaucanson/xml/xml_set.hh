#ifndef VCSN_XML_XML_SET_HH
# define VCSN_XML_XML_SET_HH

# include <vaucanson/design_pattern/structure.hh>

# include <xercesc/dom/DOM.hpp>

namespace vcsn
{
  namespace xml
  {
    using namespace xercesc;

    class XmlSet : public Structure<XmlSet>
    {
    public:
      enum { UNSET, UNKNOWN,
	     LETTERS, B, Z, R, WORDS,
	     NUMERICAL, TROPICAL_MIN, TROPICAL_MAX };
      XmlSet(DOMElement*);
      XmlSet();
      XmlSet(const XmlSet&);

      int semiring_type() const;
      int semiring_set() const;
      int monoid_type() const;
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

# include <vaucanson/xml/xml_set.hxx>

#endif // VCSN_XML_XML_SET_HH
