# AC_WITH_CXX_ZLIB

# Checks for availability of Zlib from C++ programs.

# This macro sets ZLIB_CXXFLAGS and ZLIB_LDFLAGS if the library is
# found and its functions available from C++.

AC_DEFUN([AC_WITH_CXX_ZLIB],
[dnl
 AC_REQUIRE([AC_PROG_CXX])
 AC_LANG_PUSH([C++])

 AC_ARG_WITH([zlib],
             [AC_HELP_STRING([--with-zlib@<:@=DIR@:>@], 
                    [using zlib (DIR = prefix for zlib installation)])])
 ZLIB_CXXFLAGS=''
 ZLIB_LDFLAGS=''
 if test "x$with_zlib" != xno; then
   if test -n "$with_zlib"; then
     ZLIB_CXXFLAGS="-I${with_zlib}/include"
     ZLIB_LDFLAGS="-L${with_zlib}/lib"
   fi
   oln_save_CXXFLAGS=$CXXFLAGS
   oln_save_LDFLAGS=$LDFLAGS
   CXXFLAGS="$CXXFLAGS $ZLIB_CXXFLAGS"
   LDFLAGS="$LDFLAGS $ZLIB_LDFLAGS"
   oln_have_zlib=no
   AC_CHECK_HEADER([zlib.h],
                   [AC_CHECK_LIB([z], 
                               [gzopen],
                               [oln_have_zlib=yes
                                ZLIB_LDFLAGS="$ZLIB_LDFLAGS -lz"
                                AC_DEFINE([HAVE_ZLIB], 1, 
                                          [Define to 1 if we can use zlib])])])
   CXXFLAGS=$oln_save_CXXFLAGS
   LDFLAGS=$oln_save_LDFLAGS
 fi
 AC_SUBST([ZLIB_CXXFLAGS])
 AC_SUBST([ZLIB_LDFLAGS])

 AC_LANG_POP([C++])
])
