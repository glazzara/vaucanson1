## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License
## as published by the Free Software Foundation; either version 2
## of the License, or (at your option) any later version.
##
## The complete GNU General Public Licence Notice can be found as the
## `COPYING' file in the root directory.
##
## The Vaucanson Group consists of people listed in the `AUTHORS' file.

EXTRA_DIST = generate_files.sh

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include \
	      -DVCSN_SANITY_CHECK
AM_CXXFLAGS = $(CXXFLAGS_STRICT)

# Currently files are generated in srcdir, they should be in builddir,
# and generated from the Makefile.am.
include check-programs.mk

# It is actually unclear there is any point in running these programs.
# The whole point is rather to compile them.  Maybe we can just disable
# TESTS?
TESTS = $(check_PROGRAMS)
TEST_LOGS = $(check_PROGRAMS:=.log)
include $(top_srcdir)/build-aux/check.mk
