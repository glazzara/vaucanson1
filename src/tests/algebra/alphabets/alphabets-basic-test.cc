// element-full-test.cc
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

#include <vaucanson/config/system.hh>
#include <fundamental/design_pattern-test.hh>
#include <check/tests_stuff.hh>
#include <set>
#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/alphabets/predefs.hh>
#include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>


using namespace vcsn;

template <typename S, typename T> 
bool test_alphabet(tests::Tester& t)
{
  using namespace vcsn::algebra;

  typedef Element<S, T> element_t;

  TEST_MSG("Instanciate an alphabet 'A'.");
  element_t a;
  TEST_MSG("Insert an 'a' in A.");  
  a.insert('a');
  
  test_design_pattern<S, T>();

  TEST(t, "'a' is in A."    , a.contains('a'));
  TEST(t, "'b' is not in A.", !a.contains('b'));
  TEST(t, "A is finite and its cardinal is one.",
       (a.is_finite()) && (a.size() == 1));
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

  if (test_alphabet<char_letter::Alphabets, std::set<char> >(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

