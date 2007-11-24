// minimization_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_MINIMIZATION_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_MINIMIZATION_TEST_HH

# include <sstream>
# include <map>
# include <algorithm>
# include <list>
# include <time.h>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/xml_dump.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/minimization_hopcroft.hh>
# include <vaucanson/algorithms/minimization_moore.hh>
# include <vaucanson/algorithms/trim.hh>
# include <tests/check/tester.hh>


template <class Auto>
unsigned minimization_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::algebra;

  typedef GenRandomAutomata<Auto>  gen_auto_t;
  typedef Auto			   automaton_t;

  tests::Tester t(tg);
  gen_auto_t	gen;

  unsigned success_hopcroft = 0;
  unsigned success_moore    = 0;
  unsigned success_co_moore = 0;

  for (unsigned i = 0; i < t.test_num(); i++)
  {
    automaton_t work = gen.generate_dfa(4, 5);
    automaton_t co_work = transpose(work);

    if (t.verbose(tests::Tester::high))
    {
      SAVE_AUTOMATON_XML("/tmp", "minimization_initial", work, i);
      SAVE_AUTOMATON_XML("/tmp", "co_minimization_initial", co_work, i);
    }

    automaton_t temp = trim(determinize(transpose(work)));

    automaton_t minimize = trim(determinize(transpose(temp)));
    automaton_t co_minimize = trim(transpose(minimize));

    if (t.verbose(tests::Tester::high))
    {
      SAVE_AUTOMATON_XML("/tmp", "minimization_broz", minimize, i);
      SAVE_AUTOMATON_XML("/tmp", "co_minimization_broz", co_minimize, i);
    }

    automaton_t hopcroft = trim(minimization_hopcroft(work));
    automaton_t moore = trim(minimization_moore(work));
    automaton_t co_moore = trim(co_minimization_moore(co_work));

    if (t.verbose(tests::Tester::high))
    {
      SAVE_AUTOMATON_XML("/tmp", "minimization_hopcroft", hopcroft, i);
      SAVE_AUTOMATON_XML("/tmp", "minimization_moore", moore, i);
      SAVE_AUTOMATON_XML("/tmp", "co_minimization_moore", co_moore, i);
    }

    if ((minimize.states().size() == hopcroft.states().size()) &&
	(minimize.transitions().size() ==  hopcroft.transitions().size()))
      ++success_hopcroft;
    else if (t.verbose(tests::Tester::high))
    {
      std::ostringstream s;
      s << "Hopcroft failed on " << i << std::ends;
      TEST_MSG(s.str());
    }

    if ((minimize.states().size() == moore.states().size()) &&
	(minimize.transitions().size() ==  moore.transitions().size()))
      ++success_moore;
    else if (t.verbose(tests::Tester::high))
    {
      std::ostringstream s;
      s << "Moore failed on " << i << std::ends;
      TEST_MSG(s.str());
    }

    if ((co_minimize.states().size() == co_moore.states().size()) &&
	(co_minimize.transitions().size() ==  co_moore.transitions().size()))
      ++success_co_moore;
    else if (t.verbose(tests::Tester::high))
    {
      std::ostringstream s;
      s << "Co-Moore failed on " << i << std::ends;
      TEST_MSG(s.str());
    }

  }

  std::string rate_hopcroft;
  SUCCESS_RATE(rate_hopcroft, success_hopcroft, t.test_num());
  std::string rate_moore;
  SUCCESS_RATE(rate_moore, success_moore, t.test_num());
  std::string co_rate_moore;
  SUCCESS_RATE(co_rate_moore, success_co_moore, t.test_num());
  TEST(t, "Hopcroft minimization "+rate_hopcroft,
       success_hopcroft == t.test_num());
  TEST(t, "Moore minimization	 "+rate_moore,
       success_moore	   == t.test_num());
  TEST(t, "Moore Co-minimization "+co_rate_moore,
       success_co_moore == t.test_num());

  return t.all_passed();
}
#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_MINIMIZATION_TEST_HH
