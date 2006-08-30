// transpose_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_TRANSPOSE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_TRANSPOSE_TEST_HH

# include <vaucanson/algorithms/transpose.hh>

template <class Auto>
bool   transpose_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);
  tests::Tester t(tg);

  for (int i = 0; i < 100; ++i)
  {
    alphabet_t	at;
    letter_t		la = at.random_letter(); at.insert(la);
    letter_t		lb = at.random_letter(); at.insert(lb);
    monoid_t		md (at);
    semiring_t	sg;
    series_set_t	ss (sg, md);
    automata_set_t	aa (ss);

    automaton_t	au1 (aa);

    // FIXME: Write a real test!
    vcsn::transpose(au1);
  }
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_TRANSPOSE_TEST_HH
