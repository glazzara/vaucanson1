#ifndef VCSN_XML_ERROR_HANDLER_HXX
# define VCSN_XML_ERROR_HANDLER_HXX

# include <vaucanson/xml/error_handler.hh>

# include <iostream>

namespace vcsn
{
  namespace xml
  {
    inline
    std::string
    myDOMErrorHandler::get_msg() const
    {
      return message;
    }

    inline
    myDOMErrorHandler::myDOMErrorHandler(const myDOMErrorHandler& c)
      : DOMErrorHandler()
    {
      message = c.get_msg();
      error_ = c.has_error();
    }

    inline
    bool
    myDOMErrorHandler::has_error() const
    {
      return error_;
    }

    inline
    bool
    myDOMErrorHandler::handleError(const xercesc::DOMError& err)
    {
      using namespace xercesc;
      std::string msg;

      const XMLCh* uri = err.getLocation()->getURI();
      if (uri) {
	char* str = XMLString::transcode(uri);
	msg += str;
	XMLString::release(&str);
	msg += ": ";
      }

      std::ostringstream lo;
      lo << (int)(err.getLocation()->getLineNumber());
      msg += lo.str();
      msg += ", ";
      std::ostringstream co;
      co << (int)(err.getLocation()->getColumnNumber());
      msg += co.str();
      msg += ": ";
      const XMLCh* reason = err.getMessage();
      if (reason) {
	char* str = XMLString::transcode(reason);
	msg += str;
	XMLString::release(&str);
      }
      else
	msg += "no reason";

      if (err.getSeverity() == xercesc::DOMError::DOM_SEVERITY_WARNING) {
	std::cerr << msg << std::endl;
	return true;
      }
      message = msg;

      error_ = true;
      return false;
    }
  }
}

#endif // VCSN_XML_ERROR_HANDLER_HXX
