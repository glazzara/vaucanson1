// xml_xerces_stream.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XERCES_STREAM_HH
# define VCSN_XML_XERCES_STREAM_HH

/**
 * @file xml_xerces_stream.hh
 *
 * Provide a streaming support for the Xerces DomWriter.
 * Follow Xerces Specifications.
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <ostream>
# include <xercesc/framework/XMLFormatter.hpp>

XERCES_CPP_NAMESPACE_BEGIN

template<class Ostream>
class XMLPARSER_EXPORT XMLXercesStream : public XMLFormatTarget
{
  public:

    /** @name constructors and destructor */
    //@{
    XMLXercesStream(std::ostream& os) : os_(os) {};
    ~XMLXercesStream() {};
    //@}

    /**
     * @brief Implementations of the format target interface
     */
    virtual void writeChars (const XMLByte* const toWrite,
			     const unsigned int,
			     XMLFormatter* const);

    virtual void flush() {};

  private:
    /**
     * @brief Unimplemented methods (should never be used)
     */
    XMLXercesStream(const XMLXercesStream&);
    XMLXercesStream& operator=(const XMLXercesStream&);

    Ostream&	os_;
};

XERCES_CPP_NAMESPACE_END

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/xml_xerces_stream.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // ! VCSN_XML_XERCES_STREAM_HH
