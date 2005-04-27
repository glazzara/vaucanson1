// extension_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_EXTENSION_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_EXTENSION_TEST_HH

# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algorithms/extension.hh>

// FIXME: write a real test.
template <class Auto>
bool extension_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  AUTOMATON_TYPES(Auto);
  typedef typename automaton_t::value_t			automaton_value_t;
  typedef
  typename identity_transducer_helper<automata_set_t,
				      automaton_value_t>::ret transducer_t;
  
  tests::Tester t(tg.verbose());
  GenRandomAutomata<Auto> gen(time(0x0));

  automaton_t auto1 = gen.generate(30, 60);
  automaton_t auto2 = gen.generate(30, 60);
  // FIXME: Uncomment this lines.
  // transducer_t trans1 = extension(auto1);
  // transducer_t trans2 = extension(auto2, trans1);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_EXTENSION_TEST_HH
