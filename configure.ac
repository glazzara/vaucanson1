# configure.ac
#
#
# $Id$
# VCSN_HEADER

AC_PREREQ([2.54])
AC_INIT([vaucanson], [0.5], [vaucanson-bugs@lrde.epita.fr])
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

VCSN_XML

##
## for documentation purpose.
##
AC_ARG_VAR([DOXYGEN], [the Doxygen documentation generation program])
AC_CHECK_PROGS([DOXYGEN], [doxygen], [$am_aux_dir/missing doxygen])
AC_ARG_VAR([TEXI2DVI], [program to create DVI from TeX files])
AC_CHECK_PROGS([TEXI2DVI], [texi2dvi], [$am_aux_dir/missing texi2dvi])
AC_ARG_VAR([SGML2LATEX], [program to create TeX from LinuxDoc SGML files])
AC_CHECK_PROGS([SGML2LATEX], [sgml2latex], [$am_aux_dir/missing sgml2latex])
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
	src/tests/algebra/numerical_semiring/Makefile
	src/tests/algebra/series/Makefile
	src/tests/algebra/series/krat/Makefile
	src/tests/algebra/series/krat/derivations/Makefile
	src/tests/algebra/series/krat/derivations/derivation/Makefile
	src/tests/algebra/series/krat/derivations/cderivation/Makefile
	src/tests/algebra/series/krat/derivations/partial_derivation/Makefile
	src/tests/algebra/series/krat/main/Makefile
	src/tests/algebra/series/krat/boolean/Makefile
	src/tests/algebra/series/misc/Makefile
	src/tests/algebra/series/polynom/Makefile
	src/tests/algebra/semiring/Makefile
	src/tests/algebra/alphabets/Makefile
	src/tests/algebra/free_monoid/Makefile
	src/tests/automata/Makefile
	src/tests/automata/algos/Makefile
	src/tests/automata/implementation_check/Makefile
	src/tests/boolean_automata/Makefile
	src/tests/transducers/Makefile
	src/tests/context_headers/Makefile
	src/tests/context_headers/automata/Makefile
	src/tests/context_headers/transducers/Makefile
	src/tests/test-suites/Makefile
	src/tests/xml/Makefile
	src/demos/Makefile
	src/demos/ciaa/Makefile
	src/demos/vgrep/Makefile
	src/demos/fibonacci/Makefile
	src/demos/universal/Makefile
	src/demos/samples/Makefile
	src/demos/samples/algebra/Makefile
	src/demos/samples/algorithms/Makefile
	doc/Makefile
	doc/tutorial/Makefile
	doc/beginner/Makefile
	doc/makefiles/Makefile
	doc/xml/Makefile
        doc/doc.doxy
	include/Makefile
	xml/Makefile])

m4_include([tests.m4])

AC_SUBST([VCSN_TESTS_SUBDIRS])
AC_SUBST([VCSN_VAUCANSWIG_SUBDIR])

AC_OUTPUT
