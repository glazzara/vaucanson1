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

KRAT_EXP_BISON_YY = krat_exp_bison.yy

FROM_KRAT_EXP_BISON_YY_MAIN = \
  krat_exp/krat_exp_bison.tab.cc
FROM_KRAT_EXP_BISON_YY_OTHERS = \
  krat_exp/stack.hh \
  krat_exp/position.hh \
  krat_exp/location.hh \
  krat_exp/krat_exp_bison.tab.hh
FROM_KRAT_EXP_BISON_YY = \
  $(FROM_KRAT_EXP_BISON_YY_MAIN) \
  $(FROM_KRAT_EXP_BISON_YY_OTHERS)

BUILT_SOURCES = $(FROM_KRAT_EXP_BISON_YY)
MAINTAINERCLEANFILES += $(FROM_KRAT_EXP_BISON_YY)

$(FROM_KRAT_EXP_BISON_YY_MAIN): $(srcdir)/krat_exp/$(KRAT_EXP_BISON_YY)
## We must cd into $(srcdir)/krat_exp/ first because if we tell
## bison to read $(srcdir)/krat_exp/$(KRAT_EXP_BISON_YY), it
## will also use the value of $(srcdir)/krat_exp/ in the
## generated include statements.
	cd $(srcdir)/krat_exp && bison $(KRAT_EXP_BISON_YY)
$(FROM_KRAT_EXP_BISON_YY_OTHERS): $(FROM_KRAT_EXP_BISON_YY_MAIN)
	@test -f $@ || $(MAKE) $(AM_MAKEFLAGS) $(FROM_KRAT_EXP_BISON_YY_MAIN)

EXTRA_DIST = krat_exp/$(KRAT_EXP_BISON_YY)

lib_LTLIBRARIES	+= libkrat_exp.la
libkrat_exp_la_CXXFLAGS	= $(CXXFLAGS) -I$(top_srcdir)/lib/krat_exp
libkrat_exp_la_LIBADD	= $(LIBOBJS)
libkrat_exp_la_SOURCES	= $(FROM_KRAT_EXP_BISON_YY)
