// global_consistency_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_CONTEXT_HEADERS_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH
# define VCSN_TESTS_CONTEXT_HEADERS_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH

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
  TEST_TYPE(alphabet_t, monoid_t::alphabet_t);
  TEST_TYPE(monoid_t, monoid_t);
  TEST_TYPE(semiring_t, semiring_t);
  TEST_TYPE(series_set_t, series_set_t);
  TEST_TYPE(automata_set_t, set_t);
  TEST_TYPE(output_series_set_t, semiring_t);

  alphabet_t				in_at;
  in_at.insert('a');
  in_at.insert('b');
  alphabet_t				out_at;
  out_at.insert('c');
  out_at.insert('d');

  alphabet_t				other_in_at;
  out_at.insert('e');
  out_at.insert('f');

  monoid_t				out_md (out_at);
  monoid_t				other_in_md (other_in_at);
  monoid_t				in_md(in_at);
  output_series_set_t::semiring_t	out_sg;
  output_series_set_t			out_ss(out_sg, out_md);
  series_set_t				ss (out_ss, in_md);
  automata_set_t			aa (ss);

  series_set_t				ss_2 (out_ss, other_in_md);

  automaton_t		a1 = make_automaton(in_at, out_at);
  automaton_t		a2 = make_automaton(in_at.begin(), in_at.end(),
					    out_at.begin(), out_at.end());
  automaton_t		a3 = make_automaton(other_in_at, out_at);

  TEST(t, "alphabet inegality is consistent", in_md != other_in_md);
  TEST(t, "make_automaton is consistent.", a1 == a2);
  TEST(t, "make_automaton gives a correct alphabet.",
       a1.structure().series().monoid().alphabet() == in_at);
  TEST(t, "make_automaton gives a correct monoid.",
       a1.structure().series().monoid() == in_md);
  TEST(t, "make_automaton gives a correct semiring.",
       a1.structure().series().semiring() == out_ss);
  TEST(t, "make_automaton gives a correct automata set.", a1.structure() == aa);
  TEST(t, "automata set inegality is consistent.",
       a1.structure() != a3.structure());

  return t.all_passed();
}

#endif // ! VCSN_TESTS_CONTEXT_HEADERS_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH
