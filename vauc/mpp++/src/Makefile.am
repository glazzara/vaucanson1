# Makefile.am
#
#

SUBDIRS = parse spec internal transformer

noinst_PROGRAMS = fun_trans ty_trans

INCLUDES = -I$(srcdir) -I$(top_srcdir)/lib
AM_CXXFLAGS = $(ZLIB_CXXFLAGS)
AM_LDFLAGS = $(ZLIB_LDFLAGS)

fun_trans_SOURCES = fun_trans.cc
fun_trans_LDADD = ../../lib/libvgetopt.la \
	          parse/libparse.la \
	          spec/libspec.la \
	          internal/libinternal.la \
	          transformer/libtrans.la

ty_trans_SOURCES = ty_trans.cc
ty_trans_LDADD = ../../lib/libvgetopt.la \
	         parse/libparse.la \
	         spec/libspec.la \
	         internal/libinternal.la \
	         transformer/libtrans.la


