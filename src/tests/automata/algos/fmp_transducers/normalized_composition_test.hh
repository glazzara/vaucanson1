// normalized_composition_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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

#ifndef VCSN_TESTS_FMP_TRANSDUCERS_NORMALIZED_COMPOSITION_TEST_HH
# define VCSN_TESTS_FMP_TRANSDUCERS_NORMALIZED_COMPOSITION_TEST_HH

# include <vaucanson/algorithms/normalized_composition.hh>
# include <vaucanson/algorithms/fmp_to_realtime.hh>
# include <vaucanson/algorithms/evaluation.hh>
# include <vaucanson/boolean_transducer.hh>
# include <vaucanson/boolean_automaton.hh>

template <class Automaton>
bool
normalized_composition_test(tests::Tester& t)
{
  using namespace vcsn;

  AUTOMATON_TYPES(Automaton);

  typedef typename monoid_t::first_monoid_t	first_monoid_t;
  typedef typename monoid_t::second_monoid_t	second_monoid_t;
  typedef typename first_monoid_t::alphabet_t	first_alphabet_t;
  typedef typename second_monoid_t::alphabet_t	second_alphabet_t;

  first_alphabet_t		first_at;
  first_at.insert('a');
  first_at.insert('b');

  second_alphabet_t		second_at;
  second_at.insert('x');
  second_at.insert('y');

  second_alphabet_t		third_at;
  third_at.insert('z');
  third_at.insert('t');

  first_monoid_t		first_md (first_at);
  second_monoid_t		second_md (second_at);
  second_monoid_t		third_md (third_at);

  monoid_t			fmp(first_md, second_md);
  monoid_t			fmp2(second_md, third_md);
  monoid_t			fmp3(first_md, third_md);

  semiring_t			sg;

  series_set_t			ss (sg, fmp);
  series_set_t			ss2 (sg, fmp2);
  series_set_t			ss3 (sg, fmp3);

  automata_set_t		aa (ss);
  automata_set_t		aa2 (ss2);
  automata_set_t		aa3 (ss3);

  automaton_t		t1(aa);
  automaton_t		t2(aa2);
  automaton_t		t3(aa3);

  series_set_elt_t	series_elt1(ss);
  series_set_elt_t	series_elt2(ss);
  series_set_elt_t	series_elt3(ss);
  series_set_elt_t	series_elt4(ss);


  series_set_elt_t	series_elt21(ss);
  series_set_elt_t	series_elt22(ss);
  series_set_elt_t	series_elt23(ss);
  series_set_elt_t	series_elt24(ss);

  monoid_elt_value_t	fmp_elt1 ("a", "");
  monoid_elt_value_t	fmp_elt2 ("b", "x");
  monoid_elt_value_t	fmp_elt3 ("a", "y");
  monoid_elt_value_t	fmp_elt4 ("", "x");

  monoid_elt_value_t	fmp_elt21 ("", "z");
  monoid_elt_value_t	fmp_elt22 ("x", "t");
  monoid_elt_value_t	fmp_elt23 ("y", "");
  monoid_elt_value_t	fmp_elt24 ("y", "z");

  semiring_elt_value_t	semi_elt = true;

  series_elt1.assoc(fmp_elt1, semi_elt);
  series_elt2.assoc(fmp_elt2, semi_elt);
  series_elt3.assoc(fmp_elt3, semi_elt);
  series_elt4.assoc(fmp_elt4, semi_elt);

  series_elt21.assoc(fmp_elt21, semi_elt);
  series_elt22.assoc(fmp_elt22, semi_elt);
  series_elt23.assoc(fmp_elt23, semi_elt);
  series_elt24.assoc(fmp_elt24, semi_elt);

  hstate_t	st1 = t1.add_state();
  hstate_t	st2 = t1.add_state();
  hstate_t	st3 = t1.add_state();

  hstate_t	st21 = t2.add_state();
  hstate_t	st22 = t2.add_state();
  hstate_t	st23 = t2.add_state();


  t1.set_initial(st1);
  t1.set_final(st3);

  t2.set_initial(st21);
  t2.set_final(st23);

  hedge_t			h1 = t1.add_series_edge(st1, st2, series_elt1);
  hedge_t			h2 = t1.add_series_edge(st2, st3, series_elt2);
  hedge_t			h3 = t1.add_series_edge(st1, st2, series_elt3);
  hedge_t			h4 = t1.add_series_edge(st1, st3, series_elt4);


  hedge_t			h21 = t2.add_series_edge(st21, st22,
							 series_elt21);
  hedge_t			h22 = t2.add_series_edge(st22, st23,
							 series_elt22);
  hedge_t			h23 = t2.add_series_edge(st21, st23,
							 series_elt23);
  hedge_t			h24 = t2.add_series_edge(st21, st22,
							 series_elt24);

  t3 = normalized_composition(t1, t2);

  boolean_transducer::automaton_t trans1 =
    boolean_transducer::new_automaton(first_at, second_at);

  boolean_transducer::automaton_t trans2 =
    boolean_transducer::new_automaton(second_at, third_at);

  boolean_transducer::automaton_t trans3 =
    boolean_transducer::new_automaton(first_at, third_at);

  fmp_to_realtime(t1, trans1);
  fmp_to_realtime(t2, trans2);
  fmp_to_realtime(t3, trans3);

  boolean_automaton::rat_exp_t exp =
    boolean_automaton::new_rat_exp(first_at, "abbababa");

  TEST(t, "Normalized composition works.",
       (boolean_transducer::evaluation(trans3, exp) ==
	boolean_transducer::evaluation(trans2,
				       boolean_transducer::evaluation(trans1,
								      exp))));

  return t.all_passed();
}

#endif  // ! VCSN_TESTS_FMP_TRANSDUCERS_NORMALIZED_COMPOSITION_TEST_HH

