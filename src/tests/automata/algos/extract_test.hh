// extract_test.hh
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

#ifndef EXTRACT_TEST_HH
# define EXTRACT_TEST_HH

# include <time.h>
# include <map>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/reachable.hh>
# include <vaucanson/misc/dot_dump.hh>

template <class Auto>
unsigned extract_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  AUTOMATON_TYPES(Auto);
  typedef Auto automaton_t;
  
  tests::Tester t(tg.verbose());
  gen_auto_t gen(time(0x0));
  
  const unsigned nb_tests = 10;
  unsigned	 success  = 0;
  
  for (unsigned i = 0; i < nb_tests; i++)
    {
      unsigned nb_state = 5;
      unsigned nb_edge = 10;
      automaton_t a = gen.generate(nb_state, nb_edge);
      
      a = auto_extract(a, a.states());
      
      if ((a.states().size() == nb_state) &&
	  (a.edges().size() == nb_edge))
	++success;
    }
  std::string rate;
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "extract "+rate, success == nb_tests);
  return t.all_passed();
}
    
#endif // EXTRACT_TEST_HH
