set title "Memory usage of CBS Timer on empty scopes (2GHz Intel Centrino, 1GB RAM)"
set xlabel "Number of measures"
set ylabel "Memory usage (MB)"
set key top left
plot 'timer-start-stop.data' using ($1):($3/1024/1024) t "Memory usage" smooth unique w linespoints pt 5 lc 1 lw 2
