// reachable.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef REACHABLE_TEST_HH
# define REACHABLE_TEST_HH

# include <time.h>
# include <map>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/algorithms/reachable.hh>

template <class Auto>
unsigned reachable_test(tests::Tester& t)
{
  typedef Auto automaton_t;
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  

  gen_auto_t	 gen(time(0x0));
  const unsigned nb_tests			     = 10;
  unsigned	 success_trim			     = 0;
  unsigned	 success_final_reachable_idempotence = 0;
  unsigned	 success_start_reachable_idempotence = 0;

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t auto_connex;
      auto_connex.create();
      auto_connex = gen.generate(3, 1);
      
      unsigned nb_state = auto_connex.states().size();

      for (unsigned i =0; i < 10; i++)
	auto_connex.add_state();

      if (nb_state == 
	  auto_final_reachable(auto_start_reachable(auto_connex)).states().size())
	++success_trim;
      if (auto_final_reachable(auto_connex).states().size() == 
	  auto_final_reachable(auto_final_reachable(auto_connex)).states().size())
	++success_final_reachable_idempotence;
      if (auto_start_reachable(auto_connex).states().size() == 
	  auto_start_reachable(auto_start_reachable(auto_connex)).states().size())
	++success_start_reachable_idempotence;
    } 
  std::string rate_trim;
  std::string rate_f_idempotence;
  std::string rate_s_idempotence;
  SUCCESS_RATE(rate_trim, success_trim, nb_tests);
  SUCCESS_RATE(rate_f_idempotence, success_final_reachable_idempotence, nb_tests);
  SUCCESS_RATE(rate_s_idempotence, success_start_reachable_idempotence, nb_tests);
  TEST(t, "composition of final/start reachable is trim. "+rate_trim, 
       success_trim = nb_tests);
  TEST(t, "final reachable is idempotent. "+rate_f_idempotence, 
       success_final_reachable_idempotence == nb_tests);
  TEST(t, "start reachable is idempotent. "+rate_s_idempotence, 
       success_start_reachable_idempotence == nb_tests);
  return t.all_passed();
}

#endif // REACHABLE_TEST_HH
