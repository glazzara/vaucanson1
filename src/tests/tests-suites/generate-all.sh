#!/bin/sh

../bin/generate-test-suite.sh \
   algebra_numerical_semiring_int \
   algebra_numerical_semiring_int.defs \
   ../algebra/semiring

../bin/generate-test-suite.sh \
   algebra_numerical_semiring_bool \
   algebra_numerical_semiring_bool.defs \
   ../algebra/semiring

../bin/generate-test-suite.sh \
   algebra_numerical_semiring_double \
   algebra_numerical_semiring_double.defs \
   ../algebra/semiring \
   ../algebra/numerical_semiring

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
   algebra_series_krat \
   algebra_series_krat.defs \
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
   algebra_series_misc \
   algebra_series_misc.defs \
   ../algebra/series/misc

../bin/generate-test-suite.sh \
   algebra_set_alphabet \
   algebra_set_alphabet.defs \
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
   algebra_series_polynom_int \
   algebra_series_polynom_int.defs \
    ../algebra/series/polynom

../bin/generate-test-suite.sh \
   algebra_series_polynom_double \
   algebra_series_polynom_double.defs \
    ../algebra/series/polynom

../bin/generate-test-suite.sh \
   algebra_series_polynom_bool \
   algebra_series_polynom_bool.defs \
    ../algebra/series/polynom
