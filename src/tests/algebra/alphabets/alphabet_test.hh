// alphabet_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_ALPHABETS_ALPHABET_TEST_HH
# define VCSN_TESTS_ALGEBRA_ALPHABETS_ALPHABET_TEST_HH

#include <vaucanson/config/system.hh>
#include <design_pattern/design_pattern-test.hh>
#include <check/tester.hh>
#include <vaucanson/design_pattern/design_pattern.hh>

using namespace vcsn;

template <typename S, typename T> 
bool alphabet_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  typedef Element<S, T> element_t;
  typedef typename element_t::letter_t letter_t;

  TEST_MSG("Instantiate an alphabet A.");
  element_t A;
  TEST_MSG("Insert a random letter a in A.");  
  letter_t a = A.random_letter();
  letter_t b = A.random_letter();
  A.insert(a);
  TEST(t, "a is in A.", A.contains(a));
  TEST(t, "b is not in A.", !A.contains(b));
  TEST(t, "A is finite and its cardinal is one.",
       (A.is_finite()) && (A.size() == 1));
  return t.all_passed(); 
}

#endif // VCSN_TESTS_ALGEBRA_ALPHABETS_ALPHABET_TEST_HH
