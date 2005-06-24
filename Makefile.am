# Makefile.am
#
#
# $Id$

SUBDIRS = include doc src
EXTRA_DIST = CONTRIBUTORS NOTICE

###
### Autoconf needs additional macros.
### Tell it where to find them.
###
ACLOCAL_AMFLAGS = -I config
CONFIGURE_DEPENDENCIES = $(srcdir)/config/vcsn.m4 $(srcdir)/config/vaucanson_xml.m4

###
### Autoconf macros are installable and distributable.
###
m4datadir = $(datadir)/aclocal
dist_m4data_DATA = config/vcsn.m4 config/vaucanson_xml.m4

###
### For benchs.
###
bench:
	cd $(srcdir)/src/benchs && make bench

dist-hook:
	rm -fR $(distdir)/src/benchs
	for f in configure.ac Makefile.am Makefile.in 		\
		 src/Makefile.am src/Makefile.in; do		\
	  true;							\
	  grep -v bench $(srcdir)/$$f > $(distdir)/$$f;		\
	done
	sed 's, src/bench[^ ]*, ,g' $(srcdir)/configure |	\
	    grep -v bench > $(distdir)/configure
	cp $(srcdir)/doc/README.txt $(distdir)/README
	cp $(srcdir)/doc/INSTALL.txt $(distdir)/INSTALL

###
### Sanity check.
###
sanity-check:
	cd $(srcdir)/src/tests/sanity && make check

###
### Check headers for sanity.
###

# This is totally experimental. Comments are welcome.
maintainer-check:
	if cppi --version >/dev/null 2>&1; then \
	  find $(srcdir)/include -name '*.hh' -or -name '*.hxx' | \
	    xargs cppi --check; \
	else \
	  echo "$@: GNU cppi is required" >&2; \
	fi
