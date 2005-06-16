# Makefile.am
#
# $Id$

AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

noinst_PROGRAMS = fibonacci fibo_demo fibo_fmp_demo one_rule_rewriting

fibonacci_SOURCES = fibonacci.cc

fibo_demo_SOURCES = fibonacci_demo.cc

fibo_fmp_demo_SOURCES = fibonacci_fmp_demo.cc

one_rule_rewriting_SOURCES = one_rule_rewriting.cc
