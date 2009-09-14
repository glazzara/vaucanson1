include $(srcdir)/../common/bench.mk

EXTRA_DIST = alpha.syms				\
	     bench.mk				\
	     bench_macros.hh			\
	     README_AUTOMATA

noinst_PROGRAMS =
noinst_PROGRAMS += bench_constructs
bench_constructs_SOURCES = bench_constructs.cc bench_constructs.hh
bench_constructs_LDADD = $(benchlib)

bench: all
	@echo "Generating examples of benchmark automata..."
	./bench_constructs

bench-clean:
	rm -rf aut_*.xml
	rm -rf aut_*.dot
	rm -rf aut_*.png
