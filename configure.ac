# configure.ac
#
#
# $Id$
# VCSN_HEADER

AC_PREREQ([2.54])
AC_INIT([vaucanson], [0.4.1], [vaucanson-bugs@lrde.epita.fr])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([config/vcsn.m4])
AM_INIT_AUTOMAKE([1.7 no-define foreign dist-bzip2])
AM_CONFIG_HEADER([config.h:config.hin])

# Some C and C++ code used.
# Using $CXX as the C compiler is a hack to allow building shared
# modules from C++ source with libtool.
AC_PROG_CXX
CC=$CXX
AC_PROG_CC

# Use included Vaucanson version.
VCSN_PATH_LOCAL([.])
AC_WITH_VCSN

# Awk is used.
AC_PROG_AWK

# SWIG and Python used.
AC_CHECK_SWIG13
AM_PATH_PYTHON([2.2])

WANT_INTERPRETER=no
AC_ARG_WITH([vaucanswig],
            [AC_HELP_STRING([--without-vaucanswig], 
			    [disable building vaucanswig])],
            [WANT_INTERPRETER=$withval],
            [WANT_INTERPRETER=yes])

VCSN_VAUCANSWIG_SUBDIR=""
if test "x$WANT_INTERPRETER" != "xno"; then
if test "x$ac_cv_recent_swig" != "xyes"; then
    AC_MSG_ERROR([You need swig >= 1.3 to compile vaucanswig. 
	  	  You can disable vaucanswig by specifying 
		  --without-vaucanswig to configure.])
else
  AC_CONFIG_FILES([src/demos/vaucanswig/Makefile
	           src/demos/vaucanswig/meta/Makefile
                   src/demos/vaucanswig/src/Makefile
                   src/demos/vaucanswig/python/Makefile])
  VCSN_VAUCANSWIG_SUBDIR="vaucanswig"
fi
fi

# Libtool used
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# Attempt to use strict language conformance checking.
AC_CXX_FLAGS

# Some reflexivity wanted.
AC_DEFINE_UNQUOTED([CXX], ["$CXX"], [The C++ compiler])

# AC_CHECK_HEADERS([stl_config.h])

# Xerces C++
AC_ARG_WITH(
  [xerces],
  [  --with-xerces           specify Xerces-C++ location],
  [XERCESC=$withval],
  [if test "x$prefix" = xNONE; then
     XERCESC=$ac_default_prefix
   else
     XERCESC=$prefix
   fi])
AC_ARG_ENABLE(
  [xml],
  [  --enable-xml            enable xml tests (need Xerces-C++ 2.3.x library)],
  [ac_compile_xerces_check_save=$ac_compile
  ac_cpp_xerces_check_save=$ac_cpp
  ac_compile="$ac_compile -I${XERCESC}/include"
  ac_cpp="$ac_cpp -I${XERCESC}/include"
  AC_CHECK_HEADER(
    [xercesc/util/XercesVersion.hpp],
    [AC_MSG_CHECKING([Xerces-C++ version])
    AC_COMPILE_IFELSE(
      [AC_LANG_SOURCE(
        [
@%:@include <xercesc/util/XercesVersion.hpp>
@%:@if XERCES_VERSION_MAJOR != 2
@%:@ error "Bad Xerces-C++ major version."
@%:@endif
@%:@if XERCES_VERSION_MINOR != 3
@%:@ error "Bad Xerces-C++ minor version."
@%:@endif
        ])
      ],
      [
      AC_MSG_RESULT([2.3.x])
      LIBS_xerces_check_save=$LIBS
      AC_CHECK_LIB([xerces-c],[_ZN11xercesc_2_316XMLPlatformUtils9TerminateEv],
        AC_SUBST(XERCESC),
        AC_ERROR([Could not link to Xerces-C++ library.]),
        [-L${XERCESC}/lib])],
      AC_ERROR([Bad Xerces-C++ version.]))
      LIBS=$LIBS_xerces_check_save],
    AC_ERROR([Could not find Xerces-C++. Did you set --with-xerces argument?]))
  ac_compile=$ac_compile_xerces_check_save
  ac_cpp=$ac_cpp_xerces_check_save
  xml_check=true],
  xml_check=false
)
AM_CONDITIONAL(XML_CHECK, test x$xml_check = xtrue)

##
## for documentation purpose.
##
AC_ARG_VAR([DOXYGEN], [the Doxygen documentation generation program])
AC_CHECK_PROGS([DOXYGEN], [doxygen], [$am_aux_dir/missing doxygen])
AC_ARG_VAR([TEXI2DVI], [program to create DVI from TeX files])
AC_CHECK_PROGS([TEXI2DVI], [texi2dvi], [$am_aux_dir/missing texi2dvi])
AC_ARG_VAR([TAR], [the tape archiver program])
AC_CHECK_PROGS([TAR], [tar], [$am_aux_dir/missing tar])

##
## generate files.
##
#AC_CONFIG_SUBDIRS([vauc])

AC_CONFIG_FILES([
	Makefile
	include/vaucanson/config/pconf.hh:include/vaucanson/config/pconf-hh.in
	src/Makefile
	src/tests/Makefile
	src/tests/check/Makefile
	src/tests/check/defs
	src/tests/sanity/Makefile
	src/tests/design_pattern/Makefile
	src/tests/misc/Makefile
	src/tests/algebra/Makefile
	src/tests/algebra/series/Makefile
	src/tests/algebra/series/krat/Makefile
	src/tests/algebra/series/krat/derivations/Makefile
	src/tests/algebra/series/krat/derivations/derivation/Makefile
	src/tests/algebra/series/krat/derivations/cderivation/Makefile
	src/tests/algebra/series/krat/main/Makefile
	src/tests/algebra/series/misc/Makefile
	src/tests/algebra/semiring/Makefile
	src/tests/algebra/alphabets/Makefile
	src/tests/algebra/free_monoid/Makefile
	src/tests/automata/Makefile
	src/tests/automata/algos/Makefile
	src/tests/automata/implementation_check/Makefile
	src/tests/tests-suites/Makefile
	src/tests/xml/Makefile
	src/demos/Makefile
	src/demos/vgrep/Makefile
	src/demos/fibonacci/Makefile
	src/demos/samples/Makefile
	src/demos/samples/algebra/Makefile
	src/demos/samples/algorithms/Makefile
	doc/Makefile
	doc/tutorial/Makefile
	doc/beginner/Makefile
        doc/doc.doxy
	include/Makefile
	xml/Makefile])

VCSN_TESTS([usual_automaton_t])
VCSN_TESTS([algebra_series_krat])
VCSN_TESTS([algebra_series_krat_derivation])
VCSN_TESTS([algebra_series_misc])
VCSN_TESTS([algebra_numerical_semiring])
VCSN_TESTS([algebra_set_alphabet])
VCSN_TESTS([algebra_string_free_monoid])
VCSN_TESTS([algebra_tropical_max_semiring])

AC_SUBST([VCSN_TESTS_SUBDIRS])
AC_SUBST([VCSN_VAUCANSWIG_SUBDIR])

AC_OUTPUT
