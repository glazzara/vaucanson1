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

AC_PROG_CXX
AC_PROG_RANLIB
AC_LANG(C++)

AC_CHECK_HEADERS([limits])
AC_CHECK_HEADERS([stl_config.h])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/tests/Makefile
	src/tests/check/Makefile
	src/tests/fundamental/Makefile
	src/tests/algebra/Makefile
	src/tests/algebra/semiring/Makefile
	src/tests/algebra/alphabets/Makefile
	src/tests/algebra/free_monoid/Makefile
	src/tests/algebra/series/Makefile
	src/tests/automata/Makefile
	src/tests/automata/algos/Makefile
	src/tests/automata/implementation_check/Makefile
	src/tests/tests-suites/Makefile
	src/tests/bin/Makefile
	src/tests/tests-suites/usual_automaton_t/Makefile
	include/Makefile])

AC_OUTPUT
