# Makefile.am
#
# $Id: Makefile.am 462 2004-03-31 21:55:16Z yann $


if XML_CHECK
  AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
  AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

  noinst_PROGRAMS = u1 t1

endif

vaucanson.xsd:
	ln -sf $(top_builddir)/doc/xml/vaucanson.xsd

u1_SOURCES = u1.cc

t1_SOURCES = t1.cc

