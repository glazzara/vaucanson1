// generalized_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_GENERALIZED_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_GENERALIZED_TEST_HH

# include <check/tester.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/automata/implementation/generalized.hh>

using namespace vcsn;

template <class Auto>
bool generalized_test(tests::Tester&)
{
  AUTOMATON_TYPES(Auto);
  TEST_MSG("Basic test on a well-known automaton.");
  GenRandomAutomata<Auto> gen(time(0));
  Auto	a = gen.generate(10,20);
  typename generalized_traits<Auto>::automaton_t a_ =
    generalized(a);
  return true;
}

#endif // VCSN_TESTS_AUTOMATA_ALGOS_GENERALIZED_TEST_HH
