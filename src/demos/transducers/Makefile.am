# Makefile.am
#
# $Id: Makefile.am 462 2004-03-31 21:55:16Z yann $
include $(top_srcdir)/src/vaucanson.mk

SUBDIRS = one_rule_rewriting

AM_CPPFLAGS += -DVCSN_XSD_PATH="\"$(top_srcdir)/data/vaucanson.xsd\""

EXTRA_PROGRAMS = u1 t1

if VCSN_USE_XML
demos: $(EXTRA_PROGRAMS)
else
demos:
endif

XML_SAMPLES = $(srcdir)/u1.xml $(srcdir)/t1.xml
EXTRA_DIST = $(XML_SAMPLES)
MAINTAINERCLEANFILES = $(XML_SAMPLES)

u1_SOURCES = u1.cc
t1_SOURCES = t1.cc

$(srcdir)/u1.xml: u1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) u1$(EXEEXT)
	./u1$(EXEEXT) > $@

$(srcdir)/t1.xml: t1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) t1$(EXEEXT)
	./t1$(EXEEXT) > $@
