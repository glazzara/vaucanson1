// hopcroft.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGORITHMS_HOPCROFT_HH
# define ALGORITHMS_HOPCROFT_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*---------.
  | hopcroft |
  `---------*/
  template<typename A, typename T>
  Element<A, T>
  hopcroft_minimization_det(const Element<A, T>& a);

  template<typename A, typename T>
  Element<A, T>
  hopcroft_minimization_undet(const Element<A, T>& a);
  
} // vcsn

# include <vaucanson/algorithms/hopcroft.hxx>

#endif // ALGORITHMS_HOPCROFT_HH

