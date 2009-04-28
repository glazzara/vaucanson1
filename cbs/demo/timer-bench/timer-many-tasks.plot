set title "Time consumption of CBS Timer on many tasks (2GHz Intel Centrino, 1GB RAM)"
set xlabel "Number of tasks"
set ylabel "Time taken (ms / 1 million measures)"
set key top left
plot 'timer-many-tasks.data' using ($2):($4) t "CPU time" smooth unique w linespoints pt 5 lc 1 lw 2, \
     'timer-many-tasks.data' using ($2):($5) t "user" smooth unique w linespoints pt 6 lc 1, \
     'timer-many-tasks.data' using ($2):($6) t "system" smooth unique w linespoints pt 3 lc 1