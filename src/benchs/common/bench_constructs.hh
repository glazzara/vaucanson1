// bench_constructs.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

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
#ifndef VCSN_BENCHS_COMMON_BENCH_CONSTRUCTS_HH
# define VCSN_BENCHS_COMMON_BENCH_CONSTRUCTS_HH

/// Create a nice automaton which will have 2^n states once determinized.
void aut_2n(unsigned n, automaton_t& a)
{
  std::vector<hstate_t>	c(n);
  for (unsigned i = 0; i < n; ++i)
    c[i] = a.add_state();
  for (unsigned i = 0; i < n - 1; ++i)
    a.add_letter_edge(c[i], c[i+1], 'a');
  a.add_letter_edge(c[n-1], c[0], 'a');
  for (unsigned i = 1; i < n; ++i)
    {
      a.add_letter_edge(c[i], c[i], 'b');
      a.add_letter_edge(c[i], c[i], 'c');
      a.add_letter_edge(c[i], c[0], 'b');
    }
  a.set_initial(c[0]);
  a.set_final(c[0]);
}

void debruijn(unsigned n_value, automaton_t& an)
{
  unsigned n = 1 << n_value;

  for (unsigned i = 0; i < n; ++i)
    an.add_state();
  an.set_initial(0);
  for (unsigned i = 0; i < n; ++i)
  {
    an.add_letter_edge(i, (i*2)%n, 'a');
    an.add_letter_edge(i, (i*2+1)%n, 'b');
    if ((i << 1) & n)
      an.set_final(i);
  }
}

#endif // ! VCSN_BENCHS_COMMON_BENCH_CONSTRUCTS_HH
