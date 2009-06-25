#!/bin/sh

../../bin/plot.pl							\
  -p "empty scopes" -p "tasks"						\
  -r "memory peak" -r "time" -r "time (system)" -r "time (user)"	\
  ../../_build/demo/timer-bench/timer-start-stop_*.xml			\
  > timer-start-stop.data

../../bin/plot.pl							\
  -p "empty scopes" -p "tasks"						\
  -r "memory peak" -r "time" -r "time (system)" -r "time (user)"	\
  ../../_build/demo/timer-bench/timer-scoped_*.xml			\
  > timer-scoped.data

../../bin/plot.pl							\
  -p "empty scopes" -p "tasks"						\
  -r "memory peak" -r "time" -r "time (system)" -r "time (user)"	\
  ../../_build/demo/timer-bench/timer-many-tasks_*.xml			\
  > timer-many-tasks.data

../../bin/plot.pl							\
  -p "depth"								\
  -r "memory peak" -r "time" -r "time (system)" -r "time (user)"	\
  ../../_build/demo/timer-bench/timer-recursion_*.xml			\
  > timer-recursion.data

gnuplot timer-many-tasks-memory.plot
gnuplot timer-many-tasks-time.plot
gnuplot timer-scoped-memory.plot
gnuplot timer-scoped-time.plot
gnuplot timer-recursion-memory.plot
gnuplot timer-recursion-time.plot
