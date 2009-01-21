// ios.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2008, 2009 The Vaucanson Group.
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

#ifndef VCSN_XML_INTERNAL_IOS_HH
# define VCSN_XML_INTERNAL_IOS_HH

/**
 * @file ios.hh
 *
 * Functions required by the Xerces-C parser to manage streams.
 *
 * @see xml::Parser
 */

# include <iostream>

# include <xercesc/dom/DOM.hpp>
# include <xercesc/util/BinInputStream.hpp>
# include <xercesc/sax/InputSource.hpp>
# include <xercesc/framework/XMLFormatter.hpp>

/// The type used by Xerces-C++ for the file position type.
# if (XERCES_VERSION_MAJOR == 2)
#  define XMLSize_t unsigned int
#  define XERCES_FILEPOS XMLSize_t
# elif (XERCES_VERSION_MAJOR > 2)
#  define XERCES_FILEPOS XMLFilePos
# else
#  error "Unsupported Xerces-C++ major version (too old)."
# endif

XERCES_CPP_NAMESPACE_BEGIN

/**
 * Provide a streaming support for the Xerces DomWriter.
 * Follow Xerces Specifications.
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

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
  virtual void writeChars(const XMLByte* const toWrite,
			  const XMLSize_t,
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

namespace vcsn
{
  namespace xml
  {
    class BinCxxInputStream : public xercesc::BinInputStream
    {
    private:
      std::istream* _in;
      unsigned int _pos;

    public:
      BinCxxInputStream(std::istream* in) : _in(in), _pos(0) { }
      virtual XERCES_FILEPOS curPos() const;
      virtual XMLSize_t readBytes(XMLByte *const toFill,
				  const XMLSize_t maxToRead);
      virtual const XMLCh* getContentType () const { return 0; }
    };

    class CxxInputSource : public xercesc::InputSource
    {
    private:
      std::istream* _in;

    public:
      CxxInputSource(std::istream* in) : InputSource(), _in(in) {}
      virtual BinCxxInputStream* makeStream() const;
    };

    void print_xml(std::ostream& out,
		   xercesc::DOMImplementation* impl,
		   xercesc::DOMElement* root);

  } // ! xml

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/xml/internal/ios.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // ! VCSN_XML_IOS_HH
