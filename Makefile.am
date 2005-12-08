# Makefile.am
#
#
# $Id$

SUBDIRS = include doc src debian
EXTRA_DIST = vaucanson.spec

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
	touch $(distdir)/aclocal.m4 $(distdir)/config.hin $(distdir)/src/benchs
	rm -fR $(distdir)/src/benchs
	for f in configure.ac Makefile.am Makefile.in 		\
		 src/Makefile.am src/Makefile.in; do		\
	  true;							\
	  grep -v bench $(srcdir)/$$f > $(distdir)/$$f;		\
	done
	sed 's, src/bench[^ ]*, ,g' $(srcdir)/configure |	\
	    grep -v bench > $(distdir)/configure
	touch $(distdir)/src/demos/automaton_library/a1.xml	\
	$(distdir)/src/demos/automaton_library/b1.xml		\
	$(distdir)/src/demos/automaton_library/c1.xml		\
	$(distdir)/src/demos/transducers/u1.xml			\
	$(distdir)/src/demos/transducers/t1.xml
	cp $(srcdir)/doc/README.txt $(distdir)/README
	cp $(srcdir)/doc/NEWS.txt $(distdir)/NEWS

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

# Build debian packages.
deb:
	$(MAKE) -C debian deb

# Update headers.
rehead:
	find $(srcdir)/include -name '*.hh' -or -name '*.hxx' | \
	  xargs $(srcdir)/reheader.pl
