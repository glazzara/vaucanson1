#!/bin/sh

../bin/generate-test-suite.sh \
   algebra_numerical_semiring \
   algebra_numerical_semiring.defs \
   ../algebra/semiring

../bin/generate-test-suite.sh \
   algebra_series_krat \
   algebra_series_krat \
   ../algebra/series/krat/main

../bin/generate-test-suite.sh \
   algebra_series_krat_derivation \
   algebra_series_krat_derivation.defs \
   ../algebra/series/krat/derivations

../bin/generate-test-suite.sh \
   algebra_series_misc \
   algebra_series_misc.defs \
   ../algebra/series/misc

../bin/generate-test-suite.sh \
   algebra_set_alphabet \
   algebra_set_alphabet.defs \
   ../algebra/alphabets

../bin/generate-test-suite.sh \
   algebra_string_free_monoid \
   algebra_string_free_monoid.defs \
   ../algebra/free_monoid

../bin/generate-test-suite.sh \
   algebra_tropical_max_semiring \
   algebra_tropical_max_semiring.defs \
   ../algebra/semiring

../bin/generate-test-suite.sh \
   usual_automaton_t \
   usual_automaton_t.defs \
   ../automata/implementation_check

   