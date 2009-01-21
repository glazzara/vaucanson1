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

# _VCSN_CHECK_XML
# ---------------
AC_DEFUN([_VCSN_CHECK_XML],
[dnl
   # User-specified directory overrides any other definition
   if test "x$with_cv_xerces_dir" != x; then
      XERCES_EXTRA_CPPFLAGS="-I$with_cv_xerces_dir/include"
      XERCES_EXTRA_LDFLAGS="-L$with_cv_xerces_dir/lib"
   else
      XERCES_EXTRA_CPPFLAGS=''
      XERCES_EXTRA_LDFLAGS=''
    fi

   AC_LANG_PUSH([C++])

   AC_CACHE_CHECK([for previously found Xerces-C++ headers >= 2.3],
                  [vcsn_cv_xerces],
                  [vcsn_cv_xerces=unknown])
   if test x$vcsn_cv_xerces = xunknown; then
        vcsn_cv_xerces=no
        vcsn_save_CPPFLAGS=$CPPFLAGS
        CPPFLAGS="$CPPFLAGS $XERCES_EXTRA_CPPFLAGS"
        AC_CHECK_HEADER([xercesc/util/XercesVersion.hpp],
                        [AC_COMPILE_IFELSE([AC_LANG_SOURCE([
#include <xercesc/util/XercesVersion.hpp>
#if XERCES_VERSION_MAJOR < 2 || XERCES_VERSION_MAJOR > 3
# error "Bad Xerces-C++ major version."
#endif
#if XERCES_VERSION_MAJOR == 2 && XERCES_VERSION_MINOR < 3
# error "Bad Xerces-C++ minor version."
#endif
                                                      ])],
                                            [vcsn_cv_xerces=yes])])
      CPPFLAGS=$vcsn_save_CPPFLAGS
   fi

   if test x$vcsn_cv_xerces != xyes; then
      AC_ERROR([Xerces-C++ not found or not >= 2.3])
   fi

   AC_CACHE_CHECK([for usable Xerces-C++ library],
                  [vcsn_cv_xerces_lib],
                  [vcsn_cv_xerces_lib=no
                   vcsn_save_CPPFLAGS=$CPPFLAGS
                   vcsn_save_LDFLAGS=$LDFLAGS
                   vcsn_save_LIBS=$LIBS
                   CPPFLAGS="$CPPFLAGS $XERCES_EXTRA_CPPFLAGS"
                   LDFLAGS="$LDFLAGS $XERCES_EXTRA_LDFLAGS"
                   LIBS="$LIBS -lxerces-c"
                   AC_LINK_IFELSE([AC_LANG_SOURCE([
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>

/// The type used by Xerces-C++ for the file position type.
# if (XERCES_VERSION_MAJOR == 2)
#  define XMLSize_t unsigned int
#  define XERCES_FILEPOS XMLSize_t
# elif (XERCES_VERSION_MAJOR == 3)
#  define XERCES_FILEPOS XMLFilePos
# else
#  error "Bad Xerces-C++ major version."
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
                                  ])],
                                  [vcsn_cv_xerces_lib=yes])
                    LIBS=$vcsn_save_LIBS
                    LDFLAGS=$vcsn_save_LDFLAGS
                    CPPFLAGS=$vcsn_save_CPPFLAGS
                    ])

   if test x$vcsn_cv_xerces_lib != xyes; then
      AC_ERROR([cannot link with Xerces-C++ library])
   fi

   CPPFLAGS="$CPPFLAGS $XERCES_EXTRA_CPPFLAGS"
   LDFLAGS="$LDFLAGS $XERCES_EXTRA_LDFLAGS"
   LIBS="$LIBS -lxerces-c"

   AC_LANG_POP([C++])
])


# VCSN_XML
# --------
# Xerces C++
AC_DEFUN([VCSN_XML],
[dnl
  AC_CACHE_CHECK([for Xerces-C++ in user-specified directory],
                 [with_cv_xerces_dir],
		 [])
  AC_ARG_WITH([xerces],
              [AC_HELP_STRING([--with-xerces=DIR],
  		              [base directory where Xerces-C++ is installed])],
	      [with_cv_xerces_dir="$withval"],
	      [])
  _VCSN_CHECK_XML
])
