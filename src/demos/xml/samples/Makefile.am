# Makefile.am
#
# $Id: $

EXTRA_PROGRAMS =				\
	c1					\
	divkbaseb				\
	double_ring				\
	occ_b					\
	lomb1					\
	lomb2

if XML_CHECK
  AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
  AM_CPPFLAGS = -I$(top_srcdir)/include		\
                -I$(top_builddir)/include	\
	        -I@XERCESC@/include
  AM_LDFLAGS = -lxerces-c -L@XERCESC@/lib

  noinst_PROGRAMS =				\
	divkbaseb				\
	double_ring
endif

vaucanson.dtd:
	ln -sf $(top_builddir)/xml/vaucanson.dtd

c1_SOURCES		= c1.cc
divkbaseb_SOURCES	= divkbaseb.cc
double_ring_SOURCES	= double_ring.cc
occ_b_SOURCES		= occ_b.cc
lomb1_SOURCES		= lomb1.cc
lomb2_SOURCES		= lomb2.cc

XML_SAMPLES =					\
	$(srcdir)/c1.xml			\
	$(srcdir)/div3base2.xml			\
	$(srcdir)/double_ring6.xml		\
	$(srcdir)/occ_b.xml			\
	$(srcdir)/lomb1.xml			\
	$(srcdir)/lomb2.xml

EXTRA_DIST = $(XML_SAMPLES)
MAINTAINERCLEANFILES = $(XML_SAMPLES)

$(srcdir)/c1.xml: c1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) c1$(EXEEXT) vaucanson.dtd
	./c1$(EXEEXT) > $@

$(srcdir)/div3base2.xml: divkbaseb.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) divkbaseb$(EXEEXT) vaucanson.dtd
	./divkbaseb$(EXEEXT) 3 2 > $@

$(srcdir)/double_ring6.xml: double_ring.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) double_ring$(EXEEXT) vaucanson.dtd
	./double_ring$(EXEEXT) 6 1 3 4 5 > $@

$(srcdir)/occ_b.xml: occ_b.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) occ_b$(EXEEXT) vaucanson.dtd
	./occ_b$(EXEEXT) > $@

$(srcdir)/lomb1.xml: lomb1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) lomb1$(EXEEXT) vaucanson.dtd
	./lomb1$(EXEEXT) > $@

$(srcdir)/lomb2.xml: lomb2.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) lomb2$(EXEEXT) vaucanson.dtd
	./lomb2$(EXEEXT) > $@
