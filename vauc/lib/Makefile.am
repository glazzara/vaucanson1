INCLUDES = -I$(top_srcdir)/include

noinst_LTLIBRARIES = libvgetopt.la libvreadline.la

libvgetopt_la_SOURCES = getopt.h getopt.c getopt1.c 

libvreadline_la_SOURCES = readlinebuf.cc
libvreadline_la_LIBADD = $(LIBREADLINE) $(LIBHISTORY)
