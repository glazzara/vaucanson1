// series-test.cc
//
// $Id$
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
#include <set>
#include <check/tests_stuff.hh>
#include <fundamental/design_pattern-test.hh>
#include <algebra/series/series-test.hh>
#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>
#include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>

using namespace vcsn;

int main(int argc, char **argv)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  tests::verbose_level_e verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = tests::none;
  else
    verbose = tests::low;
  tests::Tester t(verbose);

  if (test_series<
      Series<
      NumericalSemiring, char_letter::Words>, 
      polynom<std::string, int> >(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

