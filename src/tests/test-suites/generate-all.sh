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


#    /*---------.
#    | Semiring |
#    `---------*/

../bin/generate-test-suite.sh \
   algebra_tropical_semiring_max \
   algebra_tropical_semiring_max.defs \
   ../algebra/semiring

../bin/generate-test-suite.sh \
   algebra_numerical_semiring_bool \
   algebra_numerical_semiring_bool.defs \
   ../algebra/semiring

for semiring_elt_value_t in int double float rational; do
../bin/generate-test-suite.sh \
   algebra_numerical_semiring_${semiring_elt_value_t} \
   algebra_numerical_semiring_${semiring_elt_value_t}.defs \
   ../algebra/semiring \
   ../algebra/numerical_semiring
done;


#    /*-------.
#    | Series |
#    `-------*/

for semiring_elt_value_t in bool double int; do
../bin/generate-test-suite.sh \
   algebra_series_krat_${semiring_elt_value_t}_string \
   algebra_series_krat_${semiring_elt_value_t}_string.defs \
   ../algebra/series/misc \
   ../algebra/series/krat/main

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

for automata_kind in boolean r z z_max_plus; do
../bin/generate-test-suite.sh \
   context_headers_${automata_kind} \
   context_headers_${automata_kind}.defs \
   ../context_headers/automata

../bin/generate-test-suite.sh \
   ${automata_kind}_automaton \
   ${automata_kind}_automaton.defs \
   ../automata
done;

../bin/generate-test-suite.sh \
   tropical_min_automaton \
   tropical_min_automaton.defs \
   ../automata
