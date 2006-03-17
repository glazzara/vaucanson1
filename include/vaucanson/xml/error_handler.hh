// error_handler.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_ERROR_HANDLER_HH
# define VCSN_XML_ERROR_HANDLER_HH

#include <vaucanson/config/system.hh>
#ifndef VCSN_USE_XML
# error Vaucanson XML support is disabled.
#endif

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

#endif // ! VCSN_XML_ERROR_HANDLER_HH
