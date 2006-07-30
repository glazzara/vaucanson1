// global_consistency_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_CONTEXT_HEADERS_AUTOMATA_GLOBAL_CONSISTENCY_TEST_HH
# define VCSN_TESTS_CONTEXT_HEADERS_AUTOMATA_GLOBAL_CONSISTENCY_TEST_HH

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

# define TYPE_OK(T1, T2) \
  vcsn::misc::static_eq<T1, typename Automaton::T2>::value
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

  bool			test_done = false;

  alphabet_t		at;
  at.insert('a');
  at.insert('b');

  alphabet_t		other_at;
  at.insert('c');
  at.insert('d');

  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);

  rat_exp_t		e (ss);
  rat_exp_t		f = make_rat_exp(at);
  rat_exp_t		g = make_rat_exp(at, "a+b");
  TEST(t, "make_rat_exp works. [1/3]", e == f);
  TEST(t, "make_rat_exp works. [2/3]", g != f);

  rat_exp_t::support_t			s = g.supp();
  rat_exp_t::support_t::const_iterator	i = s.begin();
  TEST(t, "make_rat_exp works. [3/3]",
       s.size() == 2 and *i == "a" and *(++i) == "b");

  while (not test_done)
    try
    {
      do
	e = ss.choose(SELECT(rat_exp_impl_t));
      while (e == vcsn::algebra::zero_as<rat_exp_impl_t>::of(ss));

      if (t.verbose (tests::Tester::high))
	std::cerr << "Expression is: " << e << std::endl;

      automaton_t a1 = make_automaton(at);
      automaton_t a2 = make_automaton(at.begin(), at.end());
      automaton_t a3 (aa);
      automaton_t a4 = standard_of(e);
      automaton_t a5 = thompson_of(e);
      automaton_t a6 = make_automaton(other_at);

      TEST(t, "make_automaton is consistent.", a1 == a2);
      TEST(t, "make_automaton gives a correct alphabet.",
	   a1.structure().series().monoid().alphabet() == at);
      TEST(t, "new automaton alphabet is consistent.",
	   a1.structure().series().monoid().alphabet() != other_at);
      TEST(t, "make_automaton gives a correct monoid.",
	   a1.structure().series().monoid() == md);
      TEST(t, "make_automaton gives a correct semiring.",
	   a1.structure().series().semiring() == sg);
      TEST(t, "make_automaton gives a correct automata set.",
	   a1.structure() == aa);
      TEST(t, "new automata set is consistent.",
	   a1.structure() != a6.structure());

      standard_of(a3, e.value());
      TEST(t, "standard_of is consistent.", a3 == a4);

      thompson_of(a3, e.value());
      TEST(t, "thompson_of is consistent.", a3 == a5);
      test_done = true;
    }
    catch (...)
    {
      test_done = false;
    }
  return t.all_passed();
}

#endif // ! VCSN_TESTS_CONTEXT_HEADERS_AUTOMATA_GLOBAL_CONSISTENCY_TEST_HH
