# Make sure we don't become promoted as default target.
all:

share_dir ?= share
bin_dir = $(share_dir)/bin
make_dir = $(share_dir)/make

update:
	$(bin_dir)/update-share

mostly-clean:
	rm -f *~

clean: mostly-clean
