// reachable_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_REACHABLE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_REACHABLE_TEST_HH

# include <time.h>
# include <map>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/algorithms/accessible.hh>

template <class Auto>
unsigned reachable_test(tests::Tester& t)
{
  typedef Auto automaton_t;
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;


  GenRandomAutomata<automaton_t> gen(time(0x0));
  const unsigned nb_tests			     = 10;
  unsigned	 success_trim			     = 0;
  unsigned	 success_final_reachable_idempotence = 0;
  unsigned	 success_start_reachable_idempotence = 0;

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t auto_connex = gen.generate(10, 20);

      unsigned nb_state = auto_connex.states().size();

      for (unsigned i =0; i < 10; i++)
	auto_connex.add_state();

      if (nb_state ==
	  accessible
	  (coaccessible(auto_connex)).states().size())
	++success_trim;
      if (coaccessible(auto_connex).states().size() ==
	  coaccessible(coaccessible(auto_connex))
	  .states().size())
	++success_final_reachable_idempotence;
      if (accessible(auto_connex).states().size() ==
	  accessible(accessible(auto_connex))
	  .states().size())
	++success_start_reachable_idempotence;
    }
  std::string rate_trim;
  std::string rate_f_idempotence;
  std::string rate_s_idempotence;
  SUCCESS_RATE(rate_trim, success_trim, nb_tests);
  SUCCESS_RATE(rate_f_idempotence, success_final_reachable_idempotence,
	       nb_tests);
  SUCCESS_RATE(rate_s_idempotence, success_start_reachable_idempotence,
	       nb_tests);
  TEST(t, "composition of final/start reachable is trim. "+rate_trim,
       success_trim == nb_tests);
  TEST(t, "final reachable is idempotent. "+rate_f_idempotence,
       success_final_reachable_idempotence == nb_tests);
  TEST(t, "start reachable is idempotent. "+rate_s_idempotence,
       success_start_reachable_idempotence == nb_tests);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_REACHABLE_TEST_HH
