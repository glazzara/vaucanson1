#!/bin/sh

#    /*----------.
#    | Alphabets |
#    `----------*/

for letter_kind in alpha char int pair_char_int; do
../bin/generate-test-suite.sh \
   algebra_alphabet_set_${letter_kind} \
   algebra_alphabet_set_${letter_kind}.defs \
   ../algebra/alphabets
done;


#    /*------------.
#    | Free monoid |
#    `------------*/

../bin/generate-test-suite.sh \
   algebra_free_monoid_string \
   algebra_free_monoid_string.defs \
   ../algebra/free_monoid


#    /*--------------------.
#    | Free monoid product |
#    `--------------------*/

../bin/generate-test-suite.sh \
   algebra_free_monoid_product_string \
   algebra_free_monoid_product_string.defs \
   ../algebra/free_monoid_product


#    /*---------.
#    | Semiring |
#    `---------*/

for semiring_type in numerical_semiring tropical_semiring_max tropical_semiring_min; do
    for semiring_elt_value_t in int double float rational bool; do
	TEST="../algebra/semiring";
	case $semiring_type:$semiring_elt_value_t in
	    numerical_semiring:bool)
		continue;;
	    numerical_semiring:*)
		TEST="$TEST ../algebra/numerical_semiring";;
	esac
	../bin/generate-test-suite.sh \
	algebra_${semiring_type}_${semiring_elt_value_t} \
	algebra_${semiring_type}_${semiring_elt_value_t}.defs \
	${TEST}
    done;
done;

#    /*-------.
#    | Series |
#    `-------*/

for semiring_elt_value_t in bool double int; do
    TEST="../algebra/series/misc ../algebra/series/krat/main"
    if [ $semiring_elt_value_t = "bool" ]; then
	TEST="$TEST ../algebra/series/krat/boolean"
    fi

    ../bin/generate-test-suite.sh \
	algebra_series_krat_${semiring_elt_value_t}_string \
	algebra_series_krat_${semiring_elt_value_t}_string.defs \
	${TEST}

    ../bin/generate-test-suite.sh \
	algebra_series_polynom_${semiring_elt_value_t}_string \
	algebra_series_polynom_${semiring_elt_value_t}_string.defs \
	../algebra/series/misc \
	../algebra/series/polynom
done;

for derivation_type in derivation cderivation partial_derivation; do
../bin/generate-test-suite.sh \
   algebra_series_krat_${derivation_type} \
   algebra_series_krat_${derivation_type}.defs \
   ../algebra/series/krat/derivations/${derivation_type}
done;


#    /*----------.
#    | Automaton |
#    `----------*/

for automata_kind in boolean r z z_max_plus z_min_plus; do
    ../bin/generate-test-suite.sh \
    context_headers_${automata_kind} \
    context_headers_${automata_kind}.defs \
    ../context_headers/automata

    TEST="../automata";
    if [ $automata_kind = "boolean" ]; then
	TEST="$TEST ../boolean_automata"
    else
	TEST="$TEST ../k_automata"
    fi
    ../bin/generate-test-suite.sh \
	${automata_kind}_automaton \
	${automata_kind}_automaton.defs \
	${TEST}
done;

#    /*-----------.
#    | Transducer |
#    `-----------*/

../bin/generate-test-suite.sh \
   context_headers_boolean_transducer \
   context_headers_boolean_transducer.defs \
   ../context_headers/transducers

../bin/generate-test-suite.sh \
   boolean_transducer \
   boolean_transducer.defs \
   ../transducers

../bin/generate-test-suite.sh \
   fmp_transducer \
   fmp_transducer.defs \
   ../fmp_transducers
