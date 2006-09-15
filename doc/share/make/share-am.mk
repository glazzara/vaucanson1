# Make sure we don't become promoted as default target.
all:

share_dir ?= $(srcdir)/share
share_bin_dir = $(share_dir)/bin
share_make_dir = $(share_dir)/make

CLEANFILES ?=

update:
	echo "*** Use \`make share-up' instead of \`make update' ***"
	$(MAKE) share-up

share-up:
	cd $(share_dir)/.. && share/bin/update-share

share-ci:
	cd $(share_dir) && vcs-svn ci
	$(MAKE) share-up

.PHONY: share-ci share-up

mostlyclean-local:
	rm -f *~
