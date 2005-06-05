#ifndef BENCH_CONSTRUCTS_HH
# define BENCH_CONSTRUCTS_HH

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

void binary(automaton_t& an)
{
  std::vector<hstate_t>	c(2);

  c[0] = an.add_state();
  c[1] = an.add_state();

  an.set_initial(c[0]);
  an.set_final(c[1]);

  an.add_letter_edge(c[0], c[0], 'a');
  an.add_letter_edge(c[0], c[0], 'b');

  an.add_letter_edge(c[0], c[1], 'b');

  an.add_letter_edge(c[1], c[1], 'a');
  an.add_letter_edge(c[1], c[1], 'a');
  an.add_letter_edge(c[1], c[1], 'b');
  an.add_letter_edge(c[1], c[1], 'b');
}

#endif
