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

include $(top_srcdir)/src/vaucanson.mk

# Z automata.
EXTRA_PROGRAMS = c1

dist_z_automata_DATA =                         \
  $(srcdir)/c1.xml

MAINTAINERCLEANFILES = $(dist_z_automata_DATA)

c1_SOURCES = c1.cc
$(srcdir)/c1.xml: c1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) c1$(EXEEXT)
	./c1$(EXEEXT) xml >$@.tmp
	mv $@.tmp $@
