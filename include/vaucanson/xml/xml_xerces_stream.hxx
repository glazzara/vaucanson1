// xml_xerces_stream.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#ifndef XML_XERCES_STREAM_HXX
# define XML_XERCES_STREAM_HXX

/**
 * @file xml_xerces_stream.hxx
 *
 * Provide a streaming support for the Xerces DomWriter.
 * Follow Xerces Specifications.
 *
 * @author Florian Lesaint <lesaint@lrde.epita.fr>
 */

XERCES_CPP_NAMESPACE_BEGIN

template<class Ostream>
void
XMLPARSER_EXPORT
XMLXercesStream<Ostream>::writeChars (const XMLByte* const toWrite,
				      const unsigned int,
				      XMLFormatter* const)
{
  os_ << toWrite;
};

XERCES_CPP_NAMESPACE_END

#endif // !XML_XERCES_STREAM_HXX
