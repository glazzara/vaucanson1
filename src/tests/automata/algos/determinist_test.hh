// determinist_test.hh
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

#ifndef DETERMINIST_TEST_HH
# define DETERMINIST_TEST_HH

# include <time.h>
# include <map>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/misc/dot_dump.hh>

template <class Auto>
unsigned determinist_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  typedef Auto automaton_t;

  tests::Tester t(tg.verbose());
  gen_auto_t gen(time(0x0));
  
  const unsigned nb_tests = 20;
  unsigned success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t dfa = gen.generate_dfa(50);;
      if (is_deterministic(dfa))
	++success;
    } 
  std::string rate;
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "is_determinist on randomly generated dfa " + rate, success == nb_tests);

  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {     
      automaton_t automata = gen.generate(40, 80);
      automaton_t dfa      = determinize(automata);
      if (is_deterministic(dfa))
	++success;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "determinize on randomly generated automaton " + rate, success == nb_tests);
  
  return t.all_passed();
}

#endif // DETERMINIST_TEST_HH
