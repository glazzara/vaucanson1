# vcsn.m4                                     -*- Autoconf -*-
#
# Vaucanson, a generic library for finite state machines.  Copyright
# (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2011 The
# Vaucanson Group.
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
m4_pattern_forbid([^_?VCSN_])

# VCSN_PATH_LOCAL([RELATIVE-PATH-TO-VAUCANSON-SOURCES])
# -----------------------------------------------------
# Detect Vaucanson sources "near" the current source directory.
# Used in the Vaucanson distribution itself
# to instruct "configure" to use the bundled Vaucanson sources.
#
# User projects can use this macro to point their "configure" to a
# nonstandard Vaucanson sources location, by invoking it _before_ using
# AC_WITH_VCSN.
AC_DEFUN([VCSN_PATH_LOCAL],
[m4_if([$1], [], [vcsn_cv_local_src=no], [dnl
    AC_CACHE_CHECK([for Vaucanson sources in local distribution],
		   [vcsn_cv_local_src],
		   [vcsn_cv_local_src=no
		    if test -r "$srcdir/$1/include/vaucanson/config/system.hh"; then
		       vcsn_cv_local_src="$1"
		    fi])
])])


# VCSN_PATH_USER
# --------------
# Checks for the location of Vaucanson sources specified with the user
# with the flag --with-vcsn.
AC_DEFUN([VCSN_PATH_USER],
[dnl
  AC_CACHE_CHECK([for Vaucanson in user-specified directory],
		 [vcsn_cv_user_hint],
		 [vcsn_cv_user_hint=no
		  AC_ARG_WITH([vcsn],
		     [AC_HELP_STRING([--with-vcsn=DIR],
		     [Include directory where Vaucanson is installed (optional)])],
		     [if test -r "$withval/vaucanson/config/system.hh"; then
			vcsn_cv_user_hint=$withval
		      fi])])
])# VCSN_PATH_USER


# _VCSN_CHECK_HEADERS
# -------------------
# Internal macro used by VCSN_PATH_HEADERS.
# This macro checks the actual availability of Vaucanson headers after
# the other heuristics have tried setting VCSN_INCLUDE_DIR and CPPFLAGS.
AC_DEFUN([_VCSN_CHECK_HEADERS],
[dnl
 AC_REQUIRE([AC_PROG_CXX])
 AC_LANG_PUSH([C++])

 have_vaucanson=yes
 vcsn_save_CPPFLAGS=$CPPFLAGS
 CPPFLAGS="$vcsn_extra_CPPFLAGS $CPPFLAGS"
 # At this point, we can be in a situation where pconf.hh does not
 # exist _yet_. In that particular case, we need a workaround.
 AC_CHECK_HEADER([vaucanson/config/pconf.hh], [],
	  [CPPFLAGS="$CPPFLAGS -DVCSN_INTERNAL_IGNORE_PCONF_HH"])
 AC_CHECK_HEADER([vaucanson/config/system.hh], [], [have_vaucanson=no])
 CPPFLAGS=$vcsn_save_CPPFLAGS

 AC_LANG_POP([C++])
])# _VCSN_CHECK_HEADERS


# VCSN_PATH_HEADERS
# -----------------
# Find an Vaucanson location from various informations: availability of
# Vaucanson sources around the current source directory, user flags, environment
# variable.
#
# This macro sets, if needed, VCSN_CPPFLAGS before proceeding with
# _VCSN_CHECK_HEADERS.
AC_DEFUN([VCSN_PATH_HEADERS],
[dnl
  AC_REQUIRE([VCSN_PATH_LOCAL])
  AC_REQUIRE([VCSN_PATH_USER])

  # User-specified directory overrides any other definition
  if test "x$vcsn_cv_user_hint" != xno; then
     if test "x$VCSN_INCLUDE_DIR" != x ; then
       AC_MSG_WARN([using $vcsn_cv_user_hint instead of $VCSN_INCLUDE_DIR])
     fi
     VCSN_INCLUDE_DIR="$vcsn_cv_user_hint"
  else
    if test "x$vcsn_cv_local_src" != xno; then
      if test "x$VCSN_INCLUDE_DIR" != x ; then
	AC_MSG_WARN([using $vcsn_cv_user_src instead of $VCSN_INCLUDE_DIR])
      fi
      VCSN_INCLUDE_DIR=''

      # This is useful for sanity checks.
      AC_SUBST([VCSN_LOCAL_SRC],   ['$(top_srcdir)/'$vcsn_cv_local_src])
      AC_SUBST([VCSN_LOCAL_BUILD], ['$(top_builddir)/'$vcsn_cv_local_src])

      vcsn_extra_CPPFLAGS="-I$vcsn_cv_local_src/include -I$srcdir/$vcsn_cv_local_src/include"
    fi
  fi

  AC_ARG_VAR([VCSN_INCLUDE_DIR],
	     [location of Vaucanson (<include dir>, should be autodetected)])
  if test "x$VCSN_INCLUDE_DIR" != x ; then
     CPPFLAGS="-I$VCSN_INCLUDE_DIR $CPPFLAGS"
  fi
  AC_SUBST([VCSN_INCLUDE_DIR])

  _VCSN_CHECK_HEADERS
])


