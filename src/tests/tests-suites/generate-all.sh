#!/bin/sh

../bin/generate-test-suite.sh \
   algebra_numerical_semiring_int \
   algebra_numerical_semiring_int.defs \
   ../algebra/semiring

../bin/generate-test-suite.sh \
   algebra_numerical_semiring_bool \
   algebra_numerical_semiring_bool.defs \
   ../algebra/semiring

#
# Disabled for the moment, since we know this implementation is buggy.
#
#../bin/generate-test-suite.sh \
#   algebra_numerical_semiring_double \
#   algebra_numerical_semiring_double.defs \
#   ../algebra/semiring \
#   ../algebra/numerical_semiring

../bin/generate-test-suite.sh \
   algebra_numerical_semiring_float \
   algebra_numerical_semiring_float.defs \
   ../algebra/semiring \
   ../algebra/numerical_semiring

../bin/generate-test-suite.sh \
   algebra_numerical_semiring_rational \
   algebra_numerical_semiring_rational.defs \
   ../algebra/semiring \
   ../algebra/numerical_semiring

../bin/generate-test-suite.sh \
   algebra_series_krat_bool_string \
   algebra_series_krat_bool_string.defs \
   ../algebra/series/misc \
   ../algebra/series/krat/main

../bin/generate-test-suite.sh \
   algebra_series_krat_double_string \
   algebra_series_krat_double_string.defs \
   ../algebra/series/misc \
   ../algebra/series/krat/main

../bin/generate-test-suite.sh \
   algebra_series_krat_int_string \
   algebra_series_krat_int_string.defs \
   ../algebra/series/misc \
   ../algebra/series/krat/main

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

../bin/generate-test-suite.sh \
   algebra_alphabet_set_alpha \
   algebra_alphabet_set_alpha.defs \
   ../algebra/alphabets

../bin/generate-test-suite.sh \
   algebra_alphabet_set_char \
   algebra_alphabet_set_char.defs \
   ../algebra/alphabets

../bin/generate-test-suite.sh \
   algebra_alphabet_set_int \
   algebra_alphabet_set_int.defs \
   ../algebra/alphabets

../bin/generate-test-suite.sh \
   algebra_alphabet_set_pair_char_int \
   algebra_alphabet_set_pair_char_int.defs \
   ../algebra/alphabets

../bin/generate-test-suite.sh \
   algebra_free_monoid_string \
   algebra_free_monoid_string.defs \
   ../algebra/free_monoid

../bin/generate-test-suite.sh \
   algebra_tropical_semiring_max \
   algebra_tropical_semiring_max.defs \
   ../algebra/semiring

../bin/generate-test-suite.sh \
   usual_automaton_t \
   usual_automaton_t.defs \
   ../automata

../bin/generate-test-suite.sh \
   algebra_series_polynom_int_string \
   algebra_series_polynom_int_string.defs \
   ../algebra/series/misc \
   ../algebra/series/polynom

../bin/generate-test-suite.sh \
   algebra_series_polynom_double_string \
   algebra_series_polynom_double_string.defs \
   ../algebra/series/misc \
   ../algebra/series/polynom

../bin/generate-test-suite.sh \
   algebra_series_polynom_bool_string \
   algebra_series_polynom_bool_string.defs \
   ../algebra/series/misc \
   ../algebra/series/polynom
