// concat_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_CONCAT_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_CONCAT_TEST_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/concatenate.hh>

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
      automaton_t ret = concatenate(auto_lhs, auto_rhs);
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

#endif // VCSN_TESTS_AUTOMATA_ALGOS_CONCAT_TEST_HH
