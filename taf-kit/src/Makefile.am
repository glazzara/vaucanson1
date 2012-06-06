## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008,
## 2009, 2010, 2011, 2012 The Vaucanson Group.
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

bin_PROGRAMS = vcsn-char-b vcsn-char-z vcsn-char-r vcsn-char-fmp-b 	\
               vcsn-int-b vcsn-int-z vcsn-int-fmp-b vcsn-char-f2	\
	       vcsn-int-fmp-z vcsn-char-fmp-z 				\
	       vcsn-char-char-b vcsn-char-char-z			\
	       vcsn-int-int-b vcsn-int-int-z				\
	       vcsn-char-int-b vcsn-char-zmin vcsn-char-zmax		\
	       vcsn-char-q

COMMON_SOURCES = commands.hh			\
		 commands.cc			\
		 common.hh			\
		 cmd_io.cc			\
		 cmd_gen.cc			\
		 edition_commands.hh		\
		 edition_commands.hxx		\
		 library_commands.hh		\
		 getters.hh			\
		 getters.hxx			\
		 getters.cc			\
		 main.cc			\
		 predefined_alphabets.hh	\
		 predefined_alphabets.hxx	\
		 pipe.hh			\
		 pipe.hxx			\
		 pipe_command_sequence.hh	\
		 pipe_command_sequence.hxx	\
		 pipe_getters.hh		\
		 pipe_getters.hxx		\
		 pipe_writers.hh		\
		 pipe_writers.hxx		\
		 parser_options.hh		\
		 parser_options.hxx		\
		 boost_spirit_compatibility.hh


vcsn_char_b_SOURCES = $(COMMON_SOURCES) cmd_wt.cc cmd_b.cc
vcsn_char_b_CPPFLAGS = $(AM_CPPFLAGS) -DDUPBOOL \
		       -DCONTEXTS='"char-b", "char-b", "char-fmp-b"' \
		       -DCONTEXT=boolean_automaton \
		       -DBOOL_CONTEXT=boolean_automaton -DBOOL_DIR='"char-b"' \
		       -DFMPI_CONTEXT=fmp_transducer -DVCSN_USE_LIB
vcsn_char_b_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-b.la \
		    $(top_builddir)/lib/libvcsn-fmp-tdc.la

vcsn_char_z_SOURCES = $(COMMON_SOURCES) cmd_wt.cc
vcsn_char_z_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=z_automaton \
		       -DCONTEXTS='"char-z", "char-b", "char-fmp-z"' \
		       -DBOOL_CONTEXT=boolean_automaton -DBOOL_DIR='"char-b"' \
		       -DFMPI_CONTEXT=z_fmp_transducer -DVCSN_USE_LIB \
			-DWITH_WEIGHTS
vcsn_char_z_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-z.la \
		    $(top_builddir)/lib/libvcsn-z-fmp-tdc.la

vcsn_char_r_SOURCES = $(COMMON_SOURCES)	cmd_wt.cc cmd_r.cc
vcsn_char_r_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=r_automaton \
		       -DCONTEXTS='"char-r", "char-b", "char-fmp-r"' \
		       -DBOOL_CONTEXT=boolean_automaton -DBOOL_DIR='"char-b"' \
		       -DVCSN_USE_LIB -DWITH_WEIGHTS
vcsn_char_r_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-r.la

vcsn_char_q_SOURCES = $(COMMON_SOURCES)	cmd_wt.cc cmd_r.cc
vcsn_char_q_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=q_automaton \
		       -DCONTEXTS='"char-q", "char-b", "char-fmp-q"' \
		       -DBOOL_CONTEXT=boolean_automaton -DBOOL_DIR='"char-b"' \
		       -DVCSN_USE_LIB -DWITH_WEIGHTS
vcsn_char_q_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-q.la

