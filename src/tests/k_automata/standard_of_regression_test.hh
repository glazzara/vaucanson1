// standard_of_regression_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_K_AUTOMATA_STANDARD_OF_REGRESSION_TEST_HH
# define VCSN_TESTS_K_AUTOMATA_STANDARD_OF_REGRESSION_TEST_HH

# include <vaucanson/algebra/implementation/series/krat.hh>
# include <vaucanson/algorithms/standard_of.hh>
# include <vaucanson/algorithms/eval.hh>
# include <vaucanson/tools/usual_macros.hh>

template <class Auto>
bool
standard_of_regression_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  tests::Tester t (tg.verbose());

  alphabet_t		at;
  letter_t		la = at.random_letter();
  at.insert(la);
  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);

  using vcsn::algebra::identity_as;
  using vcsn::algebra::zero_as;

  monoid_elt_t		ma (md, la);
  krat_t		a (ss, ma);
  semiring_elt_t	w (sg);
  do
    w = sg.choose(SELECT(semiring_elt_value_t));
  while (w == identity_as<semiring_elt_value_t>::of(sg) or
	 w == zero_as<semiring_elt_value_t>::of(sg)) ;

  krat_t e = a.star() * w; // WARNING: star() has side effects on a!

  automaton_t		au (aa);
  standard_of(au, e.value());

  TEST_MSG("Tests on \"a* w\".");
  TEST(t, "Number of states", au.states().size() == 2);
  TEST(t, "Number of initial states", au.initial().size() == 1);
  TEST(t, "Number of final states", au.final().size() == 2);
  TEST(t, "Number of edges", au.edges().size() == 2);

  bool b (true);
  for_each_initial_state(i, au)
    b = b and
    au.get_initial(*i) == identity_as<series_set_elt_value_t>::of(ss);
  TEST(t, "Weight of initials", b);

  b = true;
  for_each_edge(e, au)
    b = b and au.series_of(*e) == series_set_elt_t (ss, ma);
  TEST(t, "Weight of edges", b);

  b = true;
  for_each_final_state(f, au)
    b = b and au.get_final(*f) == series_set_elt_t (ss, w);
  TEST(t, "Weight of finals", b);

  TEST_MSG("Tests on \"(w a*)(w a*)\".");

  e = (w * a) * (w * a);
  standard_of(au, e.value());

  TEST(t, "Evaluation of 1 gives w * w.",
       eval(au, monoid_elt_t (md)) == w * w);

  TEST(t, "Evaluation of a gives w * w + w * w.",
       eval(au, ma) == w * w + w * w);

  TEST(t, "Evaluation of aa gives w * w + w * w + w * w.",
       eval(au, ma * ma) == w * w + w * w + w * w);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_K_AUTOMATA_STANDARD_OF_REGRESSION_TEST_HH
