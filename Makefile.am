## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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

include $(top_srcdir)/vaucanson.mk

SUBDIRS = argp include src data taf-kit doc build-aux debian
if ENABLE_VAUCANSWIG
  SUBDIRS += vaucanswig
endif

EXTRA_DIST = vaucanson.spec ChangeLog.1 ChangeLog.2 README NEWS

# Prevent accidental edition of generated files.
$(srcdir)/README: cp $(srcdir)/doc/README.txt
	rm -f $(srcdir)/README
	cp $(srcdir)/doc/README.txt $(srcdir)/README
	chmod -w $(srcdir)/README

$(srcdir)/NEWS: $(srcdir)/doc/NEWS.txt
	rm -f $(srcdir)/NEWS
	cp $(srcdir)/doc/NEWS.txt $(srcdir)/NEWS
	chmod -w $(srcdir)/NEWS

# Be sure to use files up to date.
BUILT_SOURCES = include/vaucanson/config/pconf.hh


###
### Autoconf needs additional macros.
### Tell it where to find them.
###
ACLOCAL_AMFLAGS = -I build-aux

###
### Making the demos. (. is builddir)
###
demos:
	cd src/demos && $(MAKE) $(AM_MAKEFLAGS) demos

###
### For benchs. (. is builddir)
###
benchs:
	cd src/benchs && $(MAKE) $(AM_MAKEFLAGS) benchs

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

###
## FIXME: The following lines override Automake's native distcheck
## rule which is not good enough for us.  So we added "chmod -R a+w ..".
## Remove this once we use a fixed version of Automake.
###
# This target untars the dist file and tries a VPATH configuration.  Then
# it guarantees that the distribution is self-contained by making another
# tarfile.
distcheck: dist
	case '$(DIST_ARCHIVES)' in \
	*.tar.gz*) \
	  GZIP=$(GZIP_ENV) gunzip -c $(distdir).tar.gz | $(am__untar) ;;\
	*.tar.bz2*) \
	  bunzip2 -c $(distdir).tar.bz2 | $(am__untar) ;;\
	*.tar.Z*) \
	  uncompress -c $(distdir).tar.Z | $(am__untar) ;;\
	*.shar.gz*) \
	  GZIP=$(GZIP_ENV) gunzip -c $(distdir).shar.gz | unshar ;;\
	*.zip*) \
	  unzip $(distdir).zip ;;\
	esac
	chmod -R a-w $(distdir); chmod a+w $(distdir)
	mkdir $(distdir)/_build
	mkdir $(distdir)/_inst
	chmod a-w $(distdir)
	set -x ; \
	dc_install_base=`$(am__cd) $(distdir)/_inst && pwd | sed -e 's,^[^:\\/]:[\\/],/,'` \
	  && dc_destdir="$${TMPDIR-/tmp}/am-dc-$$$$/" \
	  && cd $(distdir)/_build \
	  && ../configure --srcdir=.. --prefix="$$dc_install_base" \
	    $(DISTCHECK_CONFIGURE_FLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) dvi \
	  && $(MAKE) $(AM_MAKEFLAGS) check \
	  && $(MAKE) $(AM_MAKEFLAGS) install \
	  && $(MAKE) $(AM_MAKEFLAGS) installcheck \
	  && $(MAKE) $(AM_MAKEFLAGS) uninstall \
	  && $(MAKE) $(AM_MAKEFLAGS) distuninstallcheck_dir="$$dc_install_base" \
	        distuninstallcheck \
	  && echo "$$dc_install_base" \
	  && chmod -R a-w "$$dc_install_base" \
	  && ({ \
	       (cd ../.. && umask 077 && mkdir "$$dc_destdir") \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" install \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" uninstall \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" \
	            distuninstallcheck_dir="$$dc_destdir" distuninstallcheck; \
	      } || { rm -rf "$$dc_destdir"; exit 1; }) \
	  && rm -rf "$$dc_destdir" \
	  && pwd \
	  && chmod -R a+w .. \
	  && $(MAKE) $(AM_MAKEFLAGS) dist \
	  && rm -rf $(DIST_ARCHIVES) \
	  && $(MAKE) $(AM_MAKEFLAGS) distcleancheck
	$(am__remove_distdir)
	@(echo "$(distdir) archives ready for distribution: "; \
	  list='$(DIST_ARCHIVES)'; for i in $$list; do echo $$i; done) | \
	  sed -e '1{h;s/./=/g;p;x;}' -e '$${p;x;}'


## ---------------------------- ##
## Installing on LRDE servers.  ##
## ---------------------------- ##

install-epita:
# If the dload directory does not exist, bail out.
	if test ! -d $(dloaddir); then			\
	  echo >&2 "no such directory: $(dloaddir)";	\
	fi
	cd doc && $(MAKE) $(AM_MAKEFLAGS) install-epita
.PHONY: install-epita
