# Makefile.am
#
# $Id: Makefile.am 462 2004-03-31 21:55:16Z yann $

if XML_CHECK
  AM_CXXFLAGS = $(CXXFLAGS_STRICT) -DINTERNAL_CHECKS -DSTRICT
  AM_CPPFLAGS = -I$(top_srcdir)/include		\
                -I$(top_builddir)/include		\
	        -I@XERCESC@/include
  AM_LDFLAGS = -lxerces-c -L@XERCESC@/lib

  noinst_PROGRAMS = static_boolean make_session display_session
endif

static_boolean_SOURCES = static_boolean.cc
make_session_SOURCES = make_session.cc
display_session_SOURCES = display_session.cc
