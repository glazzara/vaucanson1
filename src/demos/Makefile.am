# Makefile.am
#
# $Id$

if BUILD_DEMO
SUBDIRS = ciaa universal vgrep fibonacci samples xml $(VCSN_VAUCANSWIG_SUBDIR)
endif

install-data-hook:
	files=`find . -name *.cc`; \
	for i in $$files; do \
	  $(mkinstalldirs) "$(DESTDIR)$(pkgdatadir)/`dirname $$i`"; \
	  cp "$$i" "$(DESTDIR)$(pkgdatadir)/$$i"; \
	done
