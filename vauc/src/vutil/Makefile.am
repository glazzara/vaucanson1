# parser/Makefile.am
#
#
INCLUDES = -I$(top_srcdir)/include

SUBDIRS = lemon

noinst_LTLIBRARIES = libvutil.la

libvutil_la_SOURCES = readlinebuf.cc
libvutil_la_LIBADD = $(LIBREADLINE) $(LIBHISTORY)

