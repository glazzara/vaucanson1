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

# include <sstream>

template <typename S, typename T>
bool free_monoid_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T>					element_t;
  typedef typename element_t::set_t			freemonoid_t;
  typedef typename freemonoid_t::alphabets_elt_t	alphabet_t;
  typedef typename freemonoid_t::letter_t		letter_t;

  for (int i = 0; i < 200; ++i)
    {
      alphabet_t		alpha;
      for (int j = 0; j < i; ++j)
	{
	  letter_t l;
	  do
	    l = alpha.random_letter();
	  while (alpha.contains(l));
	  alpha.insert(l);
	}
      std::ostringstream astr;
      astr << alpha;
      TEST_MSG("Alphabet is " + astr.str() + ".");

      freemonoid_t		freemonoid (alpha);
      const freemonoid_t	const_freemonoid (alpha);

      TEST(t, "alphabet() (non-const).", freemonoid.alphabet() == alpha);
      TEST(t, "alphabet() (const).", const_freemonoid.alphabet() == alpha);

      // Create a word and its mirror.
      element_t ab (freemonoid);
      if (alpha.size())
	ab = freemonoid.choose(SELECT(T));
      element_t ba (ab);
      ba.mirror();

      // Do the tests.
      int l = ab.length() + ba.length();
      int m = l;
      TEST(t, "mirror() and length().", ab.length() == ba.length());

      bool						allright = true;
      typename element_t::const_iterator		abi = ab.begin();
      typename element_t::const_reverse_iterator	bai = ba.rbegin();
      while (allright and (abi != ab.end()) and
	     (bai != const_cast<const element_t&> (ba).rend()))
	{
	  if (*abi != *bai)
	    allright = false;
	  ++abi; --l;
	  ++bai; --l;
	}
      TEST(t, "const iterators.", not l);
      TEST(t, "mirror() [1].", (allright));
      TEST(t, "mirror() [2].", (abi == ab.end()) and
	   (bai == const_cast<const element_t&> (ba).rend()));

      element_t					old_ab = ab;
      element_t					old_ba = ba;
      typename element_t::iterator		abi2 = ab.begin();
      typename element_t::reverse_iterator	bai2 = ba.rbegin();
      for (typename element_t::const_iterator i = old_ba.begin();
	   i != old_ba.end();
	   ++i)
	{
	  *abi2 = *i;
	  abi2++; ++l;
	}
      for (typename element_t::const_reverse_iterator i = old_ab.rbegin();
	   i != const_cast<const element_t&> (old_ab).rend();
	   ++i)
	{
	  *bai2 = *i;
	  bai2++; ++l;
	}

      TEST(t, "iterators [1].", l == m);
      TEST(t, "iterators [2].", (abi2 == ab.end()) and (bai2 == ba.rend()));
      std::cout << ab << std::endl << old_ba << std::endl;
      TEST(t, "iterators [3].", (ab == old_ba) and (ba == old_ab));


      TEST_MSG("Get the neural element of this free monoid.");
      element_t e = freemonoid.identity(SELECT(T));

      test_design_pattern<S, T>(const_freemonoid);
      TEST(t, "Neutral element on the right.", (ab * e) == ab);
      TEST(t, "Neutral element on the left." , (e * ba) == ba);
      TEST(t, "Mirror is idempotent.", mirror(mirror(ab)) == ab);
    }
  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_FREE_MONOID_FREE_MONOID_TEST_HH
