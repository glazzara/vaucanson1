#!/bin/sh
../../bin/plot.pl							\
  -p "empty tasks"							\
  -r "memory peak" -r "time" -r "time (system)" -r "time (user)"	\
  ../../_build/demo/memplot-bench/memplot_*.xml				\
  > memplot-bench.data

gnuplot results-memory.plot
gnuplot results-time.plot
