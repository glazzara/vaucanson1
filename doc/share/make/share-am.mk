# Make sure we don't become promoted as default target.
all:

share_dir ?= share
bin_dir = $(share_dir)/bin
make_dir = $(share_dir)/make

update:
	cd $(share_dir)/.. && share/bin/update-share

mostlyclean-local:
	rm -f *~
