# CBS, a C++ benchmarking suite.
#
# Copyright (C) 2007, 2009 The CBS Authors.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# The complete GNU General Public Licence Notice can be found as the
# `COPYING' file in the root directory.
#
# The CBS Authors consists of people listed in the `AUTHORS' file.

AC_PREREQ(2.61)
AC_INIT([cbs], [0.1], d-halluin@lrde.epita.fr)

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([lib])

AM_INIT_AUTOMAKE([1.10 tar-ustar no-define dist-bzip2])

# Checks for programs.
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_HEADER_TIME

# Checks for library functions.

AC_CONFIG_FILES([
	Makefile
	lib/Makefile
	include/Makefile
	demo/Makefile
	  demo/comparison/Makefile
	  demo/timer/Makefile
	  demo/timer-bench/Makefile
	  demo/memplot-bench/Makefile
	  demo/memplot/Makefile
	  demo/bench/Makefile])

AC_OUTPUT
