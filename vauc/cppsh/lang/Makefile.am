# Process this file with automake to produce Makefile.in
# Written by Raphaël Poss <raph@lrde.epita.fr>
# Copyright (c) 2002 LRDE.

INCLUDES = -I$(srcdir)/../include

lib_LTLIBRARIES = libcppshls.la

libcppshls_la_SOURCES = \
	parse_base.cc lemon_parser.cc 

libcppshls_la_LIBADD = ../kern/libcppshk.la

noinst_HEADERS = \
	lemon_parser.hh 

EXTRA_DIST = \
	gen_parser.sh in2grammar.sh \
	parser_header.lemon parser_header.yy 

GENPARSER = $(srcdir)/gen_parser.sh
GENPARSERDEPS = $(GENPARSER) \
	$(srcdir)/in2grammar.sh \
	$(srcdir)/parser_header.lemon \
	$(srcdir)/parser_header.yy

#simple_parser.yy: $(GENPARSERDEPS) \
#	$(srcdir)/basic.prio \
#	$(srcdir)/basic.ruleset
#	$(SHELL) $(GENPARSER) $@ cppshSimpleParse \
#	  $(srcdir) basic basic

#simple_parser.lemon: $(GENPARSERDEPS) \
#	$(srcdir)/basic.prio \
#	$(srcdir)/basic.ruleset
#	$(SHELL) $(GENPARSER) $@ cppshSimpleParse \
#	  $(srcdir) basic basic

#ext_parser.yy: $(GENPARSERDEPS) \
#	$(srcdir)/language_ext.prio \
#	$(srcdir)/basic.ruleset \
#	$(srcdir)/language_ext.ruleset
#	$(SHELL) $(srcdir)/gen_parser.sh $@ cppshExtParse \
#	  $(srcdir) language_ext basic language_ext

#ext_parser.lemon: $(GENPARSERDEPS) \
#	$(srcdir)/language_ext.prio \
#	$(srcdir)/basic.ruleset \
#	$(srcdir)/language_ext.ruleset
#	$(SHELL) $(srcdir)/gen_parser.sh $@ cppshExtParse \
#	  $(srcdir) language_ext basic language_ext

#include $(top_srcdir)/lemon/rules.am

#YFLAGS = -v

#check_LTLIBRARIES = libyysimple_parser.la libyyext_parser.la
#libyysimple_parser_la_SOURCES = yysimple_parser.yy
#libyyext_parser_la_SOURCES = yyext_parser.yy

#CLEANFILES = \
#  ext_parser.out simple_parser.out \
#  ext_parser.output simple_parser.output

#BUILT_SOURCES = \
#  simple_parser.lemon ext_parser.lemon \
#  simple_parser.yy ext_parser.yy

#DISTCLEANFILES = \
#  simple_parser.cc simple_parser.h \
#  ext_parser.cc ext_parser.h

#EXTRA_DIST += simple_parser.yy ext_parser.yy

#yysimple_parser.yy: simple_parser.yy
#	rm -f $@
#	$(LN_S) `test -f '$<' || echo '$(srcdir)/'`$< $@

#yyext_parser.yy: ext_parser.yy
#	rm -f $@
#	$(LN_S) `test -f '$<' || echo '$(srcdir)/'`$< $@

