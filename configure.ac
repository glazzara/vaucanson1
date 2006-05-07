# configure.ac
#
#
# $Id$
# VCSN_HEADER

AC_PREREQ([2.54])
AC_INIT([vaucanson], [0.7.2], [vaucanson-bugs@lrde.epita.fr])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([config/vcsn.m4])
AM_INIT_AUTOMAKE([1.9 tar-ustar no-define foreign dist-bzip2])
AC_CONFIG_HEADERS([config.h:config.hin] [include/vaucanson/config/pconf.hh])


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
AM_PATH_PYTHON([2.2])

AC_ARG_ENABLE(
	[vaucanswig],
        [AC_HELP_STRING([--enable-vaucanswig],
			[enable building vaucanswig])],
	[WANT_INTERPRETER=$enableval],
        [WANT_INTERPRETER=no
cat << \EOF
**********************************************************************
WARNING:  Vaucanswig  WILL NOT  be  built.   Vaucanswig  is a  set  of
bindings for the Python language  to use Vaucanson from an interpreter
or within a scripting language.

To enable Vaucanswig, invoke this script with --enable-vaucanswig.
To disable this warning, invoke this script with --disable-vaucanswig.

BE WARNED: the  compilation of Vaucanswig may take  several hours on a
modern computer.

Instructions about Vaucanswig are provided in
src/demos/vaucanswig/README.
**********************************************************************
EOF
sleep 5])

VCSN_VAUCANSWIG_SUBDIR=""
if test "x$WANT_INTERPRETER" != "xno"; then
  AC_CHECK_SWIG13
  if test "x$ac_cv_recent_swig" != "xyes"; then
    AC_MSG_ERROR([You need swig >= 1.3 to compile vaucanswig.])
  else
    AC_CONFIG_FILES([src/demos/vaucanswig/Makefile
 	             src/demos/vaucanswig/doc/Makefile
 	             src/demos/vaucanswig/meta/Makefile
                     src/demos/vaucanswig/src/Makefile
                     src/demos/vaucanswig/python/Makefile])
    VCSN_VAUCANSWIG_SUBDIR="vaucanswig"
  fi
fi

# Whether to compile samples or not.
# (speed up compilation)
AC_ARG_ENABLE(
       [build-demo],
        [AC_HELP_STRING([--disable-build-demo],
                       [disable compilation of demos subdirectory])],
       [build_demo=],
       [build_demo=true]
)
AM_CONDITIONAL([BUILD_DEMO], test $build_demo)

# Libtool used
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# Attempt to use strict language conformance checking.
AC_CXX_FLAGS

# Some reflexivity wanted.
AC_DEFINE_UNQUOTED([CXX], ["$CXX"], [The C++ compiler])

# AC_CHECK_HEADERS([stl_config.h])

VCSN_XML
VCSN_TAF_KIT

##
## Package header configuration.
##

# Tell what's the default XSD path.
old_prefix=$prefix
case $prefix in
  [\\/]* | ?:[\\/]* ) ;;
  *) prefix=$ac_default_prefix ;;
esac
AC_DEFINE_UNQUOTED([VCSN_DATA_PATH], ["$(eval echo \"$datadir/vaucanson/\")"],
		   [Path in which data such as XSD will be installed])
prefix=$old_prefix

# Package misc variables.
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_NAME], ["$PACKAGE_NAME"], [Full name.])
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_BUGREPORT], ["$PACKAGE_BUGREPORT"],
		   [Bug report address.])
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_STRING], ["$PACKAGE_STRING"],
		   [Full name and version.])
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_VERSION], ["$PACKAGE_VERSION"], [Version.])

##
## for documentation purpose.
##
AC_ARG_VAR([DOXYGEN], [the Doxygen documentation generation program])
AC_CHECK_PROGS([DOXYGEN], [doxygen], [$am_aux_dir/missing doxygen])
AC_ARG_VAR([TEXI2DVI], [program to create DVI from TeX files])
AC_CHECK_PROGS([TEXI2DVI], [texi2dvi], [$am_aux_dir/missing texi2dvi])
AC_CHECK_PROGS([DVIPDF], [dvipdf], [$am_aux_dir/missing dvipdf])
AC_ARG_VAR([RST2TEX], [program to create TeX from reStructuredText documents])
AC_CHECK_PROGS([RST2TEX], [rst2latex rst2latex.py], [$am_aux_dir/missing rst2latex])
AC_ARG_VAR([RST2HTML], [program to create HTML from reStructuredText documents])
AC_CHECK_PROGS([RST2HTML], [rst2html rst2html.py], [$am_aux_dir/missing rst2html])
AC_ARG_VAR([TAR], [the tape archiver program])
AC_CHECK_PROGS([TAR], [tar], [$am_aux_dir/missing tar])

##
## generate files.
##

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/taf-kit/Makefile
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
	src/tests/algebra/series/krat/tests/Makefile
	src/tests/algebra/series/misc/Makefile
	src/tests/algebra/series/polynom/Makefile
	src/tests/algebra/semiring/Makefile
	src/tests/algebra/alphabets/Makefile
	src/tests/algebra/free_monoid/Makefile
	src/tests/algebra/free_monoid_product/Makefile
	src/tests/automata/Makefile
	src/tests/automata/algos/Makefile
	src/tests/automata/algos/boolean_automata/Makefile
	src/tests/automata/algos/fmp_transducers/Makefile
	src/tests/automata/algos/freemonoid_labeled_graphs/Makefile
	src/tests/automata/algos/graphs/Makefile
	src/tests/automata/algos/label_aware_graphs/Makefile
	src/tests/automata/algos/labeled_graphs/Makefile
	src/tests/automata/algos/letter_combination_labeled_graphs/Makefile
	src/tests/automata/algos/series_multiplicity_transducers/Makefile
	src/tests/automata/implementation_check/Makefile
	src/tests/context_headers/Makefile
	src/tests/context_headers/automata/Makefile
	src/tests/context_headers/transducers/Makefile
	src/tests/context_headers/fmp_transducers/Makefile
	src/tests/test-suites/Makefile
	src/tests/xml/Makefile
	src/demos/Makefile
	src/demos/utilities/Makefile
	src/demos/utilities/vgrep/Makefile
	src/demos/automaton_library/Makefile
	src/demos/function_library/Makefile
	src/demos/algorithms/Makefile
	src/demos/transducers/Makefile
	src/demos/transducers/one_rule_rewriting/Makefile
	src/benchs/Makefile
	src/benchs/common/Makefile
	src/benchs/determinization/Makefile
	src/benchs/minimization_debruijn/Makefile
	src/benchs/minimization_stroppa/Makefile
	src/benchs/minimization_2n/Makefile
	src/benchs/quotient/Makefile
	src/benchs/composition/Makefile
	src/benchs/derived_terms/Makefile
	doc/Makefile
	doc/manual/Makefile
	doc/makefiles/Makefile
	doc/xml/Makefile
        doc/doc.doxy
	include/Makefile
        debian/Makefile])

m4_include([config/tests.m4])

AC_SUBST([VCSN_TESTS_SUBDIRS])
AC_SUBST([VCSN_VAUCANSWIG_SUBDIR])

AC_OUTPUT
