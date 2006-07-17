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

   AC_CACHE_CHECK([for useable Xerces-C++ library],
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

int main() {
  const char *foo = "foo";
  using namespace xercesc;
  XMLCh* bar = XMLString::transcode(foo);
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
  AC_ARG_ENABLE([xml],
                [AC_HELP_STRING([--disable-xml],
                  [disable XML support in Vaucanson (needs Xerces-C++ >= 2.3)])],
                [enable_vcsn_xml=$enableval],
                [enable_vcsn_xml=yes])

  AC_CACHE_CHECK([for Xerces-C++ in user-specified directory],
                 [with_xerces],
                 [AC_ARG_WITH([xerces],
                              [AC_HELP_STRING([--with-xerces=DIR],
  		                         [base directory where Xerces-C++ is installed])])])

  AC_ARG_ENABLE([xml-tests],
                [AC_HELP_STRING([--disable-xml-tests],
		   [disable tests of XML features])],
                [],
                [enable_xml_tests=yes])

  if test x$enable_vcsn_xml = xyes; then
     _VCSN_CHECK_XML
  else
     enable_xml_tests=no
  fi
  if test x$enable_vcsn_xml = xyes; then
    AC_DEFINE([VCSN_USE_XML], 1, [Define to 1 if you want to use XML I/O.])
  fi
  AM_CONDITIONAL([VCSN_USE_XML], [test x$enable_vcsn_xml = xyes])

  AM_CONDITIONAL([XML_CHECK], [test x$enable_xml_tests = xyes])
])
