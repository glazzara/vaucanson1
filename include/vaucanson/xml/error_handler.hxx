// error_handler.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
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
