// berry_sethi_test.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_TESTS_AUTOMATA_ALGOS_BERRY_SETHI_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_BERRY_SETHI_TEST_HH

# include <vaucanson/tools/usual.hh>
# include <vaucanson/algorithms/berry_sethi.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>
# include <vaucanson/algorithms/krat_exp_realtime.hh>

template <class Auto>
bool	berry_sethi_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  tests::Tester		t(tg.verbose());

  for (int i = 0; i < 10; ++i)
    {
      alphabet_t	at;
      letter_t		la = at.random_letter(); at.insert(la);
      letter_t		lb = at.random_letter(); at.insert(lb);
      monoid_t		md (at);
      semiring_t	sg;
      series_set_t		ss (sg, md);
      automata_set_t	aa (ss);

      krat_t		exp(ss);
      // We want short expressions
      do
	exp = ss.choose(SELECT(exp_t));
      while (realtime(exp).depth() > 10);
      automaton_t	au (aa);

      // FIXME: Write a real test!
      berry_sethi(au, exp);
    }
  return t.all_passed();
}

#endif // VCSN_TESTS_AUTOMATA_ALGOS_BERRY_SETHI_TEST_HH
