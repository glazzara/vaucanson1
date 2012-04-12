## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009 The Vaucanson Group.
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

## When _SOURCES is not specified, use PROGRAM.cc, not PROGRAM.c.
AM_DEFAULT_SOURCE_EXT = .cc

## -I directories are consulted in the same order as the command
## line, so put build dirs first.
AM_CPPFLAGS = \
-I$(top_builddir) \
-I$(top_builddir)/include \
-I$(top_srcdir)/include \
-I$(top_srcdir)/cbs/include \
-I$(top_builddir)/cbs/include

benchlib = $(top_builddir)/cbs/lib/libbench.la

AM_CXXFLAGS = $(CXXFLAGS_STRICT)

# Add this to CPPFLAGS to use the shipped data.
XSD_CPPFLAGS = -DVCSN_DATA_PATH="\"$(top_srcdir)/data\""

## Where we store automata.
automatadir = $(pkgdatadir)/automata
char_b_automatadir = $(automatadir)/char-b
char_char_b_automatadir = $(automatadir)/char-char-b
char_f2_automatadir = $(automatadir)/char-f2
char_fmp_b_automatadir = $(automatadir)/char-fmp-b
char_fmp_z_automatadir = $(automatadir)/char-fmp-z
char_q_automatadir = $(automatadir)/char-q$
char_r_automatadir = $(automatadir)/char-r
char_z_automatadir = $(automatadir)/char-z
char_zmin_automatadir = $(automatadir)/char-zmin
char_zmax_automatadir = $(automatadir)/char-zmax
int_b_automatadir = $(automatadir)/int-b
int_z_automatadir = $(automatadir)/int-z

## Where documentation is uploaded on EPITA servers.
dloaddir = /mnt/dload
vcsndldir = $(dloaddir)/vaucanson/$(VERSION)

## Simplify the use of CLEANFILES: always use +=.
CLEANFILES =
