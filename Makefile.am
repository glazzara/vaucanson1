# Makefile.am
#
#
# $Id$

SUBDIRS = include doc src debian
EXTRA_DIST = vaucanson.spec ChangeLog.1 ChangeLog.2

###
### Autoconf needs additional macros.
### Tell it where to find them.
###
ACLOCAL_AMFLAGS = -I config
CONFIGURE_DEPENDENCIES = $(srcdir)/config/vcsn.m4 $(srcdir)/config/vcsn_xml.m4 $(srcdir)/config/tests.m4

###
### Autoconf macros are installable and distributable.
###
m4datadir = $(datadir)/aclocal
dist_m4data_DATA = config/vcsn.m4 config/vcsn_xml.m4

###
### For benchs.
###
bench:
	cd $(srcdir)/src/benchs && make bench

dist-hook:
	cp $(srcdir)/doc/README.txt $(distdir)/README
	cp $(srcdir)/doc/NEWS.txt $(distdir)/NEWS

###
### Sanity check.
###
sanity-check:
	cd $(srcdir)/src/tests/sanity && make check

###
### Check headers for sanity. Headers will check for VCSN_USE_XML.
###

find_headers = \
   find $(srcdir)/include -name '*.hh' \
	              -or -name '*.hxx' \
	              -or -name '*.thh' \
	              -or -name '*.txx'

# This is totally experimental. Comments are welcome.
maintainer-check:
	if cppi --version >/dev/null 2>&1; then \
	  $(find_headers) | \
	    xargs cppi --check; \
	else \
	  echo "$@: GNU cppi is required" >&2; \
	fi

# Build debian packages.
deb:
	$(MAKE) -C debian deb

# Update headers.
rehead:
	$(find_headers) | \
	  xargs perl $(srcdir)/reheader.pl
