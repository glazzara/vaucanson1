set title "Memory usage of CBS Timer on many tasks (2GHz Intel Centrino, 1GB RAM)"
set xlabel "Number of tasks"
set ylabel "Memory usage (MB)"
set key top left
plot 'timer-many-tasks.data' using ($2):($3/1024/1024) t "Memory usage" smooth unique w linespoints pt 5 lc 1 lw 2
