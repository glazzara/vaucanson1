// concat_test.hh
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

#ifndef VCSN_TEST_CONCAT_TEST_HH
# define VCSN_TEST_CONCAT_TEST_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/concat.hh>

template <class Auto>
bool concat_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  AUTOMATON_TYPES(Auto);
  
  unsigned int nb_test = 20;
  unsigned int size    = 0;
  tests::Tester t(tg.verbose());

  gen_auto_t gen(time(0x0));
  for (unsigned i = 0; i < nb_test; ++i)
    {
      automaton_t auto_lhs = gen.generate_with_epsilon(30, 50, 10, 20);
      automaton_t auto_rhs = gen.generate_with_epsilon(30, 50, 10, 20);
      automaton_t ret = auto_concat(auto_lhs, auto_rhs);
      if (ret.states().size() == 
	  auto_lhs.states().size() + auto_rhs.states().size())
	++size;
    }

  std::string size_rate;
  SUCCESS_RATE(size_rate, size, nb_test);
  TEST(t, "Number of states is the addition of the two."+size_rate,
       size == nb_test);
  // FIXME: add tests based on samples from the languages.
  return t.all_passed();
}

#endif // VCSN_TEST_CONCAT_TEST_HH
