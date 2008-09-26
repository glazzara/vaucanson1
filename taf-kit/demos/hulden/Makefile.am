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


EXTRA_DIST = run.in README

CLEANFILES = run
nodist_noinst_SCRIPTS = run

run: run.in Makefile.am
	sed 's|[@]builddir[@]|$(abs_builddir)|' $(srcdir)/run.in > $@
	chmod a+x $@

check-local: run
	./run --test
