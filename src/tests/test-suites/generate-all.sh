#!/bin/sh

for ns_impl in int bool double float rational; do
../bin/generate-test-suite.sh \
   algebra_numerical_semiring_${ns_impl} \
   algebra_numerical_semiring_${ns_impl}.defs \
   ../algebra/semiring
done;

for k_impl in bool double int; do
../bin/generate-test-suite.sh \
   algebra_series_krat_${k_impl}_string \
   algebra_series_krat_${k_impl}_string.defs \
   ../algebra/series/misc \
   ../algebra/series/krat/main
done;

../bin/generate-test-suite.sh \
   algebra_series_krat_derivation \
   algebra_series_krat_derivation.defs \
   ../algebra/series/krat/derivations/derivation

../bin/generate-test-suite.sh \
   algebra_series_krat_cderivation \
   algebra_series_krat_cderivation.defs \
   ../algebra/series/krat/derivations/cderivation

../bin/generate-test-suite.sh \
   algebra_series_krat_partial_derivation \
   algebra_series_krat_partial_derivation.defs \
   ../algebra/series/krat/derivations/partial_derivation

for a_impl in alpha char int pair_char_int; do
../bin/generate-test-suite.sh \
   algebra_alphabet_set_${a_impl} \
   algebra_alphabet_set_${a_impl}.defs \
   ../algebra/alphabets
done;

../bin/generate-test-suite.sh \
   algebra_free_monoid_string \
   algebra_free_monoid_string.defs \
   ../algebra/free_monoid

../bin/generate-test-suite.sh \
   algebra_tropical_semiring_max \
   algebra_tropical_semiring_max.defs \
   ../algebra/semiring

for p_impl in int double bool; do
../bin/generate-test-suite.sh \
   algebra_series_polynom_${p_impl}_string \
   algebra_series_polynom_${p_impl}_string.defs \
   ../algebra/series/misc \
   ../algebra/series/polynom
done;

for a_kind in boolean r z z_max_plus; do
../bin/generate-test-suite.sh \
   context_headers_${a_kind} \
   context_headers_${a_kind}.defs \
   ../context_headers/automata

../bin/generate-test-suite.sh \
   ${a_kind}_automaton_t \
   ${a_kind}_automaton_t.defs \
   ../automata
done;
