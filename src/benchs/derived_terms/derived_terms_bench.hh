#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/derivatives_automaton.hh>
#include <vaucanson/algebra/implementation/series/krat.hh>
#include <vaucanson/algorithms/aut_to_exp.hh>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>

struct Data
{
    int n_len;
    double r_time_dt;
    double r_time_so;
    int n_dt_states;
    double r_time_quot_dt;
    double r_time_quot_so;
    int n_min_states;

    bool operator()(const Data& a, const Data& b) const
    {
      return a.n_len < b.n_len;
    }
};


void derived_terms_bench(int n_states)
{
  AUTOMATON_TYPES_EXACT(automaton_t);
  AUTOMATON_FREEMONOID_TYPES_EXACT(automaton_t);

  typedef std::vector<Data>  datas_t;
  RandomChooser chooser;
  datas_t	datas(1000);
  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  automaton_t a = new_automaton(alpha);
  aut_2n(n_states, a);

  // Get all data.
  for (int i = 0; i < 1000; ++i)
  {
    Data data;
    krat_t e = aut_to_exp(a, chooser);

    // Get derived terms automaton of e.
    data.n_len = e.value(). length();
    automaton_t dt = new_automaton(alpha);
    VCSN_BENCH_START_QUIET;
    derivatives_automaton(dt, e);
    VCSN_BENCH_STOP_QUIET(data.r_time_dt);
    data.n_dt_states = dt.states().size();

    // Get standart automaton of e.
    VCSN_BENCH_START_QUIET;
    automaton_t so = standard_of(e);
    VCSN_BENCH_STOP_QUIET(data.r_time_so);

    // Minimize dt.
    VCSN_BENCH_START_QUIET;
    data.n_min_states = quotient(dt).states().size();
    VCSN_BENCH_STOP_QUIET(data.r_time_quot_dt);

    // Minimize so.
    VCSN_BENCH_START_QUIET;
    quotient(so);
    VCSN_BENCH_STOP_QUIET(data.r_time_quot_so);
    datas[i] = data;
  }

  sort(datas.begin(), datas.end(), Data());

  // Summarize all data.
  datas_t::const_iterator idata = datas.begin();
  for (int i = 0; i < 20; ++i)
  {
    int n_len = 0;
    double r_time_dt = 0;
    double r_time_so = 0;
    int n_dt_states = 0;
    double r_time_quot_dt = 0;
    double r_time_quot_so = 0;
    int n_min_states = 0;

    for (int j = 0; j < 50; ++j)
    {
      n_len += idata->n_len;
      r_time_dt += idata->r_time_dt;
      r_time_so += idata->r_time_so;
      n_dt_states += idata->n_dt_states;
      r_time_quot_dt += idata->r_time_quot_dt;
      r_time_quot_so += idata->r_time_quot_so;
      n_min_states += idata->n_min_states;
      ++idata;
    }
    std::cerr << "Class " << i + 1 << std::endl
	      << "Average length: " << n_len / 50 << std::endl
	      << "Average dt time: " << r_time_dt / 50 << std::endl
	      << "Average so time: " << r_time_so / 50 << std::endl
	      << "Average dt states: " << n_dt_states / 50 << std::endl
	      << "Average quot time on dt: " << r_time_quot_dt / 50 << std::endl
	      << "Average quot time on so: " << r_time_quot_so / 50 << std::endl
	      << "Average min states: " << n_min_states / 50 << std::endl;
  }
}
