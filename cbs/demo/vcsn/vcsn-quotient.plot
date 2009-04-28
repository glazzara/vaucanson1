set title "Code optimization influence on quotient() (2GHz Intel Centrino, 1GB RAM)"
set xlabel "Product automaton complexity"
set ylabel "Time (ms)"
set key top left
plot 'vcsn-quotient-fix.data' using 1:8 title "CPU time (after)" smooth unique  w linespoints pt 5 lc 2 lw 2, \
     'vcsn-quotient-fix.data' using 1:10 title "user (after)" smooth unique w linespoints pt 6 lc 2,     \
     'vcsn-quotient-fix.data' using 1:9 title "system (after)" smooth unique w linespoints pt 3 lc 2,   \
     'vcsn-quotient-orig.data' using 1:7 title "CPU time (before)" smooth unique w linespoints pt 5 lc 1 lw 2,      \
     'vcsn-quotient-orig.data' using 1:9 title "user (before)" smooth unique w linespoints pt 6 lc 1,          \
     'vcsn-quotient-orig.data' using 1:8 title "system (before)" smooth unique w linespoints pt 3 lc 1
