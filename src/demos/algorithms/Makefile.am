
# Makefile.am
#
# $Id: Makefile.am 486 2004-03-31 22:30:33Z yann $

EXTRA_DIST = equivalent_functions.hh

if XML_CHECK
  AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
  AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

all-am: vaucanson.xsd

vaucanson.xsd:
	ln -sf $(top_srcdir)/src/vaucanson.xsd $@

noinst_PROGRAMS = universal b_are_equivalent z_are_equivalent	\
	b_exp_equiv z_exp_equiv b_contains_factor z_contains_factor classics

endif

universal_SOURCES = universal.cc

b_are_equivalent_SOURCES = are_equivalent.cc equivalent_functions.cc
b_are_equivalent_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_automaton"

z_are_equivalent_SOURCES = are_equivalent.cc equivalent_functions.cc
z_are_equivalent_CPPFLAGS =  $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/z_automaton.hh>"		\
	-DCONTEXT_NAMESPACE="vcsn::z_automaton"

b_exp_equiv_SOURCES = exp_equiv.cc equivalent_functions.cc
b_exp_equiv_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_automaton"

z_exp_equiv_SOURCES = exp_equiv.cc equivalent_functions.cc
z_exp_equiv_CPPFLAGS =  $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/z_automaton.hh>"		\
	-DCONTEXT_NAMESPACE="vcsn::z_automaton"


b_contains_factor_SOURCES = contains_factor.cc equivalent_functions.cc
b_contains_factor_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_automaton"

z_contains_factor_SOURCES = contains_factor.cc equivalent_functions.cc
z_contains_factor_CPPFLAGS =  $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/z_automaton.hh>"		\
	-DCONTEXT_NAMESPACE="vcsn::z_automaton"

classics_SOURCES = classics.cc
