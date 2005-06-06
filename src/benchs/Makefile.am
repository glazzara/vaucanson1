SUBDIRS = common determinization minimization_stroppa		\
	  minimization_debruijn	minimization_2n derived_terms	\
	  quotient composition minimization_nd

BENCHDIRS = determinization minimization_debruijn 		\
	    derived_terms minimization_2n quotient		\
	    composition minimization_nd minimization_stroppa

bench:
	for f in $(BENCHDIRS); do				\
	  (cd $$f && make bench)				\
	done
