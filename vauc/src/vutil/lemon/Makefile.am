# Process this file with automake to produce Makefile.am
# Written by Raphaël Poss <raph@lrde.epita.fr>
# Copyright (c) 2002 LRDE.

noinst_PROGRAMS = lemon

lemon_SOURCES = lemon.c
lemon_DEPENDENCIES = lempar.c

DISTCLEANFILES = lempar.c
EXTRA_DIST = lempar.in rules.am

lempar.c: lempar.in
	$(LN_S) $(srcdir)/lempar.in $@
