// determinize.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_DETERMINIZE_HH
# define ALGORITHMS_DETERMINIZE_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/fundamental/fundamental.hh>

namespace vcsn {

  /*------------.
  | determinize |
  `------------*/
  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a);

  template<typename A, typename T>
  Element<A, T>
  subset_construction(const Element<A, T>& a);
  
} // vcsn

# include <vaucanson/algorithms/determinize.hxx>

#endif // ALGORITHMS_DETERMINIZE_HH