vcsn_char_f2_SOURCES = $(COMMON_SOURCES) cmd_wt.cc cmd_r.cc
vcsn_char_f2_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=f2_automaton \
			-DCONTEXTS='"char-f2", "char-b", "char-fmp-f2"' \
			-DBOOL_CONTEXT=boolean_automaton -DBOOL_DIR='"char-b"' \
			-DVCSN_USE_LIB -DWITH_WEIGHTS
vcsn_char_f2_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-f2.la

vcsn_char_fmp_b_SOURCES = $(COMMON_SOURCES) cmd_fmp.cc
vcsn_char_fmp_b_CPPFLAGS = $(AM_CPPFLAGS) \
			    -DCONTEXTS='"char-fmp-b", "char-b", "char-char-b", "char-b", "char-b", "char-rw-char-b"' \
			    -DCONTEXT=fmp_transducer -DWITH_TWO_ALPHABETS \
			    -DIOAUT_NAME='"Boolean"' \
			    -DIOAUT_CONTEXT=boolean_automaton \
			    -DBOOL_CONTEXT=boolean_automaton \
			    -DBOOL_DIR='"char-b"' -DDUPBOOL \
			    -DRW_CONTEXT=boolean_transducer -DVCSN_USE_LIB
vcsn_char_fmp_b_LDADD = $(LDADD) \
			 $(top_builddir)/lib/libvcsn-fmp-tdc.la \
			 $(top_builddir)/lib/libvcsn-b.la \
			 $(top_builddir)/lib/libvcsn-char-char-b.la

vcsn_char_fmp_z_SOURCES = $(COMMON_SOURCES) cmd_fmp.cc
vcsn_char_fmp_z_CPPFLAGS = $(AM_CPPFLAGS) \
			    -DCONTEXTS='"char-fmp-z", "char-fmp-b", "char-char-z", "char-z", "char-z", "char-rw-char-z"' \
			    -DCONTEXT=z_fmp_transducer -DWITH_TWO_ALPHABETS \
			    -DIOAUT_NAME='"Z"' \
			    -DIOAUT_CONTEXT=z_automaton \
			    -DBOOL_CONTEXT=boolean_automaton \
			    -DBOOL_DIR='"char-b"' \
			    -DRW_CONTEXT=z_transducer -DVCSN_USE_LIB \
			    -DWITH_WEIGHTS
vcsn_char_fmp_z_LDADD = $(LDADD) \
			 $(top_builddir)/lib/libvcsn-z-fmp-tdc.la \
			 $(top_builddir)/lib/libvcsn-z.la \
                         $(top_builddir)/lib/libvcsn-char-char-z.la

vcsn_int_b_SOURCES = $(COMMON_SOURCES) cmd_wt.cc cmd_b.cc
vcsn_int_b_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=int_boolean_automaton \
		      -DCONTEXTS='"int-b", "int-b", "int-fmp-b"' \
		      -DBOOL_CONTEXT=int_boolean_automaton \
		      -DBOOL_DIR='"int-b"' -DDUPBOOL \
		      -DFMPI_CONTEXT=int_fmp_transducer \
                      -DNO_PREDEF_ALPHABETS -DVCSN_USE_LIB
vcsn_int_b_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-int-b.la \
		   $(top_builddir)/lib/libvcsn-int-fmp-tdc.la

vcsn_int_z_SOURCES = $(COMMON_SOURCES) cmd_wt.cc
vcsn_int_z_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=int_z_automaton \
		      -DCONTEXTS='"int-z", "int-z", "int-fmp-z"' \
		      -DBOOL_CONTEXT=int_boolean_automaton \
		      -DBOOL_DIR='"int-b"' \
		      -DFMPI_CONTEXT=int_z_fmp_transducer \
                      -DNO_PREDEF_ALPHABETS -DVCSN_USE_LIB \
		      -DWITH_WEIGHTS
vcsn_int_z_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-int-z.la \
		   $(top_builddir)/lib/libvcsn-int-z-fmp-tdc.la

