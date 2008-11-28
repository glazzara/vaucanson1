// complete_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_COMPLETE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_COMPLETE_TEST_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/is_deterministic.hh>
# include <vaucanson/tools/xml_dump.hh>
# include <vaucanson/misc/usual_macros.hh>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned complete_test(tests::Tester& tg)
{
  tests::Tester t(tg);
  typedef Auto				automaton_t;
  typedef GenRandomAutomata<Auto>	gen_auto_t;
  AUTOMATON_TYPES(automaton_t);
  AUTOMATON_FREEMONOID_TYPES(automaton_t);

  gen_auto_t				gen;

  unsigned				nb_success = 0;

  bool					result_test;

  for (unsigned i = 0 ; i < t.test_num(); i++)
  {
    if (tg.verbose(tests::Tester::high))
      std::cerr << "Test " << i << " / " << t.test_num() << std::endl;

    automaton_t a = gen.generate_dfa(30);

    // Remove one state.  This is a regression test for a bug in
    // complete().  With the listg implementation, the new state
    // created by complete() would be created in the hole left by
    // del_state(), and the iteration over the states of the automate
    // would mistakenly iterate over this one.
    a.del_state(5);

    automaton_t b = complete(a);
    alphabet_t alphabet = a.structure().series().monoid().alphabet();
    result_test = true;

    // Both alphabets are the same.
    if (alphabet != b.structure().series().monoid().alphabet())
      {
	TEST_MSG("alphabet of the completed automaton differs.");
	result_test = false;
      }

    // The result is complete.
    if (!is_complete(b))
      {
	TEST_MSG("!is_complete(complete(a)).");
	result_test = false;
      }

    // The result remains deterministic.
    if (!is_deterministic(b))
      {
	TEST_MSG("!is_deterministic(complete(a)) --- a is a dfa.");
	result_test = false;
      }

    // Deterministic and complete.
    if (b.transitions().size() !=
	b.states().size() * b.structure().series().monoid().alphabet().size())
      {
	TEST_MSG("#transitions != #states * #letters.");
	result_test = false;
      }

    if (result_test)
      ++nb_success;
    else
      TEST_MSG("Test failed on " << i);

    if (tg.verbose(tests::Tester::high) or not result_test)
      SAVE_AUTOMATON_XML("/tmp", "complete_initial", b, i);
  }

  std::string rate;
  SUCCESS_RATE(rate, nb_success, t.test_num());
  TEST(t, "complete on DFA." + rate, nb_success == t.test_num());
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_COMPLETE_TEST_HH
