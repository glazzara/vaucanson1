# configure.ac
#
#
# $Id$
# VCSN_HEADER

AC_PREREQ([2.54])
AC_INIT([vaucanson], [0.3.0], [vaucanson-bugs@lrde.epita.fr])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([config/vcsn.m4])
AM_INIT_AUTOMAKE([1.7 no-define foreign dist-bzip2])
AM_CONFIG_HEADER([config.h:config.hin])

# Some C and C++ code used.
# Using $CXX as the C compiler is a hack to allow building shared
# modules from C++ source with libtool.
AC_PROG_CXX
AC_PROG_CC([$CXX])

# Use included Vaucanson version.
VCSN_PATH_LOCAL([.])
AC_WITH_VCSN

# SWIG and Python used.
AC_CHECK_SWIG13
AM_PATH_PYTHON([2.2])

# Libtool used
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# Attempt to use strict language conformance checking.
AC_CXX_FLAGS

# Some reflexivity wanted.
AC_DEFINE_UNQUOTED([CXX], ["$CXX"], [The C++ compiler])

# AC_CHECK_HEADERS([stl_config.h])

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
	src/tests/fundamental/Makefile
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
	src/demos/Makefile
	src/demos/vgrep/Makefile
	src/demos/samples/Makefile
	src/demos/samples/algebra/Makefile
	src/demos/samples/algorithms/Makefile
        src/demos/vaucanswig/Makefile
        src/demos/vaucanswig/meta/Makefile
        src/demos/vaucanswig/src/Makefile
        src/demos/vaucanswig/python/Makefile
	doc/Makefile
	doc/tutorial/Makefile
        doc/doc.doxy
	include/Makefile])

dnl VCSN_TESTS([usual_automaton_t])
dnl VCSN_TESTS([algebra_series_krat])
dnl VCSN_TESTS([algebra_series_krat_derivation])
dnl VCSN_TESTS([algebra_series_misc])
dnl VCSN_TESTS([algebra_numerical_semiring])
dnl VCSN_TESTS([algebra_set_alphabet])
dnl VCSN_TESTS([algebra_string_free_monoid])
dnl VCSN_TESTS([algebra_tropical_max_semiring])

AC_SUBST([VCSN_TESTS_SUBDIRS])

AC_OUTPUT
