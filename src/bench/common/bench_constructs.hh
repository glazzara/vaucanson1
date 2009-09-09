// bench_constructs.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_BENCH_COMMON_BENCH_CONSTRUCTS_HH
# define VCSN_BENCH_COMMON_BENCH_CONSTRUCTS_HH

/// Create an aut_2n automaton (has 2^n states once determinized).
/// See README_AUTOMATA for aut_2n.
automaton_t aut_2n(unsigned n)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');
  automaton_t a = make_automaton(alpha);

  std::vector<hstate_t>	c(n);
  for (unsigned i = 0; i < n; ++i)
    c[i] = a.add_state();
  for (unsigned i = 0; i < n - 1; ++i)
    a.add_letter_transition(c[i], c[i+1], 'a');
  a.add_letter_transition(c[n-1], c[0], 'a');
  for (unsigned i = 1; i < n; ++i)
  {
    a.add_letter_transition(c[i], c[i], 'b');
    a.add_letter_transition(c[i], c[i], 'c');
    a.add_letter_transition(c[i], c[0], 'b');
  }
  a.set_initial(c[0]);
  a.set_final(c[0]);

  return a;
}

/// Create an aut_ladybird automaton.
/// See README_AUTOMATA for aut_ladybird.
automaton_t aut_ladybird(unsigned n)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  // Alphabet.
  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  // Automaton.
  automaton_t a = make_automaton (alpha);

  hstate_t p = a.add_state ();
  hstate_t x = p;
  for(unsigned i = 1; i < n; ++i)
  {
    hstate_t y = a.add_state();
    a.add_letter_transition(x, y, 'a');
    a.add_letter_transition(y, y, 'b');
    a.add_letter_transition(y, y, 'c');
    a.add_letter_transition(y, p, 'c');
    x = y;
  }
  a.add_letter_transition(x, p, 'a');
  a.set_initial(p);
  a.set_final(p);

  return a;
}

/// Create a aut_debruijn automaton.
/// See README_AUTOMATA for debruijn.
automaton_t aut_debruijn(unsigned n)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');
  automaton_t a = make_automaton(alpha);

  n = 1 << n;

  for (unsigned i = 0; i < n; ++i)
    a.add_state();
  a.set_initial(0);
  for (unsigned i = 0; i < n; ++i)
  {
    a.add_letter_transition(i, (i * 2) % n, 'a');
    a.add_letter_transition(i, (i * 2 + 1) % n, 'b');
    if ((i << 1) & n)
      a.set_final(i);
  }

  return a;
}

/// Create a aut_linear_eps automaton (for epsilon removal).
/// See README_AUTOMATA for aut_linear_eps.
automaton_t aut_linear_eps(unsigned n)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t alpha;
  alpha.insert('a');
  automaton_t a = make_automaton(alpha);

  int size = n * 500;

  std::vector<hstate_t> c(size);
  monoid_elt_t monoid_identity =
    vcsn::algebra::identity_as<monoid_elt_value_t>::of(a.series().monoid());
  semiring_elt_t semiring_elt_id =
    vcsn::algebra::identity_as<semiring_elt_value_t>::of(a.series().semiring());
  series_set_elt_t s(a.series());

  s.assoc(monoid_identity.value(), semiring_elt_id.value());
  for (unsigned i = 0; i < size; ++i)
    c[i] = a.add_state();
  for (unsigned i = 0; i < size; ++i)
    if (i % 2)
      a.add_series_transition(c[i], c[(i+1) % size], s);
    else
      a.add_letter_transition(c[i], c[(i+1) % size], 'a');
  a.set_initial(c[0]);
  a.set_final(c[size - 1]);

  return a;
}

/// Create a aut_b automaton (for quotient).
/// See README_AUTOMATA for aut_b.
automaton_t aut_b()
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');

  automaton_t a = make_automaton(alpha);

  std::vector<hstate_t>	       c(2);

  c[0] = a.add_state();
  c[1] = a.add_state();

  a.set_initial(c[0]);
  a.set_final(c[1]);

  a.add_letter_transition(c[0], c[0], 'a');
  a.add_letter_transition(c[0], c[0], 'b');

  a.add_letter_transition(c[0], c[1], 'b');

  a.add_weighted_transition(c[1], c[1], 2, "a");
  a.add_weighted_transition(c[1], c[1], 2, "b");

  return a;
}


/// Create a aut_complete automaton
/// (spontaneous transition between any two states).
/// See README_AUTOMATA for aut_complete.
automaton_t aut_complete(int n)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t alpha;
  alpha.insert('a');

  automaton_t a = make_automaton(alpha);
  std::vector<hstate_t>	state_list;

  for (int i = 0; i < n; ++i)
    state_list.push_back(a.add_state());
  a.set_initial(a.get_state(0));
  a.set_final(a.get_state(0));

  for (std::vector<hstate_t>::iterator i = state_list.begin(); i != state_list.end(); ++i)
    for (std::vector<hstate_t>::iterator j = state_list.begin(); j != state_list.end(); ++j)
      a.add_spontaneous(*i, *j);

  return a;
}

#endif // ! VCSN_BENCH_COMMON_BENCH_CONSTRUCTS_HH
