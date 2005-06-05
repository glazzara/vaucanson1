#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algorithms/aut_to_exp.hh>
#include <vaucanson/algorithms/standard_of.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>
#include <common/algorithm.hh>

void minimization_nd_bench(int n_states)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  double r_delay;
  double r_avr = 0;
  double r_best_avr = -1000;

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t avr = new_automaton(alpha);
  automaton_t a = new_automaton(alpha);
  aut_2n(n_states, a);

  for (int i = 0; i < 10; ++i)
  {
    std::cerr << "Iteration " << i << std::endl;
    automaton_t nd = standard_of(aut_to_exp(a, RandomChooser()));
    VCSN_BENCH_START_QUIET;
    quotient(nd);
    VCSN_BENCH_STOP_QUIET(r_delay);
    r_avr = (r_avr * i + r_delay) / (i + 1);
    if (fabs(r_avr - r_delay) < fabs(r_avr - r_best_avr))
    {
      avr = nd;
      r_best_avr = r_delay;
    }
  }

  std::ofstream tmp_o_file("init_o_tmp.fsm");
  fsm_dump(tmp_o_file, avr);
  tmp_o_file.close();

  std::cerr << "minimization_nb_bench: " << r_best_avr << std::endl;
}
