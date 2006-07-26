## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License
## as published by the Free Software Foundation; either version 2
## of the License, or (at your option) any later version.
##
## The complete GNU General Public Licence Notice can be found as the
## `COPYING' file in the root directory.
##
## The Vaucanson Group consists of people listed in the `AUTHORS' file.

include $(top_srcdir)/vaucanson.mk

AM_CPPFLAGS += $(CXXFLAGS_STRICT)
AM_CXXFLAGS += -DINTERNAL_CHECKS -DSTRICT

EXTRA_PROGRAMS = 				\
	r					\
	z_max_plus				\
	z_min_plus				\
	tdc					\
	rt_tdc

if VCSN_USE_XML
demos: $(EXTRA_PROGRAMS)
else
demos:
endif

r_SOURCES = algorithms.cc
r_CPPFLAGS = $(AM_CPPFLAGS)				\
	-DCONTEXT_HEADER="<vaucanson/r_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::r_automaton"

z_max_plus_SOURCES = algorithms.cc
z_max_plus_CPPFLAGS = $(AM_CPPFLAGS)				\
	-DCONTEXT_HEADER="<vaucanson/z_max_plus_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_max_plus_automaton"

z_min_plus_SOURCES = algorithms.cc
z_min_plus_CPPFLAGS = $(AM_CPPFLAGS)				\
	-DCONTEXT_HEADER="<vaucanson/z_min_plus_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_min_plus_automaton"

tdc_SOURCES = tdc_algorithms.cc
tdc_CPPFLAGS = $(AM_CPPFLAGS)					\
	-DCONTEXT_HEADER="<vaucanson/fmp_transducer.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::fmp_transducer"

rt_tdc_SOURCES = rt_tdc_algorithms.cc
rt_tdc_CPPFLAGS = $(AM_CPPFLAGS)				\
	-DCONTEXT_HEADER="<vaucanson/boolean_transducer.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_transducer"
