// elimination.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_ELIMINATION_HH
# define ALGORITHMS_ELIMINATION_HH

# include <vaucanson/automata/automata_base.hh>
# include <vaucanson/misc/selectors.hh>

namespace vcsn {

  /*------------.
  | elimination |
  `------------*/

  template<typename A, typename T>
  typename algebra::Element<A, T>::series_elt_t
  elimination(const algebra::Element<A, T>& a);

  template<typename A, typename T, typename Chooser_>
  typename algebra::Element<A, T>::series_elt_t
  elimination(const algebra::Element<A, T>& a, const Chooser_& c);
  

} // vcsn

# include <vaucanson/algorithms/elimination.hxx>

#endif // ALGORITHMS_ELIMINATION_HH
