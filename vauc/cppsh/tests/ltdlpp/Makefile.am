# Process this file with automake to produce Makefile.in
# Written by Raphaël Poss <raph@lrde.epita.fr>
# Copyright (c) 2002 LRDE.

INCLUDES = -I$(srcdir)/../../include -I$(top_srcdir)/ltdlpp
KERN = -L../../kern -lcppshk
LTDLPP = -L$(top_builddir)/ltdlpp -lltdlpp $(LIBLTDL)

noinst_HEADERS = s.hh

noinst_LTLIBRARIES = liba1.la libb1.la liba2.la libb2.la
noinst_PROGRAMS = t_dlbug1 t_dlbug2 t_dlbug3 t_dlbug12 t_dlbug22 t_dlbug32

t_dlbug1_SOURCES = dlbug1.cc
t_dlbug1_LDADD = $(KERN) $(LTDLPP) -dlopen liba1.la -dlopen libb1.la
t_dlbug2_SOURCES = dlbug2.cc
t_dlbug2_LDADD = $(KERN) $(LTDLPP) -dlopen liba1.la -dlopen libb1.la
t_dlbug3_SOURCES = dlbug3.cc
t_dlbug3_LDADD = $(KERN) $(LTDLPP) -dlopen liba1.la -dlopen libb1.la
t_dlbug12_SOURCES = dlbug1.cc
t_dlbug12_LDADD = $(KERN) $(LTDLPP) -dlopen liba2.la -dlopen libb2.la
t_dlbug22_SOURCES = dlbug2.cc
t_dlbug22_LDADD = $(KERN) $(LTDLPP) -dlopen liba2.la -dlopen libb2.la
t_dlbug32_SOURCES = dlbug3.cc
t_dlbug32_LDADD = $(KERN) $(LTDLPP) -dlopen liba2.la -dlopen libb2.la

liba1_la_SOURCES = abug1.cc
liba1_la_LDFLAGS = -rpath `pwd` -module
libb1_la_SOURCES = bbug1.cc
libb1_la_LDFLAGS = -rpath `pwd` -module
liba2_la_SOURCES = abug2.cc
liba2_la_LDFLAGS = -rpath `pwd` -module
libb2_la_SOURCES = bbug2.cc
libb2_la_LDFLAGS = -rpath `pwd` -module

CLEANFILES = *.log
