// add_edge_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ADD_EDGE_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ADD_EDGE_TEST_HH

# include <map>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/handlers.hh>

template <class Auto>
unsigned add_edge_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;
  GenRandomAutomata<Auto> gen(time(0x0));

  automaton_t automaton = gen.empty();

  hstate_t s1 = automaton.add_state();
  hstate_t s2 = automaton.add_state();

  TEST(t, "Initial number of edge = 0.", automaton.edges().size() == 0);

  hedge_t h1 = automaton.add_series_edge(s1, s2, series_set_elt_t(automaton.structure().series()));

  TEST(t, "Number of edge after one add_edge = 1.",
       automaton.edges().size() == 1);

  automaton.del_edge(h1);

  TEST(t, "Number of edge after one deletion = 0.",
       automaton.edges().size() == 0);

  std::set<hedge_t> s;
  const std::set<hedge_t>& sc = s;
  for (unsigned i = 0; i < 3; ++i)
    {
      hstate_t p1 = automaton.add_state();
      hstate_t p2 = automaton.add_state();
      s.insert(automaton.add_series_edge(p1, p2,
					series_set_elt_t(automaton.structure().series())));
    }
  EQTEST(t, "Number of edge after three edge additions = 3.",
	 automaton.edges().size(), 3);
  for (std::set<hedge_t>::const_iterator i = sc.begin();
       i != sc.end(); ++i)
    automaton.del_edge(*i);
  EQTEST(t, "Number of edge after total deletion in growing order = 0.",
	 automaton.edges().size(), 0);

  for (unsigned i = 0; i < 3; ++i)
    {
      hstate_t p1 = automaton.add_state();
      hstate_t p2 = automaton.add_state();
      s.insert(automaton.add_series_edge(p1, p2,
					series_set_elt_t(automaton.structure().series())));
    }
  EQTEST(t, "Number of edge after three edge additions = 3.",
	 automaton.edges().size(), 3);
  for (std::set<hedge_t>::const_reverse_iterator i = sc.rbegin();
       i != sc.rend(); ++i)
    automaton.del_edge(*i);
  EQTEST(t, "Number of edge after total deletion in decreasing order = 0.",
	 automaton.edges().size(), 0);

  std::vector<hedge_t> vs;
  for (unsigned i = 0; i < 100; ++i)
    {
      hstate_t p1 = automaton.add_state();
      hstate_t p2 = automaton.add_state();
      vs.push_back(automaton.add_series_edge(p1, p2,
					    series_set_elt_t(automaton.structure().series())));
    }
  std::random_shuffle(vs.begin(), vs.end());
  EQTEST(t, "Number of edge after 100 edge additions = 100.",
	 automaton.edges().size(), 100);
  for (std::vector<hedge_t>::const_iterator i = vs.begin();
       i != vs.end(); ++i)
    automaton.del_edge(*i);
  EQTEST(t, "Number of edge after total deletion in random order = 0.",
	 automaton.edges().size(), 0);


  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ADD_EDGE_TEST_HH
