## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2009 The Vaucanson Group.
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

include $(top_srcdir)/src/tests/check/check-flags.mk

# It should be check_LIBRARIES, but this is safer, in case we want to
# run check in a specific subdir.
noinst_LTLIBRARIES = libcheck.la

libcheck_la_SOURCES =			\
  tester.cc				\
  unique.cc

libcheck_a_LIBADD = $(top_builddir)/lib/libvcsn-common-ex.la
