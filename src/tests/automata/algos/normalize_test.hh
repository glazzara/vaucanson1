// normalize_test.hh
// 
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef NORMALIZE_TEST_HH
# define NORMALIZE_TEST_HH

# include <time.h>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/algorithms/normalized.hh>

template <class Auto>
unsigned normalize_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  typedef Auto automaton_t;
 
  tests::Tester     t(tg.verbose());
  gen_auto_t        gen(time(0x0));
  const unsigned    nb_tests = 10;
  unsigned	    success = 0;
  std::string	    rate;

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t normalized = gen.generate_normalized(30);;
      if (is_normalized(normalized))
	success++;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "is_normalized on random normalized automaton "+rate, 
       nb_tests == success);

  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t normalized = gen.generate(30, 60);
      normalize(normalized);
      if (is_normalized(normalized))
	success++;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "normalized on randomly generated automaton "+rate, nb_tests == success);

  return t.all_passed();
}

#endif // NORMALIZE_TEST_HH
