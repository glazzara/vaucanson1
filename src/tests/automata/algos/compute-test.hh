// compute-test.hh
//
// $Id$
// VCSN_HEADER
#ifndef TESTS_COMPUTE_TEST_HH
# define TESTS_COMPUTE_TEST_HH

# include <check/tests_stuff.hh>

# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algorithms/compute.hh>

template <class Auto>
void test_compute(tests::Tester& t)
{
  typedef Auto  				        automaton_t;
  typedef typename Auto::states_t		        states_t;
  typedef typename Auto::state_iterator		        state_iterator;
  typedef typename Auto::monoid_t::alphabet_t	        alphabet_t;
  typedef typename alphabet_t::iterator		        alphabet_iterator;
  typedef typename Auto::states_t		        states_t;
  typedef typename Auto::state_iterator		        state_iterator;
  typedef typename Auto::monoid_t::alphabets_elt_t      alphabets_elt_t;

  TEST_MSG("Basic test on a well-known automaton.");
  
}


#endif // TESTS_COMPUTE_TEST_HH
