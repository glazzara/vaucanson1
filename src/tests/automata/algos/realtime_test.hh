// realtime_test.hh
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

#ifndef REALTIME_TEST_HH
# define REALTIME_TEST_HH

# include <map>
# include <time.h>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/misc/ref.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/misc/dot_dump.hh>


template <class Auto>
unsigned realtime_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;
  tests::Tester t(tg.verbose());

  gen_auto_t gen(time(0x0));
  
  const unsigned nb_ok_tests     = 20;
  const unsigned nb_non_ok_tests = 20;
  unsigned success               = 0;

  for (unsigned i = 0; i < nb_ok_tests; i++)
    {
      automaton_t a = gen.generate(50, 60);;      
      if (is_realtime(a))
	++success;
    } 
  std::string rate;
  SUCCESS_RATE(rate, success, nb_ok_tests);
  TEST(t, "is_realtime on realtime "+rate, success == nb_ok_tests);

  success = 0;
  for (unsigned i = 0; i < nb_non_ok_tests; i++)
    {
      automaton_t a = gen.generate_with_epsilon(50, 60, 1, 15);;      
      if (!is_realtime(a))
	++success;
    } 
  SUCCESS_RATE(rate, success, nb_non_ok_tests);
  TEST(t, "is_realtime on non-realtime "+rate, success == nb_non_ok_tests);

  unsigned nb_tests = 20;
  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {     
      automaton_t automata = gen.generate_with_epsilon(40, 80, 1, 40);
      automaton_t non_epsilon = realtime(automata);
      if (is_realtime(non_epsilon))
	++success;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "realtime on non-realtime "+rate, success == nb_tests);

  return t.all_passed();
}

#endif // REALTIME_TEST_HH
