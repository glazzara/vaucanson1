# vcsn-xml.m4					-*- Autoconf -*-
# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2005, 2006, 2009 The Vaucanson Group.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# The complete GNU General Public Licence Notice can be found as the
# `COPYING' file in the root directory.
#
# The Vaucanson Group consists of people listed in the `AUTHORS' file.

AC_PREREQ([2.60])

# VCSN_XML(MAJOR, MINOR)
# ----------------------
AC_DEFUN([VCSN_XML], [
   AC_LANG_PUSH([C++])

   AC_CHECK_HEADER([xercesc/util/XercesVersion.hpp],, [AC_MSG_ERROR([
Cannot find Xerces-C++ headers.  If they are installed on an unusuall path on
your system, please run configure with the suitable CPPFLAGS and LDFLAGS
options.  For instance if it is installed in /opt/xerces/ please use:

  ./configure CPPFLAGS="-I/opt/xerces/include" LDFLAGS="-L/opt/xerces/lib"
])])
   AC_CACHE_CHECK([whether Xerces-C++ version is >= $1.$2],
                  [vcsn_cv_xerces_recent],
 		  [AC_COMPILE_IFELSE([AC_LANG_SOURCE([[
#include <xercesc/util/XercesVersion.hpp>
#if XERCES_VERSION_MAJOR < $1
# error "Unsupported Xerces-C++ major version (too old)."
#endif
#if XERCES_VERSION_MAJOR == $1 && XERCES_VERSION_MINOR < $2
# error "Unsupported Xerces-C++ minor version (too old)."
#endif
]])],
	            [vcsn_cv_xerces_recent=yes],
		    [vcsn_cv_xerces_recent=no])])

   if test x$vcsn_cv_xerces_recent != xyes; then
      AC_MSG_ERROR([Xerces-C++ appears to be too old.  We need version $1.$2 or more recent])
   fi

   AC_CACHE_CHECK([for usable Xerces-C++ library],
                  [vcsn_cv_xerces_lib],
                  [vcsn_save_LIBS=$LIBS
                   LIBS="$LIBS -lxerces-c"
                   AC_COMPILE_IFELSE([AC_LANG_SOURCE([[
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>

/// The type used by Xerces-C++ for the file position type.
# if (XERCES_VERSION_MAJOR == $1)
#  define XMLSize_t unsigned int
#  define XERCES_FILEPOS XMLSize_t
# elif (XERCES_VERSION_MAJOR >= $2)
#  define XERCES_FILEPOS XMLFilePos
# else
#  error "Unsupported Xerces-C++ major version."
# endif

int main() {
  const char *foo = "foo";
  using namespace xercesc;
  XMLCh* bar = XMLString::transcode(foo);
}

/* Check libxerces-x C++ ABI.

   When a C++ piece of Vaucanson, compiled with G++ 4.0, is linked
   against libxerces-c, compiled with G++ 3.3 (which is the case
   with Fink on Mac OS X Tiger (10.3) / Xcode 1.5), the linker
   complains about undefined symbols of typeinfo's.  (This is a
   simplistic test, but this should be enough to check the C++ ABI).
*/
#include <iostream>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>

// Taken from vaucanson/xml/internal/ios.h{h,xx}.
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
	virtual unsigned readBytes (XMLByte *const toFill,
				    const unsigned int maxToRead);
      };

      inline
      unsigned
      BinCxxInputStream::readBytes (XMLByte *const toFill,
				    const unsigned int maxToRead)
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
    }
}
                                  ]])],
                                  [vcsn_cv_xerces_lib=yes],
				  [vcsn_cv_xerces_lib=no])
                    LIBS=$vcsn_save_LIBS
                    ])

   if test x$vcsn_cv_xerces_lib != xyes; then
      AC_MSG_ERROR([cannot link with Xerces-C++ library (do you need to set LDFLAGS?)])
   fi

   LIBS="$LIBS -lxerces-c"

   AC_LANG_POP([C++])
])
