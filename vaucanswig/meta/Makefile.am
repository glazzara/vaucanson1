## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2003, 2004, 2006 The Vaucanson Group.
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

INCLUDES = -I$(srcdir) -I$(top_srcdir)/include -I$(top_builddir)/include

EXTRA_DIST =					\
	automaton.hh				\
	context.hh				\
	vaucanswig_algo_common.i		\
	vaucanswig_automaton.i			\
	vaucanswig_context.i			\
	vaucanswig_core.i			\
	vaucanswig_describe.i			\
	vaucanswig_exception.i			\
	vauto.hh				\
	vcontext.hh

lib_LTLIBRARIES = libvv.la

libvv_la_SOURCES = vcontext.cc vauto.cc