# AC_CXX_TEMPLATE_DEPTH
# ---------------------
# Check for deep template recursion upto MINIMUM-DEPTH.
#
# Automatically adds the flag `-ftemplate-depth' to VCSN_CXXFLAGS when :
# - deep template recursion is not available when it is not present
# - the compiler supports it
# - it provides the right effect when present
AC_DEFUN([AC_CXX_TEMPLATE_DEPTH],
[dnl
  AC_REQUIRE([AC_PROG_CXX])
  AC_LANG_PUSH([C++])

  cxx_tdepth=m4_if([$1], , 50, [$1])
  AC_CACHE_CHECK([for C++ template recursion upto $cxx_tdepth levels],
		 [cxx_cv_cxx_template_flags],
		 [cxx_cv_cxx_template_flags=direct
		  vcsn_save_CPPFLAGS=$CPPFLAGS
		  vcsn_save_CXXFLAGS=$CXXFLAGS
		  CPPFLAGS="$CPPFLAGS -DTDEPTH=$cxx_tdepth"
		  AC_LINK_IFELSE([AC_LANG_SOURCE([[template<unsigned n>
				  struct rec {
				     typedef typename rec<n-1>::ret ret;
				  };
				  template<> struct rec<0>
				  { typedef int ret; };
				  int main(void)
				  { rec<TDEPTH>::ret i = 0; return i; }]])],
		      [],
		      [CXXFLAGS="$CXXFLAGS -ftemplate-depth-$cxx_tdepth"
		       AC_LINK_IFELSE([AC_LANG_SOURCE([[template<unsigned n>
				       struct rec {
					   typedef typename rec<n-1>::ret ret;
				       };
				      template<> struct rec<0>
				      { typedef int ret; };
				      int main(void)
				      { rec<TDEPTH>::ret i = 0; return i; }]])],
		       [cxx_cv_cxx_template_flags="-ftemplate-depth-$cxx_tdepth"],
		       [cxx_cv_cxx_template_flags=unsupported])])
		  CPPFLAGS=$vcsn_save_CPPFLAGS
		  CXXFLAGS=$vcsn_save_CXXFLAGS])


  AC_LANG_POP([C++])

  case "$cxx_cv_cxx_template_flags" in
     unsupported )
       AC_MSG_WARN([C++ compiler does not handle template recursion upto $cxx_tdepth. Expect problems.])
       ;;
     direct ) ;;
     * )
       CXXFLAGS="$CXXFLAGS $cxx_cv_cxx_template_flags"
       ;;
  esac

])


