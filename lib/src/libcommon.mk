## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2008, 2009 The Vaucanson Group.
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
  src/krat_exp/krat_exp_bison.tab.cc
FROM_KRAT_EXP_BISON_YY_OTHERS = \
  src/krat_exp/stack.hh \
  src/krat_exp/position.hh \
  src/krat_exp/location.hh \
  src/krat_exp/krat_exp_bison.tab.hh
FROM_KRAT_EXP_BISON_YY = \
  $(FROM_KRAT_EXP_BISON_YY_MAIN) \
  $(FROM_KRAT_EXP_BISON_YY_OTHERS)

BUILT_SOURCES = $(FROM_KRAT_EXP_BISON_YY)
MAINTAINERCLEANFILES += $(FROM_KRAT_EXP_BISON_YY)

$(FROM_KRAT_EXP_BISON_YY_MAIN): $(srcdir)/src/krat_exp/$(KRAT_EXP_BISON_YY)
## We must cd into $(srcdir)/src/krat_exp/ first because if we tell
## bison to read $(srcdir)/src/krat_exp/$(KRAT_EXP_BISON_YY), it
## will also use the value of $(srcdir)/src/krat_exp/ in the
## generated include statements.
	cd $(srcdir)/src/krat_exp && bison $(KRAT_EXP_BISON_YY)
$(FROM_KRAT_EXP_BISON_YY_OTHERS): $(FROM_KRAT_EXP_BISON_YY_MAIN)
	@test -f $@ || $(MAKE) $(AM_MAKEFLAGS) $(FROM_KRAT_EXP_BISON_YY_MAIN)

EXTRA_DIST = src/krat_exp/$(KRAT_EXP_BISON_YY)

common_sources = \
  $(FROM_KRAT_EXP_BISON_YY) \
  src/misc/contract.cc

lib_LTLIBRARIES	+= libvcsn-common.la
libvcsn_common_la_LIBADD = $(LIBOBJS)
libvcsn_common_la_SOURCES = $(common_sources)
libvcsn_common_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/src/lib/krat_exp

lib_LTLIBRARIES	+= libvcsn-common-ex.la
libvcsn_common_ex_la_LIBADD = $(LIBOBJS)
libvcsn_common_ex_la_SOURCES = $(common_sources)
libvcsn_common_ex_la_CPPFLAGS = $(AM_CPPFLAGS) -DEXCEPTION_TRAPS \
                                -I$(top_srcdir)/src/lib/krat_exp
