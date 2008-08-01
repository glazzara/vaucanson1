## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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

AM_CPPFLAGS += $(CXXFLAGS_OPTIMIZE)
AM_LDFLAGS = $(TERMLIBS)

bin_PROGRAMS = vcsn-char-b vcsn-char-z vcsn-char-fmp \
               vcsn-int-b vcsn-int-z

COMMON_SOURCES = commands.hh			\
		 commands_macros.hh		\
		 common_commands.hh		\
		 common.hh			\
		 edition_commands.hh		\
		 edition_commands.hxx		\
		 library_commands.hh		\
		 getters.hh			\
		 getters.hxx			\
		 interface.cc			\
		 interface.hh			\
		 main.cc			\
		 predefined_alphabets.hh	\
		 pipe.hh			\
		 pipe.hxx			\
		 pipe_command_sequence.hh	\
		 pipe_command_sequence.hxx	\
		 pipe_getters.hh		\
		 pipe_getters.hxx		\
		 pipe_writers.hh		\
		 pipe_writers.hxx		\
		 parser_options.hh		\
		 parser_options.hxx


vcsn_char_b_SOURCES = $(COMMON_SOURCES)			\
		      ratexp_commands.hh		\
	              common_automaton_commands.hh	\
                      b_commands.cc
vcsn_char_b_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=boolean_automaton -DVCSN_USE_LIB
vcsn_char_b_LDADD = $(LDADD)				\
		    $(top_builddir)/lib/libvcsn-b.la	\
		    $(top_builddir)/lib/libkrat_exp.la

vcsn_char_z_SOURCES = $(COMMON_SOURCES)			\
		      ratexp_commands.hh		\
                      common_automaton_commands.hh 	\
                      z_commands.cc
vcsn_char_z_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=z_automaton -DVCSN_USE_LIB
vcsn_char_z_LDADD = $(LDADD)				\
		  $(top_builddir)/lib/libvcsn-z.la	\
		  $(top_builddir)/lib/libkrat_exp.la

vcsn_char_fmp_SOURCES = $(COMMON_SOURCES) fmp_commands.cc
#vcsn_char_fmp_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=fmp_transducer 	\
#		    -DWITH_TWO_ALPHABETS -DVCSN_USE_LIB
vcsn_char_fmp_CPPFLAGS = $(AM_CPPFLAGS) \
		         -DCONTEXT=fmp_transducer -DWITH_TWO_ALPHABETS
vcsn_char_fmp_LDADD = $(LDADD) \
		      $(top_builddir)/lib/libvcsn-fmp-tdc.la \
		      $(top_builddir)/lib/libkrat_exp.la

vcsn_int_b_SOURCES = $(COMMON_SOURCES)			\
		      ratexp_commands.hh		\
	              common_automaton_commands.hh	\
                      b_commands.cc
vcsn_int_b_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=int_boolean_automaton \
                      -DNO_PREDEF_ALPHABETS
vcsn_int_b_LDADD = $(LDADD)				\
		    $(top_builddir)/lib/libkrat_exp.la

vcsn_int_z_SOURCES = $(COMMON_SOURCES)			\
		      ratexp_commands.hh		\
	              common_automaton_commands.hh	\
                      z_commands.cc
vcsn_int_z_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=int_z_automaton \
                      -DNO_PREDEF_ALPHABETS
vcsn_int_z_LDADD = $(LDADD)				\
		    $(top_builddir)/lib/libkrat_exp.la


## ------ ##
## argp.  ##
## ------ ##

# Be sure to fetch the argp we ship.
AM_CPPFLAGS += -I$(top_srcdir)/argp
LDADD = $(top_builddir)/argp/libargp.la
