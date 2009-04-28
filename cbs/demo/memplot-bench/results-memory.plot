set title "Memory consumption of CBS Memplot (2GHz Intel Centrino, 1GB RAM)"
set xlabel "Number of measures"
set ylabel "Memory usage (MB)"
set key top left
plot 'memplot-bench.data' using ($1):($2/1024/1024) t "Memory consumption" smooth unique w linespoints pt 5 lc 1 lw 2
