// error_handler.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
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

#endif // ! VCSN_XML_ERROR_HANDLER_HXX
