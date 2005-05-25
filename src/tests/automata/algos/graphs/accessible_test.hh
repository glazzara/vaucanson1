// accessible_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//    * Michael Cadilhac <michael.cadilhac@lrde.epita.fr>
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_ACCESSIBLE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_ACCESSIBLE_TEST_HH

# include <algorithm>
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algorithms/accessible.hh>

// FIXME: This is minimal tests.
template <class Auto>
bool accessible_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  AUTOMATON_TYPES(Auto);
  tests::Tester t(tg.verbose());
  GenRandomAutomata<Auto> gen(time(0x0));

  unsigned int nb_test = 20;
  unsigned int success = 0;
  for (unsigned i = 0; i < nb_test; ++i)
  {
    automaton_t ac_auto = gen.generate(20, 40);
    automaton_t coac_auto = gen.generate(20, 40);

    coaccessible_here(coac_auto);
    accessible_here(ac_auto);
    std::set<hstate_t>	ac_states = accessible_states(ac_auto);
    std::set<hstate_t>	coac_states = coaccessible_states(coac_auto);
    if (equal(ac_states.begin(), ac_states.end(), ac_auto.states().begin()) &&
	equal(coac_states.begin(), coac_states.end(), coac_auto.states().begin()))
      success++;
    else
      TEST_MSG("TEST: Accessible algorithm do not give expected states.");
  }

  std::string test_rate;
  SUCCESS_RATE(test_rate, success, nb_test);
  TEST(t, "Accessible/coaccessible minimal tests." + test_rate,
       success == nb_test);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_ACCESSIBLE_TEST_HH
