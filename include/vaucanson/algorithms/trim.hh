// trim.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGORITHMS_TRIM_HH
# define ALGORITHMS_TRIM_HH

# include <set>

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  template<typename A, typename T>
  std::set<hstate_t>
  useful_states(const Element<A, T>& a);

  template<typename A, typename T>
  Element<A, T>
  trim(const Element<A, T>& a);
    
} // vcsn

# include <vaucanson/algorithms/trim.hxx>

#endif // ALGORITHMS_TRIM_HH
