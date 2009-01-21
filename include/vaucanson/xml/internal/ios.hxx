// ios.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_INTERNAL_IOS_HXX
# define VCSN_XML_INTERNAL_IOS_HXX

# include <vaucanson/xml/internal/ios.hh>

XERCES_CPP_NAMESPACE_BEGIN

template<class Ostream>
void
XMLPARSER_EXPORT
XMLXercesStream<Ostream>::writeChars(const XMLByte* const toWrite,
				     const XMLSize_t,
				     XMLFormatter* const)
{
  os_ << toWrite;
}

XERCES_CPP_NAMESPACE_END

namespace vcsn
{
  namespace xml
  {
    inline
    XMLSize_t
    BinCxxInputStream::readBytes(XMLByte *const toFill,
				 const XMLSize_t maxToRead)
    {
      // istream::readsome does not seem to work on SunOS
      unsigned s = _in->rdbuf()->sgetn((char *)toFill, maxToRead);
      _pos += s;
      return s;
    }

    inline
    XERCES_FILEPOS
    BinCxxInputStream::curPos() const
    {
      return _pos;
    }

    inline
    BinCxxInputStream*
    CxxInputSource::makeStream() const
    {
      return new BinCxxInputStream(_in);
    }

    void
    print_xml(std::ostream& out,
	      xercesc::DOMImplementation* impl,
	      xercesc::DOMElement* root)
    {
      using namespace xercesc;

      XMLXercesStream<std::ostream>* outstream = new XMLXercesStream<std::ostream>(out);

# if XERCES_VERSION_MAJOR == 2
      DOMWriter* writer = impl->createDOMWriter();

      if (writer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
	writer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);

      writer->writeNode(outstream, *root);
# elif XERCES_VERSION_MAJOR > 2
      DOMLSSerializer* writer = impl->createLSSerializer();
      DOMLSOutput *target = impl->createLSOutput();
      target->setByteStream(outstream);
      DOMConfiguration *config = writer->getDomConfig();

      if (config->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
	config->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

      writer->write(root, target);
# else
#  error "Unsupported Xerces-C++ major version (too old)."
# endif

      writer->release();

      delete outstream;
    }

  } // ! xml

} // ! vcsn

#endif // ! VCSN_XML_INTERNAL_IOS_HXX
