// determinist_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_DETERMINIST_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_DETERMINIST_TEST_HH

# include <time.h>
# include <map>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/tools/dot_dump.hh>

template <class Auto>
unsigned determinist_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  typedef Auto automaton_t;

  
  tests::Tester t(tg.verbose());
  GenRandomAutomata<automaton_t> gen(time(0x0));
  
  const unsigned nb_tests = 1;
  unsigned success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t dfa = gen.generate_dfa(50);;
      if (is_deterministic(dfa))
	++success;
    } 
  std::string rate;
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "is_determinist on randomly generated dfa " + rate, success == nb_tests);

  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {     
      automaton_t automata = gen.generate(4, 8);
      automaton_t dfa      = determinize(automata);
      if (is_deterministic(dfa))
	++success;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "determinize on randomly generated automaton " + rate, success == nb_tests);
  
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_DETERMINIST_TEST_HH