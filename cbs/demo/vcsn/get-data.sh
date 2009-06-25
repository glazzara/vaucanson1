#!/bin/sh

VCSNDIR=~/work/vaucanson/
BMIG=bench-bmig/
LISTG=bench-listg/

../../bin/plot.pl -a ${VCSNDIR}${LISTG}/quotient/bench_quotient_z*.xml > vcsn-quotient-z-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/quotient/bench_quotient_z*.xml > vcsn-quotient-z-bmig.data
../../bin/plot.pl -a ${VCSNDIR}${LISTG}/quotient/bench_quotient_bool*.xml > vcsn-quotient-bool-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/quotient/bench_quotient_bool*.xml > vcsn-quotient-bool-bmig.data

../../bin/plot.pl -a ${VCSNDIR}${LISTG}/determinization/*.xml > vcsn-determinize-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/determinization/*.xml > vcsn-determinize-bmig.data

../../bin/plot.pl -a ${VCSNDIR}${LISTG}/composition/bench_rw*.xml > vcsn-composition-rw-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/composition/bench_rw*.xml > vcsn-composition-rw-bmig.data
../../bin/plot.pl -a ${VCSNDIR}${LISTG}/composition/bench_normalized*.xml > vcsn-composition-normalized-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/composition/bench_normalized*.xml > vcsn-composition-normalized-bmig.data

../../bin/plot.pl -a ${VCSNDIR}${LISTG}/iterators/bench_accessible*.xml > vcsn-iterators-accessible-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/iterators/bench_accessible*.xml > vcsn-iterators-accessible-bmig.data
../../bin/plot.pl -a ${VCSNDIR}${LISTG}/iterators/bench_iterator_building_process*.xml > vcsn-iterators-building-process-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/iterators/bench_iterator_building_process*.xml > vcsn-iterators-building-process-bmig.data
../../bin/plot.pl -a ${VCSNDIR}${LISTG}/iterators/bench_iterator_deltai*.xml > vcsn-iterators-deltai-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/iterators/bench_iterator_deltai*.xml > vcsn-iterators-deltai-bmig.data

../../bin/plot.pl -a ${VCSNDIR}${LISTG}/minimization_debruijn/bench_minimization_debruijn_brzozowski*.xml > vcsn-minimization-debruijn-brzozowski-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/minimization_debruijn/bench_minimization_debruijn_brzozowski*.xml > vcsn-minimization-debruijn-brzozowski-bmig.data
../../bin/plot.pl -a ${VCSNDIR}${LISTG}/minimization_debruijn/bench_minimization_debruijn_hopcroft*.xml > vcsn-minimization-debruijn-hopcroft-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/minimization_debruijn/bench_minimization_debruijn_hopcroft*.xml > vcsn-minimization-debruijn-hopcroft-bmig.data
../../bin/plot.pl -a ${VCSNDIR}${LISTG}/minimization_debruijn/bench_minimization_debruijn_moore*.xml > vcsn-minimization-debruijn-moore-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/minimization_debruijn/bench_minimization_debruijn_moore*.xml > vcsn-minimization-debruijn-moore-bmig.data

../../bin/plot.pl -a ${VCSNDIR}${LISTG}/minimization_2n/bench_minimization_2n_brzozowski*.xml > vcsn-minimization-2n-brzozowski-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/minimization_2n/bench_minimization_2n_brzozowski*.xml > vcsn-minimization-2n-brzozowski-bmig.data
../../bin/plot.pl -a ${VCSNDIR}${LISTG}/minimization_2n/bench_minimization_2n_hopcroft*.xml > vcsn-minimization-2n-hopcroft-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/minimization_2n/bench_minimization_2n_hopcroft*.xml > vcsn-minimization-2n-hopcroft-bmig.data
../../bin/plot.pl -a ${VCSNDIR}${LISTG}/minimization_2n/bench_minimization_2n_moore*.xml > vcsn-minimization-2n-moore-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/minimization_2n/bench_minimization_2n_moore*.xml > vcsn-minimization-2n-moore-bmig.data

../../bin/plot.pl -a ${VCSNDIR}${LISTG}/eps_removal/*.xml > vcsn-eps-removal-listg.data
../../bin/plot.pl -a ${VCSNDIR}${BMIG}/eps_removal/*.xml > vcsn-eps-removal-bmig.data
