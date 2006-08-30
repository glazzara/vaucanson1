// compute_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_COMPUTE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_COMPUTE_TEST_HH

# include <vaucanson/tools/xml_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/eval.hh>

using namespace vcsn;

template <class Auto, class Letter>
bool odd_language_test(const Auto& a, const Letter& l)
{
  AUTOMATON_TYPES(Auto);
  for (unsigned i = 0; i < 10; ++i)
  {
    monoid_elt_t w (a.structure().series().monoid());
    for (unsigned j = 0; j < 2 * i + 3; ++j)
      w *= l;
    if (eval(a, w) == zero_as<semiring_elt_value_t>
	::of(a.structure().series().semiring()))
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
    monoid_elt_t w (a.structure().series().monoid());
    for (unsigned j = 0; j < 2 * i; ++j)
      w *= l;
    if (eval(a, w) != zero_as<semiring_elt_value_t>
	::of(a.structure().series().semiring()))
      return false;
  }
  return true;
}

template <class Auto>
bool compute_test(tests::Tester& t)
{
  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);
  TEST_MSG("Basic test on a well-known automaton.");
  vcsn::GenRandomAutomata<Auto> gen;
  Auto	a = gen.empty();
  hstate_t h1 = a.add_state();
  hstate_t h2 = a.add_state();
  hstate_t h3 = a.add_state();
  letter_t l  = a.structure().series().monoid().alphabet().choose();

  a.add_letter_transition(h1, h2, l);
  a.add_letter_transition(h2, h3, l);
  a.add_letter_transition(h3, h2, l);
  a.set_initial(h1);
  a.set_final(h2);

  // Generate words with odd length.
  TEST(t, "Test words in the language.", odd_language_test(a, l));
  TEST(t, "Test words not in the language.", even_language_test(a, l));

  return t.all_passed();
}


#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_COMPUTE_TEST_HH
