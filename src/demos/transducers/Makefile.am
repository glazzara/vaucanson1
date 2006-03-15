# Makefile.am
#
# $Id: Makefile.am 462 2004-03-31 21:55:16Z yann $

SUBDIRS = one_rule_rewriting

if XML_CHECK
  AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
  AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

  EXTRA_PROGRAMS = u1 t1
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

endif XML_CHECK

all-am: vaucanson.xsd

vaucanson.xsd:
	ln -sf $(top_srcdir)/src/vaucanson.xsd $@
