# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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

AC_PREREQ([2.60])

AC_INIT([vaucanson], [1.0], [vaucanson-bugs@lrde.epita.fr])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.9.5 tar-ustar no-define foreign dist-bzip2 nostdinc])
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


## ------------ ##
## Vaucanswig.  ##
## ------------ ##

# SWIG and Python used.
AM_PATH_PYTHON([2.2])

AC_ARG_ENABLE([vaucanswig],
        [AC_HELP_STRING([--enable-vaucanswig],
			[enable building vaucanswig])],
	[WANT_INTERPRETER=$enableval],
        [WANT_INTERPRETER=no
	 AC_MSG_WARN([Vaucanswig  WILL NOT  be  built])])

VCSN_VAUCANSWIG_SUBDIR=""
if test "x$WANT_INTERPRETER" != "xno"; then
  AC_CHECK_SWIG13
  if test "x$ac_cv_recent_swig" != "xyes"; then
    AC_MSG_ERROR([You need swig >= 1.3 to compile vaucanswig.])
  else
    AC_CONFIG_FILES([vaucanswig/Makefile
 	             vaucanswig/doc/Makefile
 	             vaucanswig/meta/Makefile
                     vaucanswig/src/Makefile
                     vaucanswig/python/Makefile])
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
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_NAME], ["$PACKAGE_NAME"], [Full name.])
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_BUGREPORT], ["$PACKAGE_BUGREPORT"],
		   [Bug report address.])
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_STRING], ["$PACKAGE_STRING"],
		   [Full name and version.])
AC_DEFINE_UNQUOTED([VCSN_PACKAGE_VERSION], ["$PACKAGE_VERSION"], [Version.])


## ------------ ##
## Components.  ##
## ------------ ##

AC_CONFIG_SUBDIRS([argp])



## --------------- ##
## Documentation.  ##
## --------------- ##

# VCSN_ARG_PROGS(PROG, DOC)
# -------------------------
m4_define([VCSN_ARG_PROGS],
[AC_ARG_VAR(m4_toupper([$1]), [$2])
AC_CHECK_PROGS(m4_toupper([$1]), [$1], [$am_aux_dir/missing $1])
])


VCSN_ARG_PROGS([doxygen],   [the Doxygen documentation generation program])
VCSN_ARG_PROGS([texi2dvi],  [program to create DVI from TeX files])
VCSN_ARG_PROGS([rst2latex], [program to create TeX from reStructuredText documents])
VCSN_ARG_PROGS([rst2html],  [program to create HTML from reStructuredText documents])
VCSN_ARG_PROGS([tar],       [the tape archiver program])

AC_CONFIG_FILES([
   doc/Makefile
   doc/doc.doxy
	doc/manual/Makefile
	doc/makefiles/Makefile
	doc/xml/Makefile
])


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
## generate files.  ##
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
	include/Makefile
        debian/Makefile])

m4_include([build-aux/tests.m4])

AC_SUBST([VCSN_TESTS_SUBDIRS])
AC_SUBST([VCSN_VAUCANSWIG_SUBDIR])

AC_OUTPUT
