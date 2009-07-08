# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 The
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

m4_pattern_forbid([^VCSN_])

# VCSN_HEADER

AC_PREREQ([2.61])

AC_INIT([vaucanson], [1.3.1a], [vaucanson-bugs@lrde.epita.fr])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.10 tar-ustar no-define foreign dist-bzip2])
AC_CONFIG_HEADERS([config.h:config.hin] [include/vaucanson/config/pconf.hh])

AC_CONFIG_SUBDIRS([cbs])

# Check the default graph implementation near the top, this way we can
# quickly react to incorrect values.
ac_default_graph_impl=listg
AC_ARG_WITH([default-graph-impl],
  [AC_HELP_STRING([--with-default-graph-impl@<:@=IMPL@:>@],
     [choose default graph implementation: listg (default) or bmig])],
     [ac_default_graph_impl="$withval"],[])

AC_DEFINE_UNQUOTED([VCSN_DEFAULT_GRAPH_IMPL], [$ac_default_graph_impl],
		   [Default graph implementation.])

case $ac_default_graph_impl in
  listg|bmig);;
  *) AC_ERROR([Unknown graph implementation: $ac_default_graph_impl]);;
esac

# Specify the path OpenFST binaries for benchmarks.
ac_openfst_path=/usr/local/bin # default install dir in OpenFST 1.1
AC_ARG_WITH([openfst],
  [AC_HELP_STRING([--with-openfst@<:@=DIR@:>@],
     [specify the path to OpenFST binaries for benchmarks])],
     [ac_openfst_path="$withval"],[])

AM_CONDITIONAL([ENABLE_OPENFST], [test -e "${ac_openfst_path}/fstcompile"])
if test -e "${ac_openfst_path}/fstcompile"; then
  AC_DEFINE_UNQUOTED([OPENFST_PATH], ["$ac_openfst_path"],
                     [Path to OpenFST binaries.])
else
  AC_MSG_WARN([OpenFST binaries not found in ${ac_openfst_path}, OpenFST benchmarks are disabled.])
fi

# Some C and C++ code used.
AC_PROG_CXX
AC_PROG_CC
gl_EARLY
gl_INIT

# Use included Vaucanson version.
VCSN_PATH_LOCAL([.])
AC_WITH_VCSN


# Awk is used.
AC_PROG_AWK


AC_ARG_ENABLE([demos],
	[AC_HELP_STRING([--enable-demos], [build demos during "make all"])])
AM_CONDITIONAL([ENABLE_DEMOS], [test "x$enable_demos" = "xyes"])
AC_ARG_ENABLE([bench],
	[AC_HELP_STRING([--enable-bench],
	                [build benchmarks during "make all"])])
AM_CONDITIONAL([ENABLE_BENCH], [test "x$enable_bench" = "xyes"])

# Boost
AX_BOOST_BASE([1.34])
# Do not require boost::serialization headers.
BOOST_CPPFLAGS="$BOOST_CPPFLAGS -DBOOST_MULTI_INDEX_DISABLE_SERIALIZATION"
# FIXME: It would be nice to check that the Boost package we require
# (boost::graph, boost::multi_index...)

AC_SUBST([MORE_DISTCHECK_CONFIGURE_FLAGS])
if test "${with_boost+set}" = set; then
  MORE_DISTCHECK_CONFIGURE_FLAGS="$MORE_DISTCHECK_CONFIGURE_FLAGS --with-boost=$with_boost"
fi


# Libtool used
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# Where to install Emacs files.
AM_PATH_LISPDIR

VCSN_XML

if test "${with_xerces+set}" = set; then
  MORE_DISTCHECK_CONFIGURE_FLAGS="$MORE_DISTCHECK_CONFIGURE_FLAGS --with-xerces=$with_xerces"
fi

VCSN_TAF_KIT

##
## Package header configuration.
##

# Tell what's the default pkgdata dir.
old_prefix=$prefix
case $prefix in
  [\\/]* | ?:[\\/]* ) ;;
  *) prefix=$ac_default_prefix ;;
esac
# This expansion by hand is a PITA, but we don't have much choice,
# Autoconf provides no standard means to do that, since RMS wants to
# support make-time changes of $prefix.  We do not support this silly
# idea.
VCSN_DATA_PATH=$(eval echo $(eval echo "$datadir/vaucanson/"))
AC_DEFINE_UNQUOTED([VCSN_DATA_PATH], ["$VCSN_DATA_PATH"],
		   [Directory where Vaucaunson data is installed.])
prefix=$old_prefix

# Package misc variables.
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_NAME], ["$PACKAGE_NAME"],
                   [Package Full name.])
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_BUGREPORT], ["$PACKAGE_BUGREPORT"],
		   [Bug report address.])
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_STRING], ["$PACKAGE_STRING"],
		   [Full name and version.])
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_VERSION], ["$PACKAGE_VERSION"],
                   [Package Version.])

