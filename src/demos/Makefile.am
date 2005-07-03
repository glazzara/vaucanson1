# Makefile.am
#
# $Id$

if BUILD_DEMO
SUBDIRS =					\
	automaton_library			\
	function_library			\
	algorithms				\
	transducers   				\
	utilities				\
	$(VCSN_VAUCANSWIG_SUBDIR)
endif

# Fastest way to install all .cc demo files.
# FIXME: Should provide a tiny Makefile for all directories
install-data-hook:
	files=`find . -name *.cc`; \
	for i in $$files; do \
	  $(mkinstalldirs) "$(DESTDIR)$(pkgdatadir)/`dirname $$i`"; \
	  cp "$$i" "$(DESTDIR)$(pkgdatadir)/$$i"; \
	done
