## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2008 The Vaucanson Group.
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

EXTRA_DIST= krat_exp/krat_exp_bison.tab.hh \
	    krat_exp/stack.hh \
	    krat_exp/location.hh \
	    krat_exp/position.hh

lib_LTLIBRARIES	+= libkrat_exp.la
libkrat_exp_la_CXXFLAGS	= $(CXXFLAGS) -I$(top_srcdir)/lib/krat_exp
libkrat_exp_la_LIBADD	= $(LIBOBJS)
libkrat_exp_la_SOURCES	= krat_exp/krat_exp_bison.tab.cc

MAINTAINERCLEANFILES += $(libkrat_exp_la_SOURCES) \
			krat_exp/krat_exp_bison.tab.hh \
			krat_exp/stack.hh \
			krat_exp/location.hh \
			krat_exp/position.hh
