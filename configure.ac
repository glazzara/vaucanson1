# configure.ac
#
#
# $Id$
# VCSN_HEADER

AC_PREREQ([2.50])
AC_INIT([vaucanson], [0.1.0], [vaucanson-bugs@lrde.epita.fr])
AC_CONFIG_SRCDIR([ChangeLog])
AM_CONFIG_HEADER(include/vaucanson/config/config.hh)
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AM_MAINTAINER_MODE

AC_DEFINE_UNQUOTED([CXX], ["$CXX"], [The C++ compiler])
AC_PROG_CXX

AC_PROG_RANLIB
AC_LANG(C++)

AC_CHECK_HEADERS([limits])
AC_CHECK_HEADERS([stl_config.h])

AC_CHECK_PROG(DOXYGEN, doxygen, doxygen, no)
if test x"$DOXYGEN" = x"no"; then
  echo "Cannot find doxygen. Disabling auto-generation of the documentation" 2>&1
  DOXYGEN=/bin/true
fi

VCSN_TESTS_SUBDIRS=""
AC_DEFUN([VCSN_TESTS], [
if test -d src/tests/tests-suites/$1; then
   VCSN_TESTS_SUBDIRS="$VCSN_TESTS_SUBDIRS $1"
   AC_CONFIG_FILES([src/tests/tests-suites/$1/Makefile])
fi
])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/tests/defs
	src/tests/Makefile
	src/tests/check/Makefile
	src/tests/fundamental/Makefile
	src/tests/algebra/Makefile
	src/tests/algebra/series/Makefile
	src/tests/algebra/semiring/Makefile
	src/tests/algebra/alphabets/Makefile
	src/tests/algebra/free_monoid/Makefile
	src/tests/automata/Makefile
	src/tests/automata/algos/Makefile
	src/tests/automata/implementation_check/Makefile
	src/tests/sanity/Makefile
	src/tests/tests-suites/Makefile
	src/tests/bin/Makefile
	doc/Makefile
        doc/doc.doxy	
	include/Makefile])

VCSN_TESTS([algebra_numerical_semiring])
VCSN_TESTS([algebra_set_alphabet])
VCSN_TESTS([algebra_string_free_monoid])
VCSN_TESTS([algebra_tropical_max_semiring])
VCSN_TESTS([usual_automaton_t])
AC_SUBST([VCSN_TESTS_SUBDIRS])

AC_OUTPUT