vcsn_int_fmp_b_SOURCES = $(COMMON_SOURCES) cmd_fmp.cc
vcsn_int_fmp_b_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=int_fmp_transducer \
			   -DCONTEXTS='"int-fmp-b", "int-fmp-b", "int-int-b", "int-b", "int-b", "int-rw-int-b"' \
			   -DNO_PREDEF_ALPHABETS -DWITH_TWO_ALPHABETS \
			   -DIOAUT_NAME='"Boolean"' \
			   -DIOAUT_CONTEXT=int_boolean_automaton \
			   -DBOOL_CONTEXT=int_boolean_automaton \
			   -DBOOL_DIR='"int-b"' \
			   -DDUPBOOL \
			   -DRW_CONTEXT=int_boolean_transducer -DVCSN_USE_LIB
vcsn_int_fmp_b_LDADD = $(LDADD) \
			$(top_builddir)/lib/libvcsn-int-b.la \
			$(top_builddir)/lib/libvcsn-int-fmp-tdc.la \
			$(top_builddir)/lib/libvcsn-int-int-b.la

vcsn_int_fmp_z_SOURCES = $(COMMON_SOURCES) cmd_fmp.cc
vcsn_int_fmp_z_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=int_z_fmp_transducer \
			   -DCONTEXTS='"int-fmp-z", "int-fmp-b", "int-int-z", "int-z", "int-z", "int-rw-int-z"' \
			   -DNO_PREDEF_ALPHABETS -DWITH_TWO_ALPHABETS \
			   -DIOAUT_NAME='"Z"' \
			   -DIOAUT_CONTEXT=int_z_automaton \
			   -DRW_CONTEXT=int_z_transducer -DWITH_WEIGHTS \
			   -DBOOL_CONTEXT=int_boolean_automaton \
			   -DBOOL_DIR='"int-b"' \
			   -DVCSN_USE_LIB
vcsn_int_fmp_z_LDADD = $(LDADD) \
			$(top_builddir)/lib/libvcsn-int-z.la \
			$(top_builddir)/lib/libvcsn-int-z-fmp-tdc.la \
			$(top_builddir)/lib/libvcsn-int-int-z.la

vcsn_char_char_b_SOURCES = $(COMMON_SOURCES) cmd_wt.cc cmd_b.cc cmd_pair.cc
vcsn_char_char_b_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=char_char_boolean_automaton \
			      -DCONTEXTS='"char-char-b", "char-char-b", "char-fmp-b", "char-b", "char-b"' \
			      -DBOOL_CONTEXT=char_char_boolean_automaton \
			      -DBOOL_DIR='"char-char-b"' \
			      -DDUPBOOL \
			      -DVCSN_USE_LIB -DNO_PREDEF_ALPHABETS \
			      -DFMP_CONTEXT=fmp_transducer \
			      -DFIRST_PROJECTION_CONTEXT=boolean_automaton \
			      -DSECOND_PROJECTION_CONTEXT=boolean_automaton \
			      -DNO_SECOND_OPERATOR
vcsn_char_char_b_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-char-char-b.la

vcsn_char_char_z_SOURCES = $(COMMON_SOURCES) cmd_wt.cc cmd_pair.cc
vcsn_char_char_z_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=char_char_z_automaton \
			      -DCONTEXTS='"char-char-z", "char-char-b", "char-fmp-z", "char-z", "char-z"' \
			      -DBOOL_CONTEXT=char_char_boolean_automaton \
			      -DBOOL_DIR='"char-char-b"' \
			      -DVCSN_USE_LIB -DNO_PREDEF_ALPHABETS \
			      -DFMP_CONTEXT=z_fmp_transducer \
			      -DFIRST_PROJECTION_CONTEXT=z_automaton \
			      -DSECOND_PROJECTION_CONTEXT=z_automaton \
			      -DNO_SECOND_OPERATOR
vcsn_char_char_z_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-char-char-z.la

