# vcsn.m4
# $Id$

# VCSN_PATH_LOCAL([RELATIVE-PATH-TO-VAUCANSON-SOURCES])

# Tries to detect Vaucanson sources "near" the current source directory.
# This macro is noticeably used in the Vaucanson distribution itself
# to instruct "configure" to use the bundled Vaucanson sources.

# User projects can use this macro to point their "configure" to a 
# nonstandard Vaucanson sources location, by invoking it _before_ using
# AC_WITH_VCSN. 

AC_DEFUN([VCSN_PATH_LOCAL],
[ifelse([$1], [], [vcsn_cv_local_src=no], [dnl
    AC_CACHE_CHECK([for Vaucanson sources in local distribution],
                   [vcsn_cv_local_src],
	           [vcsn_cv_local_src=no
                    if test -r "$srcdir/$1/include/vaucanson/config/system.hh"; then
                       vcsn_cv_local_src="$1"
                    fi])
])])

# VCSN_PATH_USER

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
])

# _VCSN_CHECK_HEADERS

# Internal macro used by VCSN_PATH_HEADERS.
# This macro checks the actual availability of Vaucanson headers after
# the other heuristics have tried setting VCSN_INCLUDE_DIR and CPPFLAGS.

AC_DEFUN([_VCSN_CHECK_HEADERS], 
[dnl
 AC_REQUIRE([AC_PROG_CXX])
 AC_LANG_PUSH([C++])

 have_vaucanson=yes
 vcsn_save_CPPFLAGS=$CPPFLAGS
 CPPFLAGS="$VCSN_EXTRA_CPPFLAGS $CPPFLAGS"
 # At this point, we can be in a situation where pconf.hh does not
 # exist _yet_. In that particular case, we need a workaround.
 AC_CHECK_HEADER([vaucanson/config/pconf.hh], [], 
          [CPPFLAGS="$CPPFLAGS -DIGNORE_PCONF_HH"])
 AC_CHECK_HEADER([vaucanson/config/system.hh], [], [have_vaucanson=no])
 CPPFLAGS=$vcsn_save_CPPFLAGS

 AC_LANG_POP([C++])
])

# VCSN_PATH_HEADERS

# Find an Vaucanson location from various informations: availability of
# Vaucanson sources around the current source directory, user flags, environment
# variable.

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
      VCSN_LOCAL_SRC='$(top_srcdir)/'$vcsn_cv_local_src
      VCSN_LOCAL_BUILD='$(top_builddir)/'$vcsn_cv_local_src

      #
      VCSN_EXTRA_CPPFLAGS="-I$vcsn_cv_local_src/include -I$srcdir/$vcsn_cv_local_src/include"

      AC_SUBST([VCSN_LOCAL_SRC])
      AC_SUBST([VCSN_LOCAL_BUILD])
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

# Check for deep template recursion upto MINIMUM-DEPTH.

# Automatically adds the flag `-ftemplate-depth' to VCSN_CXXFLAGS when :
# - deep template recursion is not available when it is not present
# - the compiler supports it 
# - it provides the right effect when present

