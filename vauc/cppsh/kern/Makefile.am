# Process this file with automake to produce Makefile.in
# Written by Raphaël Poss <raph@lrde.epita.fr>
# Copyright (c) 2002 LRDE.

INCLUDES = -I$(srcdir)/../include

lib_LTLIBRARIES = libcppshk.la libcppshio.la

libcppshk_la_SOURCES = \
	object.cc \
	objvect.cc \
	symbol.cc \
	exception.cc \
	exnprint.cc \
	debug.cc

libcppshio_la_SOURCES = \
	streams.cc \
	stdstreams_cin.cc \
	stdstreams_cout.cc \
	stdstreams_cerr.cc \
	fstreams.cc
EXTRA_DIST = \
	stdstreams_cin.hh \
	stdstreams_cout.hh \
	stdstreams_cerr.hh

libcppshio_la_LIBADD = libcppshk.la