vcsn_char_int_b_SOURCES = $(COMMON_SOURCES) cmd_wt.cc cmd_b.cc cmd_pair.cc
vcsn_char_int_b_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=char_int_boolean_automaton \
			      -DCONTEXTS='"char-int-b", "char-int-b", "unsupported", "char-b", "int-b"' \
			      -DBOOL_CONTEXT=char_int_boolean_automaton \
			      -DBOOL_DIR='"char-int-b"' \
			      -DDUPBOOL \
			      -DVCSN_USE_LIB -DNO_PREDEF_ALPHABETS \
			      -DFIRST_PROJECTION_CONTEXT=boolean_automaton \
			      -DSECOND_PROJECTION_CONTEXT=int_boolean_automaton
vcsn_char_int_b_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-char-int-b.la

vcsn_int_int_b_SOURCES = $(COMMON_SOURCES) cmd_wt.cc cmd_b.cc cmd_pair.cc
vcsn_int_int_b_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=int_int_boolean_automaton \
			    -DCONTEXTS='"int-int-b", "int-int-b", "int-fmp-b", "int-b", "int-b"' \
			    -DBOOL_CONTEXT=int_int_boolean_automaton \
			    -DBOOL_DIR='"int-int-b"' \
			    -DDUPBOOL \
			    -DVCSN_USE_LIB -DNO_PREDEF_ALPHABETS \
			    -DFMP_CONTEXT=int_fmp_transducer \
			    -DFIRST_PROJECTION_CONTEXT=int_boolean_automaton \
			    -DSECOND_PROJECTION_CONTEXT=int_boolean_automaton \
			    -DNO_SECOND_OPERATOR
vcsn_int_int_b_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-int-int-b.la

vcsn_int_int_z_SOURCES = $(COMMON_SOURCES) cmd_wt.cc cmd_pair.cc
vcsn_int_int_z_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=int_int_z_automaton \
			    -DCONTEXTS='"int-int-z", "int-int-b", "fmp-int-z", "int-z", "int-z"' \
			    -DBOOL_CONTEXT=int_int_boolean_automaton \
			    -DBOOL_DIR='"int-int-b"' \
			    -DVCSN_USE_LIB -DNO_PREDEF_ALPHABETS \
			    -DFMP_CONTEXT=int_z_fmp_transducer \
			    -DFIRST_PROJECTION_CONTEXT=int_z_automaton \
			    -DSECOND_PROJECTION_CONTEXT=int_z_automaton \
			    -DNO_SECOND_OPERATOR
vcsn_int_int_z_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-int-int-z.la

vcsn_char_zmin_SOURCES = $(COMMON_SOURCES) cmd_wt.cc
vcsn_char_zmin_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=z_min_plus_automaton \
			    -DCONTEXTS='"char-zmin", "char-b", "char-fmp-zmin"' \
			    -DBOOL_CONTEXT=boolean_automaton \
			    -DBOOL_DIR='"char-b"' \
			    -DVCSN_USE_LIB -DWITH_WEIGHTS
vcsn_char_zmin_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-z-min.la

vcsn_char_zmax_SOURCES = $(COMMON_SOURCES) cmd_wt.cc
vcsn_char_zmax_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=z_max_plus_automaton \
			    -DCONTEXTS='"char-zmax", "char-b", "char-fmp-zmax"' \
			    -DBOOL_CONTEXT=boolean_automaton \
			    -DBOOL_DIR='"char-b"' \
			    -DVCSN_USE_LIB -DWITH_WEIGHTS
vcsn_char_zmax_LDADD = $(LDADD) $(top_builddir)/lib/libvcsn-z-max.la

LDADD = \
  $(benchlib) \
  $(top_builddir)/gnulib/libgnu.la \
  $(top_builddir)/lib/libvcsn-common-ex.la
AM_CPPFLAGS += -I$(top_srcdir)/gnulib
