// closure_test.hh
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

#ifndef CLOSURE_TEST_HH
# define CLOSURE_TEST_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/closure.hh>

template <class Auto>
bool closure_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  
  typedef Auto automaton_t;
  AUTOMATON_TYPES(Auto);
  
  tests::Tester t(tg.verbose());
  gen_auto_t gen(time(0x0));
  automaton_t auto_epsilon = gen.generate_with_epsilon(30, 50, 10, 20);
  automaton_t cauto = closure(auto_epsilon);

  TEST(t, "Increase of edges number.",  
       cauto.edges().size() >= auto_epsilon.edges().size());
  TEST(t, "Idempotence.", 
       closure(cauto).edges().size() == cauto.edges().size());

  return t.all_passed();
}

#endif // CLOSURE_TEST_HH
