# Process this file with automake to produce Makefile.in
# Written by Raphaël Poss <raph@lrde.epita.fr>
# Copyright (c) 2002 LRDE.

INCLUDES = -I$(srcdir)/../../include
KERN = -L../../kern -lcppshk
KIO = -L../../kern -lcppshio

check_PROGRAMS = t_obj t_obj2 t_sym t_exn t_io
TESTS = t_obj t_obj2 t_sym t_exn t_io

t_obj_SOURCES = object.cc
t_obj_LDADD = $(KERN) 

t_obj2_SOURCES = objref.cc objref_a.cc
t_obj2_LDADD = $(KERN)

t_sym_SOURCES = symbol.cc
t_sym_LDADD = $(KERN)

t_exn_SOURCES = exception.cc
t_exn_LDADD = $(KERN)

t_io_SOURCES = streams.cc
t_io_LDADD = $(KIO)

CLEANFILES = *.log
