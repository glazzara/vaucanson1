#ifndef VCSN_XML_XML_VALUE_HH
# define VCSN_XML_XML_VALUE_HH

# include <vaucanson/design_pattern/element.hh>

# include <string>

namespace vcsn
{
  namespace xml
  {
    class XmlValue
    {
    protected:
      std::string v_;

    public:
      typedef std::string::iterator iterator;
      typedef std::string::const_iterator const_iterator;
      typedef std::string::reverse_iterator reverse_iterator;
      typedef std::string::const_reverse_iterator const_reverse_iterator;

      XmlValue() : v_("")
      {
      }

      XmlValue(const XmlValue& v) : v_(v.value())
      {
      }

      XmlValue(const std::string& v) : v_(v)
      {
      }

      template <typename T, typename V>
      XmlValue(const Element<T, V>& v);

      const std::string& value() const
      {
	return v_;
      }

      std::string& value()
      {
	return v_;
      }

      bool operator==(const XmlValue& v) const
      {
	return (this->v_ == v.value());
      }
    };

  }
}

# include <vaucanson/xml/xml_value.hxx>

#endif // VCSN_XML_XML_SET_HXX
