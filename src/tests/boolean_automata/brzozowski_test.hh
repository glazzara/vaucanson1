// brzozowski_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_BOOLEAN_AUTOMATA_BRZOZOWSKI_TEST_HH
# define VCSN_TESTS_BOOLEAN_AUTOMATA_BRZOZOWSKI_TEST_HH

# include <vaucanson/algorithms/brzozowski.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>

template <class Auto>
bool	brzozowski_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  tests::Tester		t(tg.verbose());

  for (int i = 0; i < 100; ++i)
    {
      alphabet_t	at;
      letter_t		la = at.random_letter(); at.insert(la);
      letter_t		lb = at.random_letter(); at.insert(lb);
      monoid_t		md (at);
      semiring_t	sg;
      series_set_t		ss (sg, md);
      automata_set_t	aa (ss);

      krat_t		exp = ss.choose(SELECT(exp_t));
      automaton_t	au (aa);

      // FIXME: Write a real test!
      brzozowski(au, exp);
    }
  return t.all_passed();
}

#endif // ! VCSN_TESTS_BOOLEAN_AUTOMATA_BRZOZOWSKI_TEST_HH
