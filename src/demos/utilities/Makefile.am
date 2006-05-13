# Makefile.am
#
# $Id: Makefile.am 462 2004-03-31 21:55:16Z yann $

SUBDIRS = vgrep

demos:
	for dir in $(SUBDIRS); do               \
          (cd "$dir" && $(MAKE) $(AM_MAKEFLAGS) demos); \
        done
