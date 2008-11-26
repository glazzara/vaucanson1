// global_consistency_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_TESTS_CONTEXT_HEADERS_FMP_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH
# define VCSN_TESTS_CONTEXT_HEADERS_FMP_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH

# include <vaucanson/misc/static.hh>

bool
operator == (const automaton_t& a, const automaton_t& b)
{
  return
    a.states().size() == b.states().size() and
    a.transitions().size() == b.transitions().size() and
    a.initial().size() == b.initial().size() and
    a.final().size() == b.final().size();
}

# define TYPE_OK(T1, T2) vcsn::misc::static_eq<T1, typename Automaton::T2>::value
# define TEST_TYPE(T1, T2)				\
  TEST(t, #T1 " is consistent.", TYPE_OK(T1, T2))

template <class Automaton>
bool
global_consistency_test(tests::Tester& t)
{
  TEST_TYPE(first_alphabet_t, monoid_t::first_monoid_t::alphabet_t);
  TEST_TYPE(second_alphabet_t, monoid_t::second_monoid_t::alphabet_t);
  TEST_TYPE(first_monoid_t, monoid_t::first_monoid_t);
  TEST_TYPE(second_monoid_t, monoid_t::second_monoid_t);
  TEST_TYPE(monoid_t, monoid_t);
  TEST_TYPE(semiring_t, semiring_t);
  TEST_TYPE(series_set_t, series_set_t);
  TEST_TYPE(automata_set_t, set_t);

  AUTOMATON_TYPES(Automaton);
  typedef typename monoid_t::first_monoid_t	first_monoid_t;
  typedef typename monoid_t::second_monoid_t	second_monoid_t;
  typedef typename first_monoid_t::alphabet_t	first_alphabet_t;
  typedef typename second_monoid_t::alphabet_t	second_alphabet_t;

  bool			test_done = false;

  typedef typename first_alphabet_t::set_t::letter_t	first_letter_t;
  typedef typename second_alphabet_t::set_t::letter_t	second_letter_t;

  first_alphabet_t		first_at;
  first_letter_t a = first_at.random_letter();
  first_letter_t b = first_at.random_letter();
  while (a == b) b = first_at.random_letter();
  first_at.insert(a);
  first_at.insert(b);

  second_alphabet_t		second_at;
  second_letter_t x = second_at.random_letter();
  second_letter_t y = second_at.random_letter();
  while (x == y) y = second_at.random_letter();
  second_at.insert(x);
  second_at.insert(y);

  first_alphabet_t	other_first_at;
  first_letter_t c = other_first_at.random_letter();
  first_letter_t d = other_first_at.random_letter();
  while (c == d) c = other_first_at.random_letter();
  other_first_at.insert(c);
  other_first_at.insert(d);

  second_alphabet_t		other_second_at;
  second_letter_t z = other_second_at.random_letter();
  second_letter_t tt = other_second_at.random_letter();
  while (z == tt) tt = other_second_at.random_letter();
  other_second_at.insert(z);
  other_second_at.insert(tt);

  first_monoid_t	first_md (first_at);
  second_monoid_t	second_md (second_at);

  monoid_t		fmp(first_md, second_md);

  semiring_t		sg;
  series_set_t		ss (sg, fmp);
  automata_set_t	aa (ss);

  typedef std::basic_string<first_letter_t> first_word_t;
  typedef std::basic_string<second_letter_t> second_word_t;

  first_word_t waa;
  waa += a;
  waa += a;

  second_word_t wyx;
  wyx += y;
  wyx += x;

  monoid_elt_value_t	fmp_elt (waa, wyx);

  monoid_elt_t	couple = make_couple(first_at, second_at, waa, wyx);

  TEST(t, "make_couple works.", fmp_elt == couple.value());

  while (not test_done)
    try
    {
      automaton_t		a1 = make_automaton(first_at, second_at);
      automaton_t		a2 = make_automaton(first_at.begin(),
						    first_at.end(),
						    second_at.begin(),
						    second_at.end());
      automaton_t		a3 (aa);
      automaton_t		a4 = make_automaton(other_first_at,
						    other_second_at);

      TEST(t, "make_automaton is consistent.", a1 == a2);
      TEST(t, "make_automaton gives a correct alphabet.",
	   a1.structure().series().monoid().first_monoid().alphabet()
	   == first_at
	   and
	   a1.structure().series().monoid().second_monoid().alphabet()
	   == second_at);
      TEST(t, "new automaton alphabet is consistent.",
	   a1.structure().series().monoid().first_monoid().alphabet()
	   != other_first_at
	   and
	   a1.structure().series().monoid().second_monoid().alphabet()
	   != other_second_at);
      TEST(t, "make_automaton gives a correct monoid.",
	   a1.structure().series().monoid() == fmp);
      TEST(t, "make_automaton gives a correct semiring.",
	   a1.structure().series().semiring() == sg);
      TEST(t, "make_automaton gives a correct automata set.",
	   a1.structure() == aa);
      TEST(t, "new automata set is consistent.",
	   a1.structure() != a4.structure());

      test_done = true;
    }
    catch (...)
    {
      test_done = false;
    }
  return t.all_passed();

}

#endif // ! VCSN_TESTS_CONTEXT_HEADERS_FMP_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH
