# Makefile.am
#
#
# $Id$

AUTOMAKE_OPTIONS = foreign 1.6
SUBDIRS = include src doc vauc
EXTRA_DIST = THANKS README LICENCE ChangeLog tools/scandefs.pl vcsn.m4

.PHONY: doc

doc:
	cd doc && $(MAKE) doc

ACLOCAL_AMFLAGS = -I .
CONFIGURE_DEPENDENCIES = $(srcdir)/vcsn.m4

