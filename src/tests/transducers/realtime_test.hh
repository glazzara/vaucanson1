// realtime_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_TRANSDUCERS_REALTIME_TEST_HH
# define VCSN_TESTS_TRANSDUCERS_REALTIME_TEST_HH

# include <vaucanson/algorithms/is_realtime.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/tools/gen_random.hh>


template <class Transducer>
unsigned realtime_test(tests::Tester& tg)
{
  using namespace vcsn;
  AUTOMATON_TYPES(Transducer);

  tests::Tester			t(tg.verbose());
  GenRandomAutomata<Transducer> gen(time(0x0));

  const unsigned nb_tests     = 20;
  bool error = false;

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t t = gen.generate(50, 60);;
      if (!is_realtime(t))
	error = true;
    }
  TEST(t, "is_realtime on realtime ", not error);
  error = false;

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t t = gen.generate_with_epsilon(50, 60, 1, 15);;
      if (is_realtime(t))
	error = true;
    }
  TEST(t, "is_realtime on non-realtime ", not error);

  error = false;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t automata = gen.generate_with_epsilon(4, 8, 1, 2);
      try
      	{
	  automaton_t non_epsilon = realtime(automata);
 	  if (!is_realtime(non_epsilon))
 	    error = true;
	}
      catch (std::logic_error&)
	{
	}
    }
  TEST(t, "realtime on non-realtime ", not error);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_TRANSDUCERS_REALTIME_TEST_HH