# XML namespace.
AC_DEFINE_UNQUOTED([VCSN_XMLNS], ["http://vaucanson.lrde.epita.fr"],
		   [Root of the XML namespace.])


## --------------- ##
## Documentation.  ##
## --------------- ##

# VCSN_ARG_PROGS(PROG, DOC, [PROGRAMS...])
# ----------------------------------------
m4_define([VCSN_ARG_PROGS],
[AC_ARG_VAR(m4_toupper([$1]), [$2])
AC_CHECK_PROGS(m4_toupper([$1]), [m4_default([$3], [$1])],
	       [$am_aux_dir/missing $1])
])


VCSN_ARG_PROGS([doxygen],   [the Doxygen documentation generation program])
VCSN_ARG_PROGS([texi2dvi],  [program to create DVI from TeX files])
VCSN_ARG_PROGS([rst2latex],
	       [reStructuredText to LaTeX converter],
	       [rst2latex rst2latex.py])
VCSN_ARG_PROGS([rst2html],
	       [reStructuredText to HTML converter],
	       [rst2html rst2html.py])
VCSN_ARG_PROGS([tar],       [the tape archiver program])

AC_CONFIG_FILES([
   doc/Makefile
   doc/doc.doxy
	doc/manual/Makefile
])


## ------- ##
## TAF-Kit ##
## ------- ##

AC_CONFIG_FILES([
	taf-kit/Makefile
	  taf-kit/src/Makefile
	  taf-kit/tests/Makefile
	  taf-kit/demos/Makefile
	  taf-kit/demos/hulden/Makefile
])

# Prevent accidental edition of generated files.
AC_CONFIG_FILES([taf-kit/tests/defs], [chmod a-w taf-kit/tests/defs])

# VCSN_CONFIG_WRAPPER TAF-KIT-COMPONENT-NAME
# ------------------------------------------
# Create a testing wrapper for the TAF-KIT-COMPONENT-NAME.
m4_define([VCSN_CONFIG_WRAPPER],
[AC_CONFIG_FILES([taf-kit/tests/$1:taf-kit/tests/wrapper.in],
		 [chmod a+x taf-kit/tests/$1])
])
VCSN_CONFIG_WRAPPER([vcsn-char-b])
VCSN_CONFIG_WRAPPER([vcsn-char-fmp-b])
VCSN_CONFIG_WRAPPER([vcsn-char-fmp-z])
VCSN_CONFIG_WRAPPER([vcsn-char-z])
VCSN_CONFIG_WRAPPER([vcsn-char-r])
VCSN_CONFIG_WRAPPER([vcsn-int-b])
VCSN_CONFIG_WRAPPER([vcsn-int-fmp-b])
VCSN_CONFIG_WRAPPER([vcsn-int-fmp-z])
VCSN_CONFIG_WRAPPER([vcsn-int-z])
VCSN_CONFIG_WRAPPER([vcsn-char-char-b])
VCSN_CONFIG_WRAPPER([vcsn-char-int-b])
VCSN_CONFIG_WRAPPER([vcsn-int-int-b])
VCSN_CONFIG_WRAPPER([vcsn-char-zmin])
VCSN_CONFIG_WRAPPER([vcsn-char-zmax])


## ------- ##
## Tests.  ##
## ------- ##

AC_CONFIG_FILES([
src/tests/Makefile
src/tests/check/Makefile
src/tests/check/defs
src/tests/design_pattern/Makefile
src/tests/include/Makefile
src/tests/misc/Makefile
src/tests/sanity/Makefile
src/tests/test-suites/Makefile
src/tests/xml/Makefile
])

## ---------------- ##
## Generate files.  ##
## ---------------- ##

AC_CONFIG_FILES([
	Makefile
	build-aux/Makefile
	data/Makefile
	  data/automata/Makefile
	    data/automata/char-b/Makefile
	    data/automata/char-fmp-b/Makefile
	    data/automata/char-rw-b/Makefile
	    data/automata/char-z/Makefile
	  data/emacs/Makefile
        gnulib/Makefile
	lib/Makefile
	src/Makefile
	  src/demos/Makefile
	    src/demos/algorithms/Makefile
	    src/demos/one_rule_rewriting/Makefile
	    src/demos/vgrep/Makefile
	  src/bench/Makefile
	    src/bench/common/Makefile
	    src/bench/composition/Makefile
	    src/bench/derived_terms/Makefile
	    src/bench/determinization/Makefile
	    src/bench/eps_removal/Makefile
	    src/bench/iterators/Makefile
	    src/bench/accessible/Makefile
	    src/bench/minimization/Makefile
	    src/bench/product/Makefile
	    src/bench/quotient/Makefile
	tools/Makefile
	include/Makefile
	debian/Makefile])

m4_include([build-aux/tests.m4])

AC_SUBST([VCSN_TESTS_SUBDIRS])

AC_OUTPUT
