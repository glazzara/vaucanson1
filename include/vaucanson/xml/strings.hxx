#ifndef VCSN_XML_STRINGS_HXX
# define VCSN_XML_STRINGS_HXX

# include <vaucanson/xml/strings.hh>
# include <cassert>

namespace vcsn
{
  namespace xml
  {
    inline
    std::string
    xml2str(const XMLCh* xmlstr)
    {
      assert(xmlstr != NULL);
      char* cstr = xercesc::XMLString::transcode(xmlstr);
      assert(cstr != NULL);
      std::string ret = cstr;
      xercesc::XMLString::release(&cstr);
      return ret;
    }
  }
}

#endif // VCSN_XML_STRINGS_HXX

