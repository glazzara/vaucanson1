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

include $(top_srcdir)/src/vaucanson.mk
# VCSN_USE_XML doesn't need to be checked as VCSN_TAF_KIT
# is not enabled if the former isn't.
AM_CPPFLAGS += $(CXXFLAGS_OPTIMIZE)
AM_LDFLAGS = $(TERMLIBS)

Progs = vcsn-b vcsn-z

if VCSN_TAF_KIT
  bin_PROGRAMS = $(Progs)
else
  EXTRA_PROGRAMS = $(Progs)
endif

COMMON_SOURCES = commands.hh			\
		 commands_macros.hh		\
		 common_commands.hh		\
		 common.hh			\
		 edit_automaton.hh		\
		 edit_automaton.hxx		\
		 getters.hh			\
		 getters.hxx			\
		 interface.cc			\
		 interface.hh			\
		 main.cc			\
		 predefined_alphabets.hh


vcsn_b_CPPFLAGS = $(AM_CPPFLAGS)					\
		  -DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"   \
		  -DCONTEXT_NAMESPACE="vcsn::boolean_automaton"

vcsn_z_CPPFLAGS = $(AM_CPPFLAGS)					\
		  -DCONTEXT_HEADER="<vaucanson/z_automaton.hh>"   	\
		  -DCONTEXT_NAMESPACE="vcsn::z_automaton"


vcsn_b_SOURCES = $(COMMON_SOURCES)		\
		 ratexp_commands.hh b_commands.cc

vcsn_z_SOURCES = $(COMMON_SOURCES)		\
		 ratexp_commands.hh z_commands.cc

## ------ ##
## argp.  ##
## ------ ##

# Be sure to fetch the argp we ship.
AM_CPPFLAGS += -I$(top_srcdir)/argp
vcsn_b_LDADD = $(top_builddir)/argp/libargp.la
