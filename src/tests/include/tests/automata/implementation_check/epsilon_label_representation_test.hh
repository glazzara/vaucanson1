// epsilon_label_representation_test.hh: this file is part of the Vaucanson
// project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_EPSILON_LABEL_REPRESENTATION_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_EPSILON_LABEL_REPRESENTATION_TEST_HH

# include <map>
# include <sstream>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/handlers.hh>

template <class Auto>
unsigned epsilon_label_representation_test(tests::Tester& tg)
{
  tests::Tester t(tg);

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::algebra;

  typedef Auto automaton_t;
  GenRandomAutomata<Auto> gen;

  automaton_t automaton = gen.empty();

  hstate_t s1 = automaton.add_state();
  hstate_t s2 = automaton.add_state();

  htransition_t h1 = automaton.add_spontaneous(s1, s2);

  semiring_t semiring = automaton.structure().series().semiring();
  std::stringstream ref;
  std::stringstream sstr;

  ref << "({" << semiring.identity(SELECT(semiring_elt_value_t)) << "} ";
  ref << algebra::letter_traits<typename automaton_t::letter_t>::default_epsilon() << ")";

  sstr << automaton.series_value_of(h1);

  EQTEST(t, "Spontaneous transition representation as a polynom = " + ref.str() + ".",
	 sstr.str(), ref.str());

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_EPSILON_LABEL_REPRESENTATION_TEST_HH
