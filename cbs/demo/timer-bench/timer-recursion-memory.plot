set title "Memory usage of CBS Timer on recursive tasks (2GHz Intel Centrino, 1GB RAM)"
set xlabel "Recursion depth"
set ylabel "Memory usage (MB)"
set key top left
plot 'timer-recursion.data' using ($1):($2/1024/1024) t "Memory usage" smooth unique w linespoints pt 5 lc 1 lw 2
