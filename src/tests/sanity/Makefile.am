## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009 The Vaucanson Group.
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

EXTRA_DIST = generate_files.sh hhck.pl

# Note: use -DBENCH_DISABLED to disable libbench
AM_CPPFLAGS = -I$(top_srcdir)/include			\
	      -I$(top_builddir)/include			\
	      -I$(top_srcdir)/cbs/include		\
	      -I$(top_builddir)/cbs/include		\
	      $(BOOST_CPPFLAGS) -DVCSN_SANITY_CHECK
AM_CXXFLAGS = $(CXXFLAGS_STRICT)
LDADD = $(top_builddir)/lib/libvcsn-common.la

# FIXME: Currently files are generated in srcdir, they should be in builddir,
# and generated from the Makefile.am.
include check-programs.mk

# We don't run the resulting tests, there is no point in doing so, as
# they just check that the syntax is ok.
# Note: libbench.la is not linked since the tests are not run.



.PHONY: hhck
hhck:
	$(srcdir)/hhck.pl $(top_srcdir)/include/vaucanson/algorithms/*.hh

check-local: hhck
