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

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/tests/defs
	src/tests/Makefile
	src/tests/check/Makefile
	src/tests/fundamental/Makefile
	src/tests/algebra/Makefile
	src/tests/algebra/series/Makefile
	src/tests/automata/Makefile
	src/tests/automata/algos/Makefile
	src/tests/automata/implementation_check/Makefile
	src/tests/sanity/Makefile
	src/tests/tests-suites/Makefile
	src/tests/bin/Makefile
	src/tests/tests-suites/usual_automaton_t/Makefile
	src/tests/tests-suites/algebra_set_alphabet/Makefile
	src/tests/tests-suites/algebra_string_free_monoid/Makefile
	src/tests/tests-suites/algebra_numerical_semiring/Makefile
	src/tests/tests-suites/algebra_tropical_max_semiring/Makefile
	doc/Makefile
        doc/doc.doxy	
	include/Makefile])

AC_OUTPUT
