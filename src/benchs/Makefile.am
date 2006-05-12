SUBDIRS = common determinization 				\
	  minimization_debruijn	minimization_2n derived_terms	\
	  quotient composition

BENCHDIRS = determinization minimization_debruijn 		\
	    derived_terms minimization_2n quotient		\
	    composition 

bench:
	for f in $(BENCHDIRS); do				\
	  (cd $$f && make bench)				\
	done
