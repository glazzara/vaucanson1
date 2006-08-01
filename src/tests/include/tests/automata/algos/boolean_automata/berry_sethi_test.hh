// berry_sethi_test.hh: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_BERRY_SETHI_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_BERRY_SETHI_TEST_HH

# include <vaucanson/algorithms/berry_sethi.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>
# include <vaucanson/algorithms/krat_exp_realtime.hh>

template <class Auto>
bool	berry_sethi_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  tests::Tester t(tg);

  for (int i = 0; i < 10; ++i)
    {
      alphabet_t	at;
      letter_t		la = at.random_letter(); at.insert(la);
      letter_t		lb = at.random_letter(); at.insert(lb);
      monoid_t		md (at);
      semiring_t	sg;
      series_set_t		ss (sg, md);
      automata_set_t	aa (ss);

      krat_t		exp(ss);
      // We want short expressions
      do
	exp = ss.choose(SELECT(exp_t));
      while (realtime(exp).depth() > 10);
      automaton_t	au (aa);

      // FIXME: Write a real test!
      berry_sethi(au, exp);
    }
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_AUTOMATA_BERRY_SETHI_TEST_HH
