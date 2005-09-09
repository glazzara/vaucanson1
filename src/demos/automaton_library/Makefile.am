# Makefile.am
#
# $Id: Makefile.am 1005 2005-06-23 17:17:36Z o-conn_s $

AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

EXTRA_PROGRAMS = a1 b1 c1
noinst_PROGRAMS = divkbaseb double_ring ladybird

XML_SAMPLES = $(srcdir)/a1.xml $(srcdir)/b1.xml $(srcdir)/c1.xml
EXTRA_DIST = $(XML_SAMPLES)
MAINTAINERCLEANFILES = $(XML_SAMPLES)

a1_SOURCES = a1.cc
b1_SOURCES = b1.cc
c1_SOURCES = c1.cc
divkbaseb_SOURCES = divkbaseb.cc
double_ring_SOURCES = double_ring.cc
ladybird_SOURCES = ladybird.cc

$(srcdir)/a1.xml: a1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) a1$(EXEEXT)
	./a1$(EXEEXT) > $@

$(srcdir)/b1.xml: b1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) b1$(EXEEXT)
	./b1$(EXEEXT) > $@

$(srcdir)/c1.xml: c1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) c1$(EXEEXT)
	./c1$(EXEEXT) > $@
