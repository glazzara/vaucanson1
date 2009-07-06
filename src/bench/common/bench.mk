# Makefile.flags -*- Makefile -*-

include $(top_srcdir)/vaucanson.mk

AM_CPPFLAGS += -I$(top_srcdir)/src/bench -I$(top_builddir)/src/bench
AM_CPPFLAGS += -DVCSN_SRC_DIR="\"$(top_srcdir)\""
AM_CPPFLAGS += -DNDEBUG -O3 -DVCSN_BENCH
