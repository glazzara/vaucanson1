// accessible_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004, 2005 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_ACCESSIBLE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_ACCESSIBLE_TEST_HH

# include <algorithm>
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algorithms/accessible.hh>

// FIXME: This is minimal tests.
template <class Auto>
bool accessible_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  AUTOMATON_TYPES(Auto);
  tests::Tester t(tg.verbose());
  GenRandomAutomata<Auto> gen(time(0x0));

  unsigned int nb_test = 20;
  unsigned int success = 0;
  for (unsigned i = 0; i < nb_test; ++i)
  {
    automaton_t ac_auto = gen.generate(20, 40);
    automaton_t coac_auto = gen.generate(20, 40);

    coaccessible_here(coac_auto);
    accessible_here(ac_auto);
    std::set<hstate_t>	ac_states = accessible_states(ac_auto);
    std::set<hstate_t>	coac_states = coaccessible_states(coac_auto);
    if (equal(ac_states.begin(), ac_states.end(), ac_auto.states().begin()) &&
	equal(coac_states.begin(), coac_states.end(), coac_auto.states().begin()))
      success++;
    else
      TEST_MSG("TEST: Accessible algorithm do not give expected states.");
  }

  std::string test_rate;
  SUCCESS_RATE(test_rate, success, nb_test);
  TEST(t, "Accessible/coaccessible minimal tests." + test_rate,
       success == nb_test);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_ACCESSIBLE_TEST_HH
