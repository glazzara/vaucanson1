// complete.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGORITHMS_COMPLETE_HH
# define ALGORITHMS_COMPLETE_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {
  
  template <typename A, typename T>
  void
  auto_in_complete(Element<A, T>&);

  template <typename A, typename T>
  Element<A, T>
  auto_complete(const Element<A, T>&);

} // vcsn

# include <vaucanson/algorithms/complete.hxx>

#endif // ALGORITHMS_COMPLETE_HH
