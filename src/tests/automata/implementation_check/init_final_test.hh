// init_final_test.hh
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

#ifndef INIT_FINAL_TEST_HH
# define INIT_FINAL_TEST_HH

# include <map>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/tools/gen_random.hh>
# include <check/tester.hh>
# include <vaucanson/misc/ref.hh>
# include <vaucanson/tools/usual_macros.hh>

template <class Auto>
unsigned init_final_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;
  tools::GenRandomAutomata<Auto> gen(time(0x0));

  automaton_t automaton = gen.empty();
  
  hstate_t s1 = automaton.add_state();
  automaton.set_initial(s1);

  TEST(t, "After set_initial(s), s is an initial state. ", automaton.is_initial(s1));

  automaton.unset_initial(s1);

  TEST(t, "After unset_initial(s), s is not an initial state.", !automaton.is_initial(s1));

  automaton.set_final(s1);

  TEST(t, "After set_final(s), s is a final state.", automaton.is_final(s1));

  automaton.unset_final(s1);

  TEST(t, "After unset_final(s), s is not a final state.", !automaton.is_final(s1));

  return t.all_passed();
}

# endif // INIT_FINAL_TEST_HH
