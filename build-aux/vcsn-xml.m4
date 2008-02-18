# vcsn-xml.m4					-*- Autoconf -*-
# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2005, 2006 The Vaucanson Group.
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
   if test "x$with_xerces" != x; then
      XERCES_EXTRA_CPPFLAGS="-I$with_xerces/include"
      XERCES_EXTRA_LDFLAGS="-L$with_xerces/lib"
   else
      XERCES_EXTRA_CPPFLAGS=''
      XERCES_EXTRA_LDFLAGS=''
      for ac_xerces_path_tmp in /usr /usr/local /opt /opt/local ; do
	if test -d "$ac_xerces_path_tmp/include/xercesc" && test -r "$ac_xerces_path_tmp/include/xercesc"; then
	  XERCES_EXTRA_LDFLAGS="-L$ac_xerces_path_tmp/lib"
	  XERCES_EXTRA_CPPFLAGS="-I$ac_xerces_path_tmp/include"
	  break;
	fi
      done
    fi

   AC_LANG_PUSH([C++])

   AC_CACHE_CHECK([for previously found Xerces-C++ headers >= 2.3],
                  [vcsn_cv_xerces],
                  [vcsn_cv_xerces=unknown])
   if test x$vcsn_cv_xerces = xunknown; then
        vcsn_cv_xerces=no
        vcsn_save_CPPFLAGS=$CPPFLAGS
        CPPFLAGS="$XERCES_EXTRA_CPPFLAGS $CPPFLAGS"
        AC_CHECK_HEADER([xercesc/util/XercesVersion.hpp],
                        [AC_COMPILE_IFELSE([AC_LANG_SOURCE([
#include <xercesc/util/XercesVersion.hpp>
#if XERCES_VERSION_MAJOR != 2
# error "Bad Xerces-C++ major version."
#endif
#if XERCES_VERSION_MINOR < 3
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
                   CPPFLAGS="$XERCES_EXTRA_CPPFLAGS $CPPFLAGS"
                   LDFLAGS="$XERCES_EXTRA_LDFLAGS $LDFLAGS"
                   LIBS="$LIBS -lxerces-c"
                   AC_LINK_IFELSE([AC_LANG_SOURCE([
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>

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

// Taken from vaucanson/xml/ios.h{h,xx}.
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
      unsigned int
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

   CPPFLAGS="$XERCES_EXTRA_CPPFLAGS $CPPFLAGS"
   LDFLAGS="$XERCES_EXTRA_LDFLAGS $LDFLAGS"
   LIBS="$LIBS -lxerces-c"

   AC_LANG_POP([C++])
])


# VCSN_XML
# --------
# Xerces C++
AC_DEFUN([VCSN_XML],
[dnl
  AC_CACHE_CHECK([for Xerces-C++ in user-specified directory],
                 [with_xerces],
                 [AC_ARG_WITH([xerces],
                              [AC_HELP_STRING([--with-xerces=DIR],
  		                         [base directory where Xerces-C++ is installed])])])

  _VCSN_CHECK_XML
])
