#ifndef VCSN_XML_STRINGS_HH
# define VCSN_XML_STRINGS_HH
# include <xercesc/util/XMLUniDefs.hpp>
# include <xercesc/util/XMLString.hpp>

# include <string>

namespace vcsn
{
  namespace xml
  {
    using namespace xercesc;

    std::string
    xml2str(const XMLCh*);

# include <vaucanson/xml/xmlstrings.inc>
  }
}

# include <vaucanson/xml/strings.hxx>

#endif // VCSN_XML_STRINGS_HH
