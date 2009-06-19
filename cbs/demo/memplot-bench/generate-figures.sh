#!/bin/sh
../../bin/plot.pl -a ../../_build/demo/memplot-bench/memplot_*.xml  > memplot-bench.data
gnuplot results-memory.plot
gnuplot results-time.plot
