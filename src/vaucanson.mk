## -I directories are consulted in the same order as the command
## line, so put build dirs first.
AM_CPPFLAGS = \
-I$(top_builddir) \
-I$(top_builddir)/include \
-I$(top_srcdir)/include

AM_CXXFLAGS = $(CXXFLAGS_STRICT)
