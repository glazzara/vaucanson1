#!/bin/sh
../../../bin/plot.pl -a timer-start-stop_*.xml  > timer-start-stop.data
../../../bin/plot.pl -a timer-scoped_*.xml  > timer-scoped.data
../../../bin/plot.pl -a timer-many-tasks_*.xml > timer-many-tasks.data
../../../bin/plot.pl -a timer-recursion_*.xml > timer-recursion.data
