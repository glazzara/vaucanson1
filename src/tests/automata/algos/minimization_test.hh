// minimization_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003,2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_MINIMIZATION_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_MINIMIZATION_TEST_HH

# include <sstream>
# include <map>
# include <algorithm>
# include <list>
# include <time.h>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/minimization_hopcroft.hh>
# include <vaucanson/algorithms/minimization_moore.hh>
# include <vaucanson/algorithms/trim.hh>
# include <check/tester.hh>


template <class Auto>
unsigned minimization_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;

  typedef GenRandomAutomata<Auto>  gen_auto_t;
  typedef Auto			   automaton_t;

  tests::Tester t(tg.verbose());
  gen_auto_t    gen(time(0x0));

  const unsigned nb_test    = 20;
  unsigned success_hopcroft = 0;
  unsigned success_moore    = 0;

  for (unsigned i = 0; i < nb_test; i++)
    {
      automaton_t work = gen.generate_dfa(4, 5);

      if (t.verbose() == tests::high)
	{
	  TEST_MSG("Automaton saved in /tmp.");
	  SAVE_AUTOMATON_DOT("/tmp", "minimization_initial", work, i);
	}

      automaton_t temp = trim(determinize(transpose(work)));
      //      temp = trim(determinize(temp));

      automaton_t minimize =
	trim(determinize(transpose(temp)));
      if (t.verbose() == tests::high)
	{
	  TEST_MSG("Automaton saved in /tmp.");
	  SAVE_AUTOMATON_DOT("/tmp", "minimization_broz", temp, i);
	}

      automaton_t hopcroft = trim(minimization_hopcroft(work));
      automaton_t moore = trim(minimization_moore(work));

      if (t.verbose() == tests::high)
	{
	  TEST_MSG("Automaton saved in /tmp.");
	  SAVE_AUTOMATON_DOT("/tmp", "minimization_hopcroft", hopcroft, i);
	}

      if (t.verbose() == tests::high)
	{
	  TEST_MSG("Automaton saved in /tmp.");
	  SAVE_AUTOMATON_DOT("/tmp", "minimization_moore", moore, i);
	}

      if ((minimize.states().size() == hopcroft.states().size()) &&
	  (minimize.edges().size() ==  hopcroft.edges().size()))
	++success_hopcroft;
      else if (t.verbose() == tests::high)
	{
	  std::ostringstream s;
	  s << "Hopcroft failed on " << i << std::ends;
	  TEST_MSG(s.str());
	}

      if ((minimize.states().size() == moore.states().size()) &&
	  (minimize.edges().size() ==  moore.edges().size()))
	++success_moore;
      else if (t.verbose() == tests::high)
	{
	  std::ostringstream s;
	  s << "Moore failed on " << i << std::ends;
	  TEST_MSG(s.str());
	}

    }

  std::string rate_hopcroft;
  SUCCESS_RATE(rate_hopcroft, success_hopcroft, nb_test);
  std::string rate_moore;
  SUCCESS_RATE(rate_moore, success_moore, nb_test);
  TEST(t, "Hopcroft minimization "+rate_hopcroft, success_hopcroft == nb_test);
  TEST(t, "Moore minimization    "+rate_moore,    success_moore    == nb_test);

  return t.all_passed();
}
#endif // VCSN_TESTS_AUTOMATA_ALGOS_MINIMIZATION_TEST_HH
