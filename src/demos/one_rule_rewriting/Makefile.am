# Makefile.am
#
# $Id$

AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

noinst_PROGRAMS = fibonacci_demo fibonacci_rt fibonacci_tdc ORR_demo ORR_rt \
	ORR_tdc

fibonacci_demo_SOURCES = fibonacci_demo.cc

fibonacci_rt_SOURCES = fibonacci_rt_gen.cc

fibonacci_tdc_SOURCES = fibonacci_tdc_gen.cc

ORR_demo_SOURCES = ORR_demo.cc

ORR_rt_SOURCES = ORR_rt_gen.cc

ORR_tdc_SOURCES = ORR_tdc_gen.cc
