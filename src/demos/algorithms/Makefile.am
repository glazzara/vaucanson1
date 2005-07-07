
# Makefile.am
#
# $Id: Makefile.am 486 2004-03-31 22:30:33Z yann $

EXTRA_DIST = equivalent_functions.hh

if XML_CHECK
  AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
  AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

all-am: vaucanson.xsd

vaucanson.xsd:
	ln -sf $(top_builddir)/doc/xml/vaucanson.xsd

noinst_PROGRAMS = universal b_are_equivalent z_are_equivalent	\
	b_exp_recognized z_exp_recognized classics

endif

universal_SOURCES = universal.cc

b_are_equivalent_SOURCES = are_equivalent.cc equivalent_functions.cc
b_are_equivalent_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_automaton"

z_are_equivalent_SOURCES = are_equivalent.cc equivalent_functions.cc
z_are_equivalent_CPPFLAGS =  $(AM_CPPFLAGS)		\
	-DCONTEXT_HEADER="<vaucanson/z_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_automaton"

b_exp_recognized_SOURCES = exp_recognized.cc equivalent_functions.cc
b_exp_recognized_CPPFLAGS = $(AM_CPPFLAGS)					\
	-DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_automaton"

z_exp_recognized_SOURCES = exp_recognized.cc equivalent_functions.cc
z_exp_recognized_CPPFLAGS =  $(AM_CPPFLAGS)				\
	-DCONTEXT_HEADER="<vaucanson/z_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_automaton"

classics_SOURCES = classics.cc
