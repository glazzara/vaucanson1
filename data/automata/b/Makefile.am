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

include $(top_srcdir)/vaucanson.mk

EXTRA_PROGRAMS = a1 b1 divkbaseb ladybird double_ring

dist_b_automata_DATA =				\
  $(srcdir)/a1.xml				\
  $(srcdir)/b1.xml				\
  $(srcdir)/div3base2.xml			\
  $(srcdir)/ladybird-6.xml			\
  $(srcdir)/double-3-1.xml

EXTRA_DIST = $(XML_SAMPLES)
MAINTAINERCLEANFILES = $(dist_b_automata_DATA)

a1_CPPFLAGS = $(AM_CPPFLAGS)
a1_SOURCES = a1.cc

$(srcdir)/a1.xml: a1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) a1$(EXEEXT)
	./a1$(EXEEXT) xml >$@.tmp
	mv $@.tmp $@

# Accepts words with a `b'.
# See ETA Fig. III.2.3, p. 434.
b1_CPPFLAGS = $(AM_CPPFLAGS)
b1_SOURCES = b1.cc
$(srcdir)/b1.xml: b1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) b1$(EXEEXT)
	./b1$(EXEEXT) xml >$@.tmp
	mv $@.tmp $@

divkbaseb_CPPFLAGS = $(AM_CPPFLAGS)
divkbaseb_SOURCES = divkbaseb.cc
$(srcdir)/div3base2.xml: divkbaseb.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) divkbaseb$(EXEEXT)
	./divkbaseb$(EXEEXT) 3 2 xml >$@.tmp
	mv $@.tmp $@

ladybird_CPPFLAGS = $(AM_CPPFLAGS)
ladybird_SOURCES = ladybird.cc
$(srcdir)/ladybird-6.xml: ladybird.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) ladybird$(EXEEXT)
	./ladybird$(EXEEXT) 6 xml >$@.tmp
	mv $@.tmp $@

double_ring_CPPFLAGS = $(AM_CPPFLAGS)
double_ring_SOURCES = double_ring.cc
$(srcdir)/double-3-1.xml: double_ring.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) double_ring$(EXEEXT)
	./double_ring$(EXEEXT) 3 1 xml >$@.tmp
	mv $@.tmp $@
