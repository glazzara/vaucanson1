SUBDIRS = common determinization 				\
	  minimization_debruijn	minimization_2n derived_terms	\
	  quotient composition eps_removal

BENCHDIRS = determinization minimization_debruijn 		\
	    derived_terms minimization_2n quotient		\
	    composition eps_removal

benchs:
	for f in $(BENCHDIRS); do				\
	  (cd $$f && $(MAKE) $(AM_MAKEFLAGS) benchs || exit 1)	\
	done
