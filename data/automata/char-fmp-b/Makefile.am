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

noinst_PROGRAMS = t1 u1
bin_PROGRAMS = quotkbaseb-char-fmp-b ORR-char-fmp-b

nodist_char_fmp_b_automata_DATA =		\
	t1.xml					\
	u1.xml					\
	quot3base2.xml				\
	fibred_right.xml			\
	fibred_left.xml

CLEANFILES += $(nodist_char_fmp_b_automata_DATA)

t1_CPPFLAGS = $(AM_CPPFLAGS)
t1_SOURCES = t1.cc

t1.xml: t1$(EXEEXT)
	./t1$(EXEEXT) >$@.tmp
	mv $@.tmp $@

u1_CPPFLAGS = $(AM_CPPFLAGS)
u1_SOURCES = u1.cc

u1.xml: u1$(EXEEXT)
	./u1$(EXEEXT) >$@.tmp
	mv $@.tmp $@

quotkbaseb_char_fmp_b_CPPFLAGS = $(AM_CPPFLAGS)
quotkbaseb_char_fmp_b_SOURCES = quotkbaseb.cc

quot3base2.xml: quotkbaseb-char-fmp-b$(EXEEXT)
	./quotkbaseb-char-fmp-b$(EXEEXT) 3 2 >$@.tmp
	mv $@.tmp $@

ORR_char_fmp_b_CPPFLAGS = $(AM_CPPFLAGS)
ORR_char_fmp_b_SOURCES = ORR.cc

fibred_right.xml: ORR-char-fmp-b$(EXEEXT)
	./ORR-char-fmp-b$(EXEEXT) abb baa fibred xml

fibred_left.xml: fibred_right.xml
