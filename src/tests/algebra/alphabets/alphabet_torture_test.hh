// alphabet_torture_test.hh: this file is part of the Vaucanson project.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_TESTS_ALGEBRA_ALPHABET_ALPHABET_TORTURE_TEST_HH
# define VCSN_TESTS_ALGEBRA_ALPHABET_ALPHABET_TORTURE_TEST_HH

# include <vaucanson/config/system.hh>
# include <design_pattern/design_pattern-test.hh>
# include <check/tester.hh>
# include <vaucanson/design_pattern/design_pattern.hh>

# include <set>

using namespace vcsn;

template <typename S, typename T>
bool alphabet_torture_test(tests::Tester& t)
{
  using namespace vcsn::algebra;

  typedef Element<S, T>			alphabet_t;
  typedef typename alphabet_t::letter_t	letter_t;

  std::set<letter_t>	alphaset;
  alphabet_t		base;
  size_t		test_sizes[] =
    {
      0,
      1,
      base.max_size() >= 2 ? 2 : 1,
      base.max_size() <= 256 ? base.max_size() / 2 : 128,
      base.max_size() <= 256 ? base.max_size() : 256
    };

  for (size_t i = 0; i < sizeof (test_sizes) / sizeof (size_t); ++i)
    {
      alphabet_t alpha (base);
      letter_t l;
      alphaset.clear();
      for (size_t j = 0; j < test_sizes[i]; ++j)
	{
	  do
	    l = alpha.random_letter();
	  while (alpha.contains(l));
	  alphaset.insert(l);
	  alpha.insert(l);
	}

      bool error = false;
      for (size_t k = 0; k < test_sizes[i]; ++k)
	{
	  l = alpha.choose();
	  if (alphaset.find(l) == alphaset.end())
	    error = true;
	}
      TEST(t, "Choose gives correct letters.", not error);

      error = false;
      for (typename std::set<letter_t>::const_iterator  it = alphaset.begin();
	   it != alphaset.end(); ++it)
	{
	  if (not alpha.contains(*it))
	    error = true;
	}
      TEST(t, "Contains gives correct letters.", not error);
    }
  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_ALPHABET_ALPHABET_TORTURE_TEST_HH
