// free_monoid-test.cc
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <vaucanson/algebra/concrete/free_monoid/predefs.hh>
# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>

# include <check/tests_stuff.hh>
# include <fundamental/design_pattern-test.hh>

template <typename S, typename T> 
bool test_free_monoid(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T> element_t;
  element_t a;
  TEST_MSG("Get the neural element of this free monoid.");
  element_t e = a.set().identity(SELECT(T));
  
  test_design_pattern<S, T>();
  TEST(t, "Neutral element on the right.", (a * e) == a);
  TEST(t, "Neutral element on the left." , (e * a) == a);
  TEST(t, "Mirror is idempotent.", mirror(mirror(a)) == a);

  return t.all_passed(); 
}

int main(int argc, char **argv)
{
  using namespace vcsn::algebra;
  tests::verbose_level_e verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = tests::none;
  else
    verbose = tests::low;
  tests::Tester t(verbose);

  if (test_free_monoid<char_letter::Words, std::string>(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

