// free_monoid_test.hh: this file is part of the Vaucanson project.
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
//

#ifndef VCSN_TESTS_ALGEBRA_FREE_MONOID_FREE_MONOID_TEST_HH
# define VCSN_TESTS_ALGEBRA_FREE_MONOID_FREE_MONOID_TEST_HH

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <design_pattern/design_pattern-test.hh>

template <typename S, typename T>
bool free_monoid_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T>					element_t;
  typedef typename element_t::set_t			freemonoid_t;
  typedef typename freemonoid_t::alphabets_elt_t	alphabet_t;

  // Instanciate a non-empty alphabet and a corresponding free monoid.
  alphabet_t	alpha;
  alpha.insert(alpha.random_letter());
  freemonoid_t	freemonoid (alpha);

  // Create a word.
  element_t a = freemonoid.choose(SELECT(T));

  // Do the tests.
  TEST_MSG("Get the neural element of this free monoid.");
  element_t e = freemonoid.identity(SELECT(T));

  test_design_pattern<S, T>();
  TEST(t, "Neutral element on the right.", (a * e) == a);
  TEST(t, "Neutral element on the left." , (e * a) == a);
  TEST(t, "Mirror is idempotent.", mirror(mirror(a)) == a);

  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_FREE_MONOID_FREE_MONOID_TEST_HH
