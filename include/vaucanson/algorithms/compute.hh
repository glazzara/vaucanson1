// compute.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_COMPUTE_HH
# define ALGORITHMS_COMPUTE_HH

# include <vaucanson/fundamental/element.hh>

namespace vcsn {

  /*--------.
  | compute |
  `--------*/
  // precondition : the automaton is realtime
  //
  //
  template<typename A, typename T, typename W>
  typename Element<A, T>::series_elt_t
  compute(const Element<A, T>& a, const W& word);

} // vcsn

# include <vaucanson/algorithms/compute.hxx>

#endif // ALGORITHMS_COMPUTE_HH
