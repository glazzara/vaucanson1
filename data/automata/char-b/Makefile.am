## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009, 2011 The
## Vaucanson Group.
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

LDADD = $(top_builddir)/lib/libvcsn-common.la
AM_CPPFLAGS += -DBENCH_DISABLED

noinst_PROGRAMS = a1 b1
bin_PROGRAMS = divkbaseb-char-b ladybird-char-b doublering-char-b

nodist_char_b_automata_DATA =			\
  a1.xml					\
  b1.xml					\
  div3base2.xml					\
  ladybird-6.xml				\
  double-3-1.xml

CLEANFILES += $(nodist_char_b_automata_DATA)

a1_CPPFLAGS = $(AM_CPPFLAGS)
a1_SOURCES = a1.cc

a1.xml: a1$(EXEEXT)
	./a1$(EXEEXT) xml >$@.tmp
	mv $@.tmp $@

# Accepts words with a `b'.
# See ETA Fig. III.2.3, p. 434.
b1_CPPFLAGS = $(AM_CPPFLAGS)
b1_SOURCES = b1.cc
b1.xml: b1$(EXEEXT)
	./b1$(EXEEXT) xml >$@.tmp
	mv $@.tmp $@

divkbaseb_char_b_CPPFLAGS = $(AM_CPPFLAGS)
divkbaseb_char_b_SOURCES = divkbaseb.cc
div3base2.xml: divkbaseb-char-b$(EXEEXT)
	./divkbaseb-char-b$(EXEEXT) 3 2 xml >$@.tmp
	mv $@.tmp $@

ladybird_char_b_CPPFLAGS = $(AM_CPPFLAGS)
ladybird_char_b_SOURCES = ladybird.cc
ladybird-6.xml: ladybird-char-b$(EXEEXT)
	./ladybird-char-b$(EXEEXT) 6 xml >$@.tmp
	mv $@.tmp $@

doublering_char_b_CPPFLAGS = $(AM_CPPFLAGS)
doublering_char_b_SOURCES = double_ring.cc
double-3-1.xml: doublering-char-b$(EXEEXT)
	./doublering-char-b$(EXEEXT) 3 1 xml >$@.tmp
	mv $@.tmp $@
