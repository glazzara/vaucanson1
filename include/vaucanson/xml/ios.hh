// ios.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_XML_IOS_HH
# define VCSN_XML_IOS_HH

# include <xercesc/util/BinInputStream.hpp>
# include <xercesc/sax/InputSource.hpp>
# include <iostream>

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
	virtual unsigned int curPos() const;
	virtual unsigned readBytes (XMLByte *const toFill,
				    const unsigned int maxToRead);
      };

      class CxxInputSource : public xercesc::InputSource
      {
      private:
	std::istream* _in;

      public:
	CxxInputSource(std::istream* in) : InputSource(), _in(in) {}
	virtual BinCxxInputStream* makeStream() const;
      };
    }
}

# include <vaucanson/xml/ios.hxx>

#endif // ! VCSN_XML_IOS_HH
