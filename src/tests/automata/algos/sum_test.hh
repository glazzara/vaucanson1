// sum_test.hh
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

#ifndef SUM_TEST_HH
# define SUM_TEST_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/sum.hh>
# include <time.h>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned sum_test(tests::Tester& tg)
{  
  typedef Auto automaton_t;

  tests::Tester t(tg.verbose());
  gen_auto_t    gen(time(0x0));
  unsigned      nb_tests       = 10;
  unsigned      success_states = 0;
  unsigned      success_edges  = 0;

  for (unsigned i = 0 ; i < nb_tests; i++) 
    {
      automaton_t a = gen.generate(20, 40);
      automaton_t b = gen.generate(10, 20);
      automaton_t c = sum(a, b);

      if (a.states().size() + b.states().size() == c.states().size())
	++success_states;
      if (a.edges().size() + b.edges().size() == c.edges().size())
	++success_edges;
    }
  std::string rate_states, rate_edges;
  SUCCESS_RATE(rate_states, success_states, nb_tests);
  SUCCESS_RATE(rate_edges, success_edges, nb_tests);
  TEST(t, "Union basic tests (edges: "+rate_edges+", states: "+rate_states+")", 
       ((nb_tests == success_edges) && (nb_tests == success_states)));
  return t.all_passed();
}

#endif // SUM_TEST_HH
