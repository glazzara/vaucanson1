# Makefile.am
#
# $Id: Makefile.am 462 2004-03-31 21:55:16Z yann $

## FIXME: What's the point of the utilities directory?

SUBDIRS = vgrep

demos:
	for dir in $(SUBDIRS); do               \
          (cd "$$dir" && $(MAKE) $(AM_MAKEFLAGS) demos); \
        done
