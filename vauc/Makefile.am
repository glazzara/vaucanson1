SUBDIRS = include lib libltdl ltdlpp lemon cppsh vcore vparse mpp++

EXTRA_DIST = bootstrap.sh cleanup.sh \
	     config/ltwrap-sh.in config/cxxwrap-sh.in \
	     config/readline.m4 config/libz.m4 config/libtool-fix.m4

ACLOCAL_AMFLAGS = -I config
CONFIGURE_DEPENDENCIES = $(srcdir)/config/readline.m4 $(srcdir)/config/libz.m4 $(srcdir)/config/libtool-fix.m4
