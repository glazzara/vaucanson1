// compute-test.hh
//
// $Id$
// VCSN_HEADER
#ifndef TESTS_COMPUTE_TEST_HH
# define TESTS_COMPUTE_TEST_HH

# include <check/tests_stuff.hh>

# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algorithms/compute.hh>

template <class S, class T>
void test_compute(tests::Tester& t)
{
  typedef	Element<S,T>				automaton_t;
  typedef typename TAutomata::states_t		        states_t;
  typedef typename TAutomata::state_iterator		state_iterator;
  typedef typename TAutomata::monoid_t::alphabet_t	alphabet_t;
  typedef typename alphabet_t::iterator		        alphabet_iterator;
  typedef typename TAutomata::states_t		        states_t;
  typedef typename TAutomata::state_iterator		state_iterator;
  typedef typename TAutomata::monoid_t::alphabets_elt_t alphabets_elt_t;

  TEST_MSG("Basic test on a well-known automaton.");
  
}


#endif // TESTS_COMPUTE_TEST_HH
