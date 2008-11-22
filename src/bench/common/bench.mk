# Makefile.flags -*- Makefile -*-
# $Id$

AM_CXXFLAGS = $(CXXFLAGS_OPTIMIZE)
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src/bench	\
	      -I$(top_builddir)/include -I$(top_builddir)/src/bench
AM_CPPFLAGS += -DEXCEPTION_TRAPS
AM_CPPFLAGS += -DVCSN_SRC_DIR=\"'\$(top_srcdir)'\"
AM_CPPFLAGS += -DNDEBUG -O3 -DVCSN_BENCH
