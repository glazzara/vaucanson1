// krat_exp_realtime_conflict_test.hh: this file is part of the Vaucanson
// project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_KRAT_EXP_REALTIME_CONFLICT_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_KRAT_EXP_REALTIME_CONFLICT_TEST_HH

# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/algorithms/krat_exp_realtime.hh>

# include <vaucanson/algebra/implementation/series/krat.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/tools/gen_random.hh>

template <class Auto>
unsigned krat_exp_realtime_conflict_test(tests::Tester& tg)
{
  tests::Tester			t(tg.verbose());

  // By  the  past  realtime()  in realtime.hh  was  conflicting  with
  // realtime()   in   krat_exp_realtime.hh.   The  following   is   a
  // corresponding regression test.
  AUTOMATON_TYPES(Auto);
  typedef
    vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>			krat_exp_t;

  alphabet_t	at;
  at.insert(at.random_letter());
  monoid_t	md (at);
  semiring_t	sg;
  series_set_t	ss(sg, md);
  krat_exp_t	e1 = ss.choose(SELECT(exp_t));
  krat_exp_t	e2 = realtime(e1);
  realtime_here(e1);
  TEST(t, "realtime(automaton) does not conflict with realtime(exp) [1].",
       e1 == e2);

  vcsn::GenRandomAutomata<Auto> generator;

  automaton_t	a = realtime(generator.generate(50, 60));
  TEST(t, "realtime(automaton) does not conflict with realtime(exp) [2].",
       true);

  automaton_t	b = generator.generate_with_epsilon(50, 60, 1, 15);
  realtime_here(b);
  TEST(t, "realtime(automaton) does not conflict with realtime(exp) [3].",
       true);

  return t.all_passed();
}

#endif // VCSN_TESTS_AUTOMATA_ALGOS_KRAT_EXP_REALTIME_CONFLICT_TEST_HH
