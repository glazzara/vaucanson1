// compute_test.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef TESTS_COMPUTE_TEST_HH
# define TESTS_COMPUTE_TEST_HH

# include <check/tests_stuff.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algorithms/compute.hh>

using namespace vcsn;

template <class Auto, class Letter>
bool odd_language_test(const Auto& a, const Letter& l)
{
  AUTOMATON_TYPES(Auto);
  for (unsigned i = 0; i < 10; ++i)
    {
      monoid_elt_t w;
      for (unsigned j = 0; j < 2 * i + 3; ++j)
	w *= monoid_elt_t(l);
      if (compute(a, w) == a.series().zero_)
	return false;
    }
  return true;
}

template <class Auto, class Letter>
bool even_language_test(const Auto& a, const Letter& l)
{
  AUTOMATON_TYPES(Auto);
  for (unsigned i = 1; i < 10; ++i)
    {
      monoid_elt_t w;
      for (unsigned j = 0; j < 2 * i; ++j)
	w *= monoid_elt_t(l);
      if (compute(a, w) != a.series().zero_)
	return false;
    }
  return true;
}

template <class Auto>
bool compute_test(tests::Tester& t)
{
  AUTOMATON_TYPES(Auto);
  TEST_MSG("Basic test on a well-known automaton.");
  vcsn::tools::GenRandomAutomata<Auto> gen(time(0));
  Auto	a = gen.empty();
  hstate_t h1 = a.add_state();
  hstate_t h2 = a.add_state();
  hstate_t h3 = a.add_state();
  letter_t l  = a.series().monoid().alphabet().choose();

  a.add_letter_edge(h1, h2, l);
  a.add_letter_edge(h2, h3, l);
  a.add_letter_edge(h3, h2, l);
  a.set_initial(h1);
  a.set_final(h2);

  // Generate words with odd length.
  TEST(t, "Test words in the language.", odd_language_test(a, l));
  TEST(t, "Test words not in the language.", even_language_test(a, l));

  return t.all_passed();
}


#endif // TESTS_COMPUTE_TEST_HH
