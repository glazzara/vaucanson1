#!/bin/sh


# generate DESTINATION-DIRECTORY DESCRIPTION-FILE TESTS-DIRS
# ----------------------------------------------------------
# Convenient wrapper around generate-test-suite.sh.
generate ()
{
    local dir=$1
    local defs=$1.defs
    shift
    local dirs=
    for i in "$@"
    do
      dirs="$dirs tests/$i"
    done
    ../bin/generate-test-suite.sh "$dir" "$defs" $dirs
}


## ----------- ##
## Alphabets.  ##
## ----------- ##

for letter_kind in alpha char int pair_char_int
do
  generate \
      algebra_alphabet_set_${letter_kind} \
      algebra/alphabets
done;


## ------------- ##
## Free monoid.  ##
## ------------- ##

generate \
   algebra_free_monoid_string \
   algebra/free_monoid


## --------------------- ##
## Free monoid product.  ##
## --------------------- ##

generate \
   algebra_free_monoid_product_string \
   algebra/free_monoid_product


## ---------- ##
## Semiring.  ##
## ---------- ##

for semiring_type in numerical_semiring tropical_semiring_max tropical_semiring_min; do
    for semiring_elt_value_t in int double float rational bool; do
	TEST="algebra/semiring";
	case $semiring_type:$semiring_elt_value_t in
	    numerical_semiring:bool)
		continue;;
	    numerical_semiring:*)
		TEST="$TEST algebra/numerical_semiring";;
	esac
	generate \
	algebra_${semiring_type}_${semiring_elt_value_t} \
	${TEST}
    done;
done;



## -------- ##
## Series.  ##
## -------- ##

for semiring_elt_value_t in bool double int; do
    TEST="algebra/series/misc algebra/series/krat/main"
    if [ $semiring_elt_value_t = "bool" ]; then
	TEST="$TEST algebra/series/krat/boolean"
    fi

    generate \
	algebra_series_krat_${semiring_elt_value_t}_string \
	${TEST}

    generate \
	algebra_series_polynom_${semiring_elt_value_t}_string \
	algebra/series/misc \
	algebra/series/polynom
done;

for derivation_type in derivation cderivation partial_derivation
do
  generate \
      algebra_series_krat_${derivation_type} \
      algebra/series/krat/derivations/${derivation_type}
done


## ----------- ##
## Automaton.  ##
## ----------- ##

for kind in boolean int_boolean r z z_max_plus z_min_plus char_char_boolean int_int_boolean
do
  generate \
      context_headers_${kind} \
      context_headers/automata

  # Create directories test list.
  TEST="automata/implementation_check"
  DIR="automata/algos/"
  for i in label_aware_graphs labeled_graphs letter_combination_labeled_graphs freemonoid_labeled_graphs graphs
  do
    TEST="$TEST $DIR$i"
  done

  if [ $kind = "boolean" ]; then
    TEST="$TEST automata/algos/boolean_automata"
  fi

  if [ $kind = "char_char_boolean" ] || [ $kind = "int_int_boolean" ]; then
    TEST="$TEST automata/algos/pair_automata"
  fi

  generate \
      ${kind}_automaton \
      ${TEST}
done


## ----------------------- ##
## Boolean RW_Transducer.  ##
## ----------------------- ##

for kind in boolean int_boolean
do
  generate \
      context_headers_${kind}_transducer \
      context_headers/transducers

  generate \
      ${kind}_transducer \
      automata/implementation_check automata/algos/graphs \
      automata/algos/series_multiplicity_transducers \
      automata/algos/boolean_rw_transducers
done

## -------------- ##
## Z Transducer.  ##
## -------------- ##

for kind in z int_z
do
  generate \
      context_headers_${kind}_transducer \
      context_headers/transducers

  generate \
      ${kind}_transducer \
      automata/implementation_check automata/algos/graphs \
      automata/algos/series_multiplicity_transducers
done


# FIXME: Directories labeled_graphs, label_aware_graphs and
#	 freemonoid_labeled_graphs are not tested.


# How come there is no explicit name here?
for kind in "" z_ int_ int_z_
do
  generate \
      context_headers_${kind}fmp_transducer \
      context_headers/fmp_transducers

  generate \
      ${kind}fmp_transducer \
      automata/algos/fmp_transducers
done

# FIXME: Directories labeled_graphs, implementation_check, graphs and
#	 label_aware_graphs are not tested.
