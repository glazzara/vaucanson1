// free_monoid_product_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004, 2005 The Vaucanson Group.
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

#ifndef VCSN_TESTS_ALGEBRA_FREE_MONOID_PRODUCT_FREE_MONOID_PRODUCT_TEST_HH
# define VCSN_TESTS_ALGEBRA_FREE_MONOID_PRODUCT_FREE_MONOID_PRODUCT_TEST_HH

#include <vaucanson/misc/functors.hh>

template <typename S, typename T>
bool free_monoid_product_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T>					element_t;
  typedef S						freemonoid_product_t;
  typedef typename freemonoid_product_t::first_monoid_t	first_monoid_t;
  typedef typename freemonoid_product_t::second_monoid_t
							second_monoid_t;
  typedef typename first_monoid_t::alphabet_t		first_alphabet_t;
  typedef typename second_monoid_t::alphabet_t		second_alphabet_t;

  first_alphabet_t	first_base;
  second_alphabet_t	second_base;
  size_t		test_sizes[] =
    {
      1,
      first_base.max_size() >= 2 ? 2 : 1,
      first_base.max_size() <= 256 ? first_base.max_size() / 2 : 128,
      first_base.max_size() <= 256 ? first_base.max_size() : 256
    };

  bool monoid_error = false;
  bool neutral_error = false;
  bool mirror_error = false;
  bool length_error = false;

  for (size_t i = 0; i < sizeof (test_sizes) / sizeof (size_t); ++i)
    {
      first_alphabet_t first_alpha (first_base);
      second_alphabet_t second_alpha (second_base);
      for (size_t j = 0; j < test_sizes[i]; ++j)
	{
	  typename first_alphabet_t::letter_t l1;
	  typename second_alphabet_t::letter_t l2;
	  do
	    {
	      l1 = first_alpha.random_letter();
	      l2 = second_alpha.random_letter();
	    }
	  while (first_alpha.contains(l1) or second_alpha.contains(l2));
	  first_alpha.insert(l1);
	  second_alpha.insert(l2);
	}

      first_monoid_t		first_monoid (first_alpha);
      second_monoid_t		second_monoid(second_alpha);

      freemonoid_product_t	freemonoid_product(first_monoid,
						   second_monoid);

      if ((freemonoid_product.first_monoid() != first_monoid) or
	  (freemonoid_product.second_monoid() != second_monoid))
	monoid_error = true;

      element_t ab (freemonoid_product);
      if (first_alpha.size() and second_alpha.size())
	ab = freemonoid_product.choose(SELECT(T));
      element_t ba (ab);
      ba.mirror();

      element_t e = freemonoid_product.identity(SELECT(T));


      if (((ab * e) != ab) or ((e * ba) != ba))
	neutral_error = true;

      if (mirror(mirror(ab)) != ab)
	mirror_error = true;

      std::string first_word;
      std::string second_word;

      for (int i = 1; i <= 10; ++i)
	{
	  char t =  first_alpha.choose();
	  first_word += t;
	}

      for (int j = 1; j <= 15; ++j)
	second_word += second_alpha.choose();

      std::pair<std::string, std::string> p = make_pair(first_word,
							second_word);

      element_t w(freemonoid_product, p);

      std::pair<int, int> pair_len = w.length(utility::pair<int>());
      int add_len = w.length(std::plus<int>());

      std::pair<int, int> len (10, 15);

      if ((pair_len != len) or (add_len != 25))
	length_error = true;

    }


  TEST(t, "Monoid accessors are correct.", not monoid_error);
  TEST(t, "Neutral element is correct.", not neutral_error);
  TEST(t, "Mirror is idempotent.", not mirror_error);
  TEST(t, "Length is correct.", not length_error)

  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_FREE_MONOID_FREE_MONOID_TEST_HH
