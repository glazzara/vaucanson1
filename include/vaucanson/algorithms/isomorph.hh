// isomorph.hh
//
// $Id$
// VCSN_HEADER


#ifndef ALGO_ISOMORPH_HH
# define ALGO_ISOMORPH_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/fundamental/fundamental.hh>

namespace vcsn {

  /*----------.
  | isomorph |
  `----------*/
  template<typename A, typename T>
  bool
  is_isomorph(const Element<A, T>& a, const Element<A, T>& b);
  

} // vcsn

# include <vaucanson/algorithms/isomorph.hxx>

#endif // ALGO_ISOMORPH_HH
