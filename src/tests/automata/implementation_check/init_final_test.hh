// init_final_test.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>


# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>

# include <vaucanson/automata/concept/kinds.hh>

# include <vaucanson/automata/concept/tags.hh>

# include <vaucanson/automata/concrete/manylinks.hh>

# include <check/tests_stuff.hh>
# include <map>

# include <vaucanson/misc/ref.hh>
# include <vaucanson/tools/usual.hh>

template <class Auto>
unsigned init_final_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;
  automaton_t automaton;
  
  automaton.create();

  hstate_t s1 = automaton.add_state();
  automaton.set_initial(s1);

  TEST(t, "Is Initial State [set]", automaton.is_initial(s1));

  automaton.unset_initial(s1);

  TEST(t, "Is Initial State [unset]", !automaton.is_initial(s1));


  automaton.set_final(s1);

  TEST(t, "Is Final State [set]", automaton.is_final(s1));

  automaton.unset_final(s1);

  TEST(t, "Is Final State [unset]", !automaton.is_final(s1));

  return t.all_passed();
}

# endif
