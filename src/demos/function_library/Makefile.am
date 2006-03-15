# Makefile.am
#
# $Id: Makefile.am 462 2004-03-31 21:55:16Z yann $

if XML_CHECK
  AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
  AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

  noinst_PROGRAMS =				\
	b					\
	z					\
	r					\
	z_max_plus				\
	z_min_plus				\
	tdc					\
	rt_tdc
endif

all-am: vaucanson.xsd

vaucanson.xsd:
	ln -sf $(top_srcdir)/src/vaucanson.xsd $@

b_SOURCES = algorithms.cc
b_CPPFLAGS = $(AM_CPPFLAGS)					\
	-DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_automaton"

z_SOURCES = algorithms.cc
z_CPPFLAGS = $(AM_CPPFLAGS)				\
	-DCONTEXT_HEADER="<vaucanson/z_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_automaton"

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
