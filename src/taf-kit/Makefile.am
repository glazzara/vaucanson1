AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include
AM_CXXFLAGS = $(CXXFLAGS_STRICT) $(CXXFLAGS_OPTIMIZE)
AM_LDFLAGS = $(TERMLIBS)

bin_PROGRAMS = vcsn-b

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
