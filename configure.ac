# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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

AC_INIT([vaucanson], [1.1], [vaucanson-bugs@lrde.epita.fr])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.10 tar-ustar no-define foreign dist-bzip2 nostdinc])
AC_CONFIG_HEADERS([config.h:config.hin] [include/vaucanson/config/pconf.hh])

VCSN_PRE_RELEASE

# Some C and C++ code used.
AC_PROG_CXX
AC_PROG_CC

# Use included Vaucanson version.
VCSN_PATH_LOCAL([.])
AC_WITH_VCSN


# Awk is used.
AC_PROG_AWK

# Libtool used
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# Where the install Emacs files.
AM_PATH_LISPDIR

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


## ------------ ##
## Components.  ##
## ------------ ##

AC_CONFIG_SUBDIRS([argp])


## ------- ##
## TAF-Kit ##
## ------- ##

AC_CONFIG_FILES([
	taf-kit/Makefile
	  taf-kit/src/Makefile
	  taf-kit/tests/Makefile
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
VCSN_CONFIG_WRAPPER([vcsn-b])
VCSN_CONFIG_WRAPPER([vcsn-tdc])
VCSN_CONFIG_WRAPPER([vcsn-z])



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
	    data/automata/b/Makefile
	    data/automata/tdc/Makefile
	    data/automata/tdc-rw/Makefile
	    data/automata/z/Makefile
	lib/Makefile
	src/Makefile
	  src/demos/Makefile
	    src/demos/vgrep/Makefile
	    src/demos/function_library/Makefile
	    src/demos/algorithms/Makefile
	    src/demos/one_rule_rewriting/Makefile
	  src/benchs/Makefile
	    src/benchs/common/Makefile
	    src/benchs/determinization/Makefile
	    src/benchs/minimization_debruijn/Makefile
	    src/benchs/minimization_2n/Makefile
	    src/benchs/quotient/Makefile
	    src/benchs/composition/Makefile
	    src/benchs/derived_terms/Makefile
	include/Makefile])

m4_include([build-aux/tests.m4])

AC_SUBST([VCSN_TESTS_SUBDIRS])

AC_OUTPUT
