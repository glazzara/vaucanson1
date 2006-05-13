# Makefile.am
#
# $Id$

AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

EXTRA_PROGRAMS = vgrep

demos: vgrep

vgrep_SOURCES = vgrep.cc
