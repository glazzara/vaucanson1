# eps_removal/Makefile.am			* -*- Makefile -*-

include $(top_srcdir)/src/benchs/common/bench.mk

EXTRA_PROGRAMS = eps_removal_boolean-bench eps_removal_z-bench
COMMON_SOURCES = eps_removal-bench.cc eps_removal_bench.hh

eps_removal_boolean_bench_SOURCES = $(COMMON_SOURCES)
eps_removal_boolean_bench_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=boolean_automaton

eps_removal_z_bench_SOURCES = $(COMMON_SOURCES)
eps_removal_z_bench_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT=z_automaton

benchs: $(EXTRA_PROGRAMS)
	@echo '=======================';				\
	echo '|Epsilon removal bench|';					\
	echo '=======================';					\
	for n_states in $$(seq 14 20); do				\
		echo "----------------------For $$n_states states";	\
		echo "--------------VCSN boolean:";			\
		./eps_removal_boolean-bench $$n_states;			\
		echo "--------------VCSN Z:";				\
		./eps_removal_z-bench $$n_states;			\
	done;

