// ios.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_IOS_HXX
# define VCSN_XML_IOS_HXX

# include <vaucanson/xml/ios.hh>

namespace vcsn
{
    namespace xml
    {
      unsigned
      BinCxxInputStream::readBytes (XMLByte *const toFill,
				    const unsigned int maxToRead)
      {
	// istream::readsome does not seem to work on SunOS
	unsigned s = _in->rdbuf()->sgetn((char *)toFill, maxToRead);
	_pos += s;
	return s;
      }

      unsigned int
      BinCxxInputStream::curPos() const
      {
	return _pos;
      }

      BinCxxInputStream*
      CxxInputSource::makeStream() const
      {
	return new BinCxxInputStream(_in);
      }
  }
}

#endif // ! VCSN_XML_IOS_HXX
