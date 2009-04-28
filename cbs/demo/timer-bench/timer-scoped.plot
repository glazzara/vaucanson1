set title "Time consumption of CBS Timer on empty scopes (2GHz Intel Centrino, 1GB RAM)"
set xlabel "Number of measures"
set ylabel "Time taken (ms)"
set key top left
plot 'timer-scoped.data' using ($1):($4) t "CPU time (scoped)" smooth unique w linespoints pt 5 lc 1 lw 2, \
     'timer-scoped.data' using ($1):($5) t "user (scoped)" smooth unique w linespoints pt 6 lc 1, \
     'timer-scoped.data' using ($1):($6) t "system (scoped)" smooth unique w linespoints pt 3 lc 1, \
     'timer-start-stop.data' using ($1):($4) t "CPU time (start & stop)" smooth unique w linespoints pt 5 lc 3 lw 2, \
     'timer-start-stop.data' using ($1):($5) t "user (start & stop)" smooth unique w linespoints pt 6 lc 3, \
     'timer-start-stop.data' using ($1):($6) t "system (start & stop)" smooth unique w linespoints pt 3 lc 3
