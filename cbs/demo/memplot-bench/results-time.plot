set title "Time consumption of CBS Memplot (2GHz Intel Centrino, 1GB RAM)"
set xlabel "Number of measures"
set ylabel "Time taken (ms)"
set key top left
plot 'memplot-bench.data' using ($1):($3) t "CPU time" smooth unique w linespoints pt 5 lc 1 lw 2, \
     'memplot-bench.data' using ($1):($4) t "user" smooth unique w linespoints pt 6 lc 1, \
     'memplot-bench.data' using ($1):($5) t "system" smooth unique w linespoints pt 3 lc 1
