// realtime_test.hh: this file is part of the Vaucanson project.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_REALTIME_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_REALTIME_TEST_HH

# include <vaucanson/algorithms/realtime.hh>

# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/tools/gen_random.hh>


template <class Auto>
unsigned realtime_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);

  tests::Tester			t(tg.verbose());
  vcsn::GenRandomAutomata<Auto> gen(time(0x0));

  const unsigned nb_ok_tests     = 20;
  const unsigned nb_non_ok_tests = 20;
  unsigned success               = 0;

  for (unsigned i = 0; i < nb_ok_tests; i++)
    {
      automaton_t a = gen.generate(50, 60);;
      if (is_realtime(a))
	++success;
    }
  std::string rate;
  SUCCESS_RATE(rate, success, nb_ok_tests);
  TEST(t, "is_realtime on realtime "+rate, success == nb_ok_tests);

  success = 0;
  for (unsigned i = 0; i < nb_non_ok_tests; i++)
    {
      automaton_t a = gen.generate_with_epsilon(50, 60, 1, 15);;
      if (!is_realtime(a))
	++success;
    }
  SUCCESS_RATE(rate, success, nb_non_ok_tests);
  TEST(t, "is_realtime on non-realtime "+rate, success == nb_non_ok_tests);

  unsigned nb_tests = 20;
  unsigned nb_tests_done = 0;
  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t automata = gen.generate_with_epsilon(4, 8, 1, 2);
      try
	{
	  automaton_t non_epsilon = realtime(automata);
	  if (is_realtime(non_epsilon))
	    ++success;
	  ++nb_tests_done;
	}
      catch (std::logic_error&)
	{
	  ++nb_tests;
	}
    }
  SUCCESS_RATE(rate, success, nb_tests_done);
  TEST(t, "realtime on non-realtime "+rate, success == nb_tests_done);

  return t.all_passed();
}

#endif // VCSN_TESTS_AUTOMATA_ALGOS_REALTIME_TEST_HH
