# Makefile.am
#
# $Id: Makefile.am 462 2004-03-31 21:55:16Z yann $

if XML_CHECK
  AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
  AM_CPPFLAGS = -I$(top_srcdir)/include		\
                -I$(top_builddir)/include	\
	        -I@XERCESC@/include
  AM_LDFLAGS = -lxerces-c -L@XERCESC@/lib

  noinst_PROGRAMS =				\
	static_boolean				\
	make_session				\
	display_session				\
	b					\
	z					\
	r					\
	z_max_plus				\
	z_min_plus
endif

static_boolean_SOURCES = static_boolean.cc
make_session_SOURCES = make_session.cc
display_session_SOURCES = display_session.cc

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
