// generalized_test.hh
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

#ifndef GENERALIZED_TEST_HH
# define GENERALIZED_TEST_HH

# include <check/tests_stuff.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/automata/concrete/generalized.hh>

using namespace vcsn;

template <class Auto>
bool generalized_test(tests::Tester& t)
{
  AUTOMATON_TYPES(Auto);
  TEST_MSG("Basic test on a well-known automaton.");
  vcsn::tools::GenRandomAutomata<Auto> gen(time(0));
  Auto	a = gen.generate(10,20);
  typename generalized_traits<Auto>::automaton_t a_ = 
    generalized(a);
  return true;
}

#endif // GENERALIZED_TEST_HH
