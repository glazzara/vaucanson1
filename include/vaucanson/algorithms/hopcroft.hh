// hopcroft.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGORITHMS_HOPCROFT_HH
# define ALGORITHMS_HOPCROFT_HH

# include <vaucanson/automata/automata_base.hh>

namespace vcsn {

  /*---------.
  | hopcroft |
  `---------*/
  template<typename A, typename T>
  algebra::Element<A, T>
  hopcroft_minimization_det(const algebra::Element<A, T>& a);

  template<typename A, typename T>
  algebra::Element<A, T>
  hopcroft_minimization_undet(const algebra::Element<A, T>& a);
  
} // vcsn

# include <vaucanson/algorithms/hopcroft.hxx>

#endif // ALGORITHMS_HOPCROFT_HH

