SUBDIRS = lib libltdl mpp++ 

EXTRA_DIST = boostrap.sh cleanup.sh \
	     ltwrap-sh.in cxxwrap-sh.in \
	     config/readline.m4 config/libz.m4 config/libtool-fix.m4

ACLOCAL_AMFLAGS = -I config
CONFIGURE_DEPENDENCIES = $(srcdir)/config/readline.m4 $(srcdir)/config/libz.m4 $(srcdir)/config/libtool-fix.m4