# AC_CXX_NUMERIC_LIMITS
# ---------------------
# Checks for the availability of std::numeric_limits::infinity()
# from C++.
#
# This tests adds -DUSE_C_LIMITS to CPPFLAGS if the numeric
# limits are unavailable, in which case HUGE_VAL and HUGE_VALF are
# used instead by Vaucanson.
AC_DEFUN([AC_CXX_NUMERIC_LIMITS],
[dnl
  AC_REQUIRE([AC_PROG_CXX])
  AC_LANG_PUSH([C++])

  ### Vaucanson needs definitions for infinity values for the `float' and
  ### `double' data types, and max and min for integer data types.

  # In ISO C++98, these are provided by std::numeric_limits, declared
  # in header <limits>.

  AC_CHECK_HEADERS([limits])

  # Some old (and faulty) <limits> implementations define unusable
  # std::numeric_limits. Check it.

  AC_CACHE_CHECK([for proper std::numeric_limits in <limits>],
		 [cxx_cv_have_numeric_limits],
		 [if test x$ac_cv_header_limits != xno; then
		     AC_TRY_LINK([@%:@include <limits>
				  template<bool b> struct sif {};
				  template<> struct sif<true> { int a; };],
				 [float f1 =
				     std::numeric_limits<float>::infinity();
				  double f2 =
				     std::numeric_limits<double>::infinity();
				  sif<std::numeric_limits<float>::has_infinity> i1;
				  sif<std::numeric_limits<double>::has_infinity> i2;
				  i1.a = std::numeric_limits<int>::min();
				  i2.a = std::numeric_limits<int>::max();],
			 [cxx_cv_have_numeric_limits=yes],
			 [cxx_cv_have_numeric_limits=no])
		  else
		     cxx_cv_have_numeric_limits=no
		  fi])


  if test x$cxx_cv_have_numeric_limits = xno; then
     # Usable std::numeric_limits were *not* found in <limits>.
     CPPFLAGS="-DUSE_C_LIMITS $CPPFLAGS"
  fi

  AC_LANG_POP([C++])
])


# AC_CXX_CHECK_MATH([FUNCTION], [MACRO_NAME], [TEST])
# ---------------------------------------------------
# Checks for the availability of a particular math function
# from C++.
#
# This test attempts to use the function without flags
# at first, then with -D_ISOC99_SOURCE which is known to
# activate C99 declarations in the GNU libc headers.
# If the latter works, the flag is added to CPPFLAGS.
# In the default case, it adds -DNEED_XXX to
# CPPFLAGS, hoping that config/math.hh will provide
# an implementation.
AC_DEFUN([AC_CXX_CHECK_MATH],
[dnl
  AC_REQUIRE([AC_PROG_CXX])
  AC_LANG_PUSH([C++])
  AC_CACHE_CHECK([for flags to enable $1() from C++],
		 [cxx_cv_$1_flags],
		 [cxx_save_CPPFLAGS=$CPPFLAGS
		  AC_LINK_IFELSE([AC_LANG_SOURCE([[@%:@include <cmath>
				  int main() { $3 }]])],
				 [cxx_cv_$1_flags=unneeded],
				 [CPPFLAGS="$CPPFLAGS -D_ISOC99_SOURCE=1"
				  AC_LINK_IFELSE(
                                       [AC_LANG_SOURCE([[@%:@include <cmath>
							 int main() { $3 }]])],
				       [cxx_cv_$1_flags=isodef],
				       [cxx_cv_$1_flags=redef])])
		  CPPFLAGS=$cxx_save_CPPFLAGS])
  if test "x$[]cxx_cv_$1_flags" = xredef; then
     CPPFLAGS="$CPPFLAGS -DNEED_$2"
  elif test "x$[]cxx_cv_$1_flags" = xisodef; then
     CPPFLAGS="$CPPFLAGS -D_ISOC99_SOURCE=1"
  fi
  AC_LANG_POP([C++])
])


AC_DEFUN([AC_CXX_FLOAT_MATH],
[dnl
  AC_CXX_CHECK_MATH([sqrtf], [SQRTF], [float f = sqrtf(0.1f);])
  AC_CXX_CHECK_MATH([floorf], [FLOORF], [float f = floorf(0.1f);])
  AC_CXX_CHECK_MATH([round], [ROUND], [double f = round(0.1);])
  AC_CXX_CHECK_MATH([roundf], [ROUNDF], [float f = roundf(0.1f);])
])


# AC_WITH_VCSN
# ------------
# Invoke configuration code to test for Vaucanson and set a collection
# of appropriate flags.
AC_DEFUN([AC_WITH_VCSN],
[dnl
  AC_REQUIRE([AC_CXX_TEMPLATE_DEPTH])
  AC_REQUIRE([AC_CXX_NUMERIC_LIMITS])
  AC_REQUIRE([AC_CXX_FLOAT_MATH])
  AC_REQUIRE([VCSN_PATH_HEADERS])
])
