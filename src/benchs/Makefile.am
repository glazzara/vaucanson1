SUBDIRS = common determinization minimization_stroppa		\
	  minimization_debruijn	minimization_2n derived_terms	\
	  quotient minimization_nd

BENCHDIRS = determinization minimzation_stroppa			\
	    minimization_debruijn derived_terms minimization_2n \
	    quotient minimization_nd

bench:
	for f in $(BENCHDIRS); do				\
	  (cd $$f && make bench)				\
	done
