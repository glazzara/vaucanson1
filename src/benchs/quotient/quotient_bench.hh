#include <vaucanson/z_automaton.hh>
#include <vaucanson/algorithms/product.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::z_automaton;

#include <common/bench_constructs.hh>

void quotient_bench(int n_power)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t a = new_automaton(alpha);
  binary(a);
  automaton_t an = a;

  while (n_power--)
    a = product(a, an);

  VCSN_BENCH_START;
  quotient(a);
  VCSN_BENCH_STOP_AND_PRINT;
}
