#!/bin/sh
../../bin/plot.pl -a ../../_build/demo/timer-bench/timer-start-stop_*.xml  > timer-start-stop.data
../../bin/plot.pl -a ../../_build/demo/timer-bench/timer-scoped_*.xml  > timer-scoped.data
../../bin/plot.pl -a ../../_build/demo/timer-bench/timer-many-tasks_*.xml > timer-many-tasks.data
../../bin/plot.pl -a ../../_build/demo/timer-bench/timer-recursion_*.xml > timer-recursion.data

gnuplot timer-many-tasks-memory.plot
gnuplot timer-many-tasks-time.plot
gnuplot timer-scoped-memory.plot
gnuplot timer-scoped-time.plot
gnuplot timer-recursion-memory.plot
gnuplot timer-recursion-time.plot
