#ifndef VCSN_XML_ERROR_HANDLER_HH
# define VCSN_XML_ERROR_HANDLER_HH

# include <xercesc/util/PlatformUtils.hpp>
# include <xercesc/dom/DOM.hpp>

# include <sstream>

namespace vcsn
{
  namespace xml
  {
    struct myDOMErrorHandler : public xercesc::DOMErrorHandler
    {
    protected:
      std::string message;
      bool error_;
    public:
      myDOMErrorHandler() : DOMErrorHandler(), message(), error_(false) { };
      myDOMErrorHandler(const myDOMErrorHandler& c);
      std::string get_msg() const;
      bool has_error() const;
      virtual bool handleError(const xercesc::DOMError& err);
    };
  }
}

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/error_handler.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_XML_ERROR_HANDLER_HH
