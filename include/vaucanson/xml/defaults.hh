#ifndef VCSN_XML_DEFAULTS_HH
# define VCSN_XML_DEFAULTS_HH

# include <xercesc/dom/DOM.hpp>

# define XML_BEGIN xercesc::XMLPlatformUtils::Initialize()
# define XML_END xercesc::XMLPlatformUtils::Terminate()

# include <vaucanson/xml/types.hh>
# include <vaucanson/xml/errors.hh>
# include <vaucanson/xml/xml_ops.hh>

#endif // VCSN_XML_DEFAULTS_HH
