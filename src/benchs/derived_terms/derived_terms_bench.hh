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

#define CLASSES 20
#define SAMPLES_PER_CLASS 50
#define SAMPLES (CLASSES * SAMPLES_PER_CLASS)

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
    int n_dt_edges;
    int n_so_edges;
    double r_time_quot_dt;
    double r_time_quot_so;
    int n_min_states;
    int n_min_edges;

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
  datas_t	datas(SAMPLES);
  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  automaton_t a = new_automaton(alpha);
  aut_2n(n_states, a);

  // Get all data.
  for (int i = 0; i < SAMPLES; ++i)
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
    data.n_dt_edges = dt.edges().size();

    // Get standart automaton of e.
    VCSN_BENCH_START_QUIET;
    automaton_t so = standard_of(e);
    VCSN_BENCH_STOP_QUIET(data.r_time_so);
    data.n_so_edges = so.edges().size();

    // Minimize dt.
    VCSN_BENCH_START_QUIET;
    automaton_t q = quotient(dt);
    VCSN_BENCH_STOP_QUIET(data.r_time_quot_dt);
    data.n_min_states = q.states().size();
    data.n_min_edges = q.edges().size();

    // Minimize so.
    VCSN_BENCH_START_QUIET;
    quotient(so);
    VCSN_BENCH_STOP_QUIET(data.r_time_quot_so);
    datas[i] = data;
  }

  sort(datas.begin(), datas.end(), Data());

  // Summarize all data.
  datas_t::const_iterator idata = datas.begin();
  for (int i = 0; i < CLASSES; ++i)
  {
    int n_len = 0;
    double r_time_dt = 0;
    double r_time_so = 0;
    int n_dt_states = 0;
    double r_time_quot_dt = 0;
    double r_time_quot_so = 0;
    int n_min_states = 0;
    int n_dt_edges = 0;
    int n_so_edges = 0;
    int n_min_edges = 0;

    for (int j = 0; j < SAMPLES_PER_CLASS; ++j)
    {
      n_len += idata->n_len;
      r_time_dt += idata->r_time_dt;
      r_time_so += idata->r_time_so;
      n_dt_states += idata->n_dt_states;
      n_dt_edges += idata->n_dt_edges;
      r_time_quot_dt += idata->r_time_quot_dt;
      r_time_quot_so += idata->r_time_quot_so;
      n_min_states += idata->n_min_states;
      n_min_edges += idata->n_min_edges;
      ++idata;
    }
    n_len /= SAMPLES_PER_CLASS;
    r_time_dt /= SAMPLES_PER_CLASS;
    r_time_so /= SAMPLES_PER_CLASS;
    n_dt_states /= SAMPLES_PER_CLASS;
    r_time_quot_dt /= SAMPLES_PER_CLASS;
    r_time_quot_so /= SAMPLES_PER_CLASS;
    n_min_states /= SAMPLES_PER_CLASS;
    n_dt_edges /= SAMPLES_PER_CLASS;
    n_so_edges /= SAMPLES_PER_CLASS;
    n_min_edges /= SAMPLES_PER_CLASS;
    std::cerr << "Class " << i + 1 << std::endl
	      << "Average length: " << n_len << std::endl
	      << "Average dt time: " << r_time_dt << std::endl
	      << "Average so time: " << r_time_so << std::endl
	      << "Average dt states: " << n_dt_states << std::endl
	      << "Average dt edges: " << n_dt_edges << std::endl
	      << "Average so edges: " << n_so_edges << std::endl
	      << "Average quot time on dt: " << r_time_quot_dt << std::endl
	      << "Average quot time on so: " << r_time_quot_so << std::endl
	      << "Average min states: " << n_min_states << std::endl
	      << "Average min edges: " << n_min_edges << std::endl;
  }
}
