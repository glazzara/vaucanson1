# Makefile.am
#
# $Id$

SUBDIRS = ciaa universal vgrep fibonacci samples xml $(VCSN_VAUCANSWIG_SUBDIR)

# Fastest way to install all .cc demo files.
# FIXME: Should provide a tiny Makefile for all directories
install-data-hook:
	files=`find . -name *.cc`; \
	for i in $$files; do \
	  $(mkinstalldirs) "$(DESTDIR)$(pkgdatadir)/`dirname $$i`"; \
	  cp "$$i" "$(DESTDIR)$(pkgdatadir)/$$i"; \
	done
