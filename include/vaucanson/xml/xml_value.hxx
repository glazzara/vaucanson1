#ifndef VCSN_XML_XML_VALUE_HXX
# define VCSN_XML_XML_VALUE_HXX

# include <vaucanson/xml/xml_value.hh>

namespace vcsn {
  namespace xml {
    template <typename T, typename V>
    inline
    XmlValue::XmlValue(const Element<T, V>& v)
    {
      *this = op_convert(v.set(), SELECT(XmlValue), v.value());
    }
  }
}

#endif // VCSN_XML_XML_VALUE_HXX
