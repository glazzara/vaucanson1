// complete_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/usual_macros.hh>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned complete_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());
  typedef Auto				automaton_t;
  typedef GenRandomAutomata<Auto>	gen_auto_t;
  AUTOMATON_TYPES(automaton_t);
  AUTOMATON_FREEMONOID_TYPES(automaton_t);

  gen_auto_t				gen(time(0x0));

  const unsigned			nb_test = 50;
  unsigned				nb_success = 0;

  typedef std::set<hstate_t>		delta_ret_t;
  delta_ret_t				delta_ret;
  bool					result_test;

  for (unsigned i = 0 ; i < nb_test; i++)
  {
    automaton_t a = gen.generate_dfa(30);
    automaton_t b = a;
    complete_here(a);
    alphabet_t alphabet = a.structure().series().monoid().alphabet();
    result_test = true;

    if ((a.transitions().size() == a.states().size() *
	 a.structure().series().monoid().alphabet().size())
	&& is_deterministic(a))
    {
      for (alphabet_iterator l = alphabet.begin();
	   l != alphabet.end();
	   ++l)
      {
	for_each_state(s, a)
	{
	  delta_ret.clear();
	  a.letter_deltac(delta_ret, *s, *l,
			  delta_kind::states());
	  if (delta_ret.size() == 0)
	    result_test = false;
	}
      }
      if (result_test)
	++nb_success;
    }
    else
      result_test = false;

    if (not result_test)
    {
      std::ostringstream s;
      s << "Test failed on " << i << std::ends;
      TEST_MSG(s.str());
    }

    if (tg.verbose() != tests::high or not result_test)
    {
      TEST_MSG("Automaton saved in /tmp.");
      SAVE_AUTOMATON_DOT("/tmp", "complete_initial", b, i);
    }
  }
  std::string rate;
  SUCCESS_RATE(rate, nb_success, nb_test);
  TEST(t, "complete on DFA." + rate, nb_success == nb_test);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_COMPLETE_TEST_HH
