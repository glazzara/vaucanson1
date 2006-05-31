include $(top_srcdir)/src/vaucanson.mk
# VCSN_USE_XML doesn't need to be checked as VCSN_TAF_KIT
# is not enabled if the former isn't.
AM_CPPFLAGS += $(CXXFLAGS_OPTIMIZE)
AM_LDFLAGS = $(TERMLIBS)

Progs = vcsn-b

if VCSN_TAF_KIT
  bin_PROGRAMS = $(Progs)
else
  EXTRA_PROGRAMS = $(Progs)
endif

COMMON_SOURCES = commands.hh			\
		 commands_macros.hh		\
		 common_commands.hh		\
		 common.hh			\
		 edit_automaton.hh		\
		 edit_automaton.hxx		\
		 getters.hh			\
		 getters.hxx			\
		 main.cc			\
		 predefined_alphabets.hh


vcsn_b_CPPFLAGS = $(AM_CPPFLAGS)					\
		  -DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"   \
		  -DCONTEXT_NAMESPACE="vcsn::boolean_automaton"


vcsn_b_SOURCES = $(COMMON_SOURCES)		\
		 b_commands.cc

## ------ ##
## argp.  ##
## ------ ##

# Be sure to fetch the argp we ship.
AM_CPPFLAGS += -I$(top_srcdir)/argp
vcsn_b_LDADD = $(top_builddir)/argp/libargp.la
