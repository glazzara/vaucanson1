// semiring-numerical-test.cc
//
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


// goal : provide a first static tests for numerical semiring families.
// FIXME: it will be use in a tests generator.

# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>

# include <algebra/semiring/semiring-test.hh>

# include <check/tests_stuff.hh>


int main(int argc, char **argv)
{
  tests::verbose_level_e verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = tests::none;
  else
    verbose = tests::low;
  tests::Tester t(verbose);
  if (test_semiring<vcsn::algebra::NumericalSemiring, int>(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