AC_DEFUN([AC_CXX_TEMPLATE_DEPTH],
[dnl
  AC_REQUIRE([AC_PROG_CXX])
  AC_LANG_PUSH([C++])

  cxx_tdepth=ifelse([$1], , 50, [$1])
  AC_CACHE_CHECK([for C++ template recursion upto $cxx_tdepth levels],
                 [cxx_cv_cxx_template_flags],
                 [cxx_cv_cxx_template_flags=direct
                  vcsn_save_CPPFLAGS=$CPPFLAGS
                  vcsn_save_CXXFLAGS=$CXXFLAGS
                  CPPFLAGS="$CPPFLAGS -DTDEPTH=$cxx_tdepth"
                  AC_LINK_IFELSE([template<unsigned n> 
				  struct rec { 
			             typedef typename rec<n-1>::ret ret; 
                                  };
                                  template<> struct rec<0> 
                                  { typedef int ret; };
                                  int main(void) 
                                  { rec<TDEPTH>::ret i = 0; return i; }], 
                      [], 
                      [CXXFLAGS="$CXXFLAGS -ftemplate-depth-$cxx_tdepth"
                       AC_LINK_IFELSE([template<unsigned n> 
                                       struct rec { 
                                           typedef typename rec<n-1>::ret ret;
                                       };
                                      template<> struct rec<0> 
                                      { typedef int ret; };
                                      int main(void) 
                                      { rec<TDEPTH>::ret i = 0; return i; }],
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

## The following macro (AC_CXX_EXCEPTIONS) is courtesy
## Luc Maisonobe, extracted from the Autoconf Macro Repository

# AC_CXX_EXCEPTIONS

# Checks whether the current C++ compiler configuration supports
# exceptions. It can be used to e.g. abort configure if exceptions
# are disabled (-fdisable-exceptions in CXXFLAGS or the like),
# instead of waiting for compilation errors.

AC_DEFUN([AC_CXX_EXCEPTIONS],
[dnl
  AC_CACHE_CHECK([whether the compiler supports exceptions],
                 [cxx_cv_cxx_exceptions],
                 [AC_REQUIRE([AC_PROG_CXX])
                  AC_LANG_PUSH([C++])
                  AC_COMPILE_IFELSE([try { throw 1; } 
                                     catch (int i) { return i; }],
			            [cxx_cv_cxx_exceptions=yes],
				    [cxx_cv_cxx_exceptions=no])
		  AC_LANG_POP([C++])])
  if test "$cxx_cv_cxx_exceptions" = yes; then
     AC_DEFINE([HAVE_EXCEPTIONS], 1, 
               [define if the compiler supports exceptions])
  fi
])

# AC_CXX_NUMERIC_LIMITS

# Checks for the availability of std::numeric_limits::infinity()
# from C++.

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

# Checks for the availability of a particular math function
# from C++.

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
                  AC_LINK_IFELSE([@%:@include <cmath>
                                  int main() { $3 }],
                                 [cxx_cv_$1_flags=unneeded],
                                 [CPPFLAGS="$CPPFLAGS -D_ISOC99_SOURCE=1"
                                  AC_LINK_IFELSE([@%:@include <cmath>
                                                  int main() { $3 }],
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

# AC_CXX_FLAGS

# Attempts to recognize specific compilers to set, if availables, extra
# flags for debugging, optimization and strict conformance to language
# specifications.

# This macro checks for the following compilers :
#   - GNU C++ (g++)
#   - Sun WorkShop C++ (Sun/CC)
#   - Intel C++ (icc)
#   - Comeau C++ (como)
# and sets the following autoconf variables:
#   CXXFLAGS_DEBUG
#   CXXFLAGS_STRICT
#   CXXFLAGS_STRICT_ERRORS
#   CXXFLAGS_OPTIMIZE

AC_DEFUN([AC_CXX_FLAGS],
[dnl
   AC_REQUIRE([AC_PROG_CXX])
   AC_LANG_PUSH([C++])
   AC_CACHE_CHECK([for C++ compiler-specific extra flags],
                  [ac_cv_cxx_style],
                  [ac_cv_cxx_style=unknown
                   if test "x$ac_compiler_gnu" != xno; then
		      if $CXX --version | grep '^2\.' >/dev/null ; then
			ac_cv_cxx_style=weakGNU
                      else
                        ac_cv_cxx_style=GNU
                      fi
                   elif $CXX -V 2>&1 | grep -i "WorkShop">/dev/null 2>&1; then 
		      ac_cv_cxx_style=Sun
                   elif $CXX -V 2>&1 | grep -i "Intel(R) C++">/dev/null 2>&1;
                   then
                      ac_cv_cxx_style=Intel
                   else
                      echo "int main() {}" >conftest.cc
                      if $CXX --version conftest.cc 2>&1 \
		         | grep -i "Comeau C/C++" >/dev/null 2>&1; then       
                         ac_cv_cxx_style=Comeau
		      fi
                      rm -f conftest.*
                   fi])
   AC_LANG_POP([C++])

   case "$ac_cv_cxx_style" in
     GNU)
      _CXXFLAGS_DEBUG="-g"
      _CXXFLAGS_OPTIMIZE="-O3 -finline-limit-1500"
      _CXXFLAGS_STRICT="-W -Wall"
      _CXXFLAGS_STRICT_ERRORS="-W -Wall -Werror"
      ;;
     weakGNU)
      _CXXFLAGS_DEBUG="-g"
      _CXXFLAGS_OPTIMIZE="-O2 -felide-constructors -funroll-loops"
      _CXXFLAGS_STRICT="-W -Wall"
      _CXXFLAGS_STRICT_ERRORS="-W -Wall -Werror"
      ;;
     Sun)
      _CXXFLAGS_DEBUG="-g"
      _CXXFLAGS_OPTIMIZE="-fast"
      _CXXFLAGS_STRICT="-v"
      _CXXFLAGS_STRICT_ERRORS="-v -xwe"
      ;;
     Comeau)
      _CXXFLAGS_DEBUG="-g"
      _CXXFLAGS_STRICT="-r"
      _CXXFLAGS_STRICT_ERRORS="-r"
      ;;
     Intel)
      _CXXFLAGS_OPTIMIZE="-O3"
      _CXXFLAGS_DEBUG="-g"
      _CXXFLAGS_STRICT="-w1"
      _CXXFLAGS_STRICT_ERRORS="-w1"
      ;;
   esac

   if test "x$CXXFLAGS_OPTIMIZE" = "x"; then
	CXXFLAGS_OPTIMIZE=$_CXXFLAGS_OPTIMIZE
   fi
   if test "x$CXXFLAGS_DEBUG" = "x"; then
	CXXFLAGS_DEBUG=$_CXXFLAGS_DEBUG
   fi
   if test "x$CXXFLAGS_STRICT" = "x"; then
	CXXFLAGS_STRICT=$_CXXFLAGS_STRICT
   fi
   if test "x$CXXFLAGS_STRICT_ERRORS" = "x"; then
	CXXFLAGS_STRICT_ERRORS=$_CXXFLAGS_STRICT_ERRORS
   fi

   AC_SUBST([CXXFLAGS_DEBUG])
   AC_SUBST([CXXFLAGS_OPTIMIZE])
   AC_SUBST([CXXFLAGS_STRICT])
   AC_SUBST([CXXFLAGS_STRICT_ERRORS])
])

# VCSN_WARN_CXXFLAGS

# Check that the variable CXXFLAGS does not contain debug or
# optimization flags

AC_DEFUN([VCSN_WARN_CXXFLAGS],
[dnl
  vcsn_cxxflags_clean=yes

  AC_REQUIRE([AC_PROG_CXX])
  AC_LANG_PUSH([C++])dnl force initialization of default CXXFLAGS
  AC_MSG_CHECKING([for debbuging options in CXXFLAGS ($CXXFLAGS)])
  if echo "$CXXFLAGS" | grep -- "-g" >/dev/null 2>&1; then
     AC_MSG_RESULT([yes])
     AC_MSG_WARN([CXXFLAGS seems to contain debugging options, which is known to conflict with Vaucanson optimizations.])
     AC_MSG_NOTICE([please cleanup CXXFLAGS and use CXXFLAGS_DEBUG instead for your own options.])
     vcsn_cxxflags_clean=no
  else
     AC_MSG_RESULT([no, good])
  fi
  AC_MSG_CHECKING([for optimization options in CXXFLAGS ($CXXFLAGS)])
  if echo "$CXXFLAGS" | grep -- "-O" >/dev/null 2>&1; then
     AC_MSG_RESULT([yes])
     AC_MSG_WARN([CXXFLAGS seems to contain optimization options, while Vaucanson provides its own optimization flags.])
     AC_MSG_NOTICE([please cleanup CXXFLAGS and use CXXFLAGS_OPTIMIZE instead for your own options.])
     vcsn_cxxflags_clean=no
  else
     AC_MSG_RESULT([no, good])
  fi
  AC_LANG_POP([C++])
])

# AC_WITH_VCSN

# Invoke configuration code to test for Vaucanson and set a collection
# of appropriate flags.

AC_DEFUN([AC_WITH_VCSN],
[dnl
  AC_REQUIRE([AC_CXX_TEMPLATE_DEPTH])
  AC_REQUIRE([AC_CXX_NUMERIC_LIMITS])
  AC_REQUIRE([AC_CXX_FLOAT_MATH])
  AC_REQUIRE([VCSN_PATH_HEADERS])
  AC_REQUIRE([VCSN_WARN_CXXFLAGS])
])

# Test invocation macro

AC_DEFUN([VCSN_TESTS], [
AC_MSG_CHECKING([for $1 in testsuite])
if test -d $srcdir/src/tests/tests-suites/$1; then
   AC_MSG_RESULT([yes])
   VCSN_TESTS_SUBDIRS="$VCSN_TESTS_SUBDIRS $1"
   AC_CONFIG_FILES([src/tests/tests-suites/$1/Makefile])
else 
   AC_MSG_RESULT([no])
fi
])

# Check for SWIG

AC_DEFUN([AC_CHECK_SWIG13],
[dnl
  AC_ARG_VAR([SWIG], [the SWIG interface generator])
  AC_CHECK_PROGS([SWIG], [swig], [$am_aux_dir/missing swig])

  AC_CACHE_CHECK([for SWIG >= 1.3],
                 [ac_cv_recent_swig],
                 [ac_cv_recent_swig=no
                  swig_ver=`$SWIG -version 2>&1 | sed -n -e '/SWIG Version/{s/^.*Version \(.*\)/\1/g;p;q;}'`
                  swig_minor=`echo "$swig_ver" | sed -e 's/^@<:@0-9@:>@*\.\(@<:@^.@:>@*\).*/\1/g'`
                  swig_major=`echo "$swig_ver" | sed -e 's/^\(@<:@0-9@:>@*\)\..*/\1/g'`
	          if test `expr $swig_major \* 100 + $swig_minor 2>/dev/null` -ge 103 >/dev/null 2>&1; then
                      ac_cv_recent_swig=yes
                  fi])
])


