# Makefile.am
# $Id$

AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

noinst_PROGRAMS=derivatives_automaton determinize_standard classics

derivatives_automaton_SOURCES = derivatives_automaton.cc
determinize_standard_SOURCES = determinize_standard.cc
classics_SOURCES = classics.cc
