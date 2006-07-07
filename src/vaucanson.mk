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

## -I directories are consulted in the same order as the command
## line, so put build dirs first.
AM_CPPFLAGS = \
-I$(top_builddir) \
-I$(top_builddir)/include \
-I$(top_srcdir)/include

AM_CXXFLAGS = $(CXXFLAGS_STRICT)

## The directory where we store automata.
automatadir = $(pkgdatadir)/automata
b_automatadir = $(automatadir)/b
z_automatadir = $(automatadir)/z