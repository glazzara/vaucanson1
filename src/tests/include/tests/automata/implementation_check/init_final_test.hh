// init_final_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_INIT_FINAL_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_INIT_FINAL_TEST_HH

# include <map>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/tools/gen_random.hh>
# include <tests/check/tester.hh>
# include <vaucanson/misc/usual_macros.hh>

template <class Auto>
unsigned init_final_test(tests::Tester& tg)
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
  automaton.set_initial(s1);

  TEST(t, "After set_initial(s), s is an initial state. ", automaton.is_initial(s1));

  automaton.unset_initial(s1);

  TEST(t, "After unset_initial(s), s is not an initial state.", !automaton.is_initial(s1));

  automaton.set_final(s1);

  TEST(t, "After set_final(s), s is a final state.", automaton.is_final(s1));

  automaton.unset_final(s1);

  TEST(t, "After unset_final(s), s is not a final state.", !automaton.is_final(s1));

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_INIT_FINAL_TEST_HH
