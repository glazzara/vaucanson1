// brzozowski_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004, 2005 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_BRZOZOWSKI_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_BRZOZOWSKI_TEST_HH

# include <vaucanson/algorithms/brzozowski.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>

template <class Auto>
bool	brzozowski_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  tests::Tester		t(tg.verbose());

  for (int i = 0; i < 100; ++i)
    {
      alphabet_t	at;
      letter_t		la = at.random_letter(); at.insert(la);
      letter_t		lb = at.random_letter(); at.insert(lb);
      monoid_t		md (at);
      semiring_t	sg;
      series_set_t		ss (sg, md);
      automata_set_t	aa (ss);

      krat_t		exp = ss.choose(SELECT(exp_t));
      automaton_t	au (aa);

      // FIXME: Write a real test!
      brzozowski(au, exp);
    }
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_BRZOZOWSKI_TEST_HH
