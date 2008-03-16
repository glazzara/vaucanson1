// accessible_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_ACCESSIBLE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_ACCESSIBLE_TEST_HH

# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algorithms/accessible.hh>

template <typename Iterator1, typename Auto>
bool
test_has_states(Iterator1 i, Iterator1 end, const Auto& a)
{
  for (; i != end; ++i)
    if (!a.has_state(*i))
      return false;
  return true;
}

// FIXME: This is minimal tests.
template <class Auto>
bool accessible_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::algebra;

  AUTOMATON_TYPES(Auto);
  tests::Tester t(tg);
  GenRandomAutomata<Auto> gen;

  unsigned int success = 0;
  for (unsigned i = 0; i < t.test_num(); ++i)
  {
    automaton_t ac_auto = gen.generate(20, 40);
    automaton_t coac_auto = gen.generate(20, 40);

    coaccessible_here(coac_auto);
    accessible_here(ac_auto);
    std::set<hstate_t>	ac_states = accessible_states(ac_auto);
    std::set<hstate_t>	coac_states = coaccessible_states(coac_auto);

    if (test_has_states(ac_states.begin(), ac_states.end(), ac_auto) &&
        test_has_states(coac_states.begin(), coac_states.end(), coac_auto))
      success++;
    else
      TEST_MSG("TEST: Accessible algorithm do not give expected states.");
  }

  std::string test_rate;
  SUCCESS_RATE(test_rate, success, t.test_num());
  TEST(t, "Accessible/coaccessible minimal tests." + test_rate,
       success == t.test_num());
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_ACCESSIBLE_TEST_HH
