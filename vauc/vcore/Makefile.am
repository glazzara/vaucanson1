
INCLUDES = $(LTDLINCL) -I$(VCSN_INCLUDEDIR) -I$(CPPSH_SRCDIR)/include -I$(top_srcdir)/include

lib_LTLIBRARIES = libvcore.la

libvcore_la_SOURCES = \
	interrupt_handler.cc \
	lazy_print_visitor.cc \
	module_loader.cc \
	unwind_init.cc unwind_init.hh \
	env.cc \
	object_catalog.cc \
	closure.cc \
	partial_call.cc \
	functionimpl.cc \
	eval.cc \
	find_path.cc
libvcore_la_LIBADD = ../cppsh/kern/libcppshk.la ../cppsh/kern/libcppshio.la