# Makefile.am
#
# $Id$

SUBDIRS =					\
	automaton_library			\
	function_library			\
	algorithms				\
	transducers   				\
	utilities

demos:
	for dir in $(SUBDIRS); do		\
	  (cd "$$dir" && $(MAKE) $(AM_MAKEFLAGS) demos || exit 1); \
	done
