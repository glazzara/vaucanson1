# Make sure we don't become promoted as default target.
all:

share_dir ?= $(srcdir)/share
share_bin_dir = $(share_dir)/bin
share_make_dir = $(share_dir)/make

CLEANFILES =

SVN = vcs-svn

share-up:
	$(share_bin_dir)/svn-externals --update=share $(share_dir)/..

share-ci:
	cd $(share_dir) && $(SVN) ci .
	$(MAKE) share-up

.PHONY: share-ci share-up

mostlyclean-local:
	rm -f *~
