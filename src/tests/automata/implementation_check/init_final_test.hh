// init_final_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_INIT_FINAL_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_INIT_FINAL_TEST_HH

# include <map>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/tools/gen_random.hh>
# include <check/tester.hh>
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

#endif // VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_INIT_FINAL_TEST_HH
