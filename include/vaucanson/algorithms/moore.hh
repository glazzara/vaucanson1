// moore.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGORITHMS_MOORE_HH
# define ALGORITHMS_MOORE_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*------.
  | moore |
  `------*/
  template<typename A, typename T>
  Element<A, T>
  moore_minimization(const Element<A, T>& a);
  
} // vcsn

# include <vaucanson/algorithms/moore.hxx>

#endif // ALGORITHMS_MOORE_HH

