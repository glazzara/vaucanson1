// extension_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_SERIES_MULTIPLICITY_TRANSDUCERS_EXTENSION_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_SERIES_MULTIPLICITY_TRANSDUCERS_EXTENSION_TEST_HH

# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algorithms/extension.hh>

// FIXME: write a real test.
template <class Auto>
bool extension_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;

  AUTOMATON_TYPES(Auto);
  typedef typename automaton_t::value_t			automaton_value_t;
  typedef
  typename identity_transducer_helper<automata_set_t,
				      automaton_value_t>::ret transducer_t;

  tests::Tester t(tg.verbose());
  GenRandomAutomata<Auto> gen(time(0x0));

  automaton_t auto1 = gen.generate(30, 60);
  automaton_t auto2 = gen.generate(30, 60);
  // FIXME: Uncomment this lines.
  // transducer_t trans1 = extension(auto1);
  // transducer_t trans2 = extension(auto2, trans1);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_SERIES_MULTIPLICITY_TRANSDUCERS_EXTENSION_TEST_HH
