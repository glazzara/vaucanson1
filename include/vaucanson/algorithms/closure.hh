// closure.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGORITHMS_CLOSURE_HH
# define ALGORITHMS_CLOSURE_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*-----------.
  | in_closure |
  `-----------*/
  // preconditions :
  //
  // note : this a particularily dummy closure. to be optimized.
  template<typename A, typename T>
  void
  in_closure(const Element<A, T>& a);

  template<typename A, typename T>
  Element<A, T>
  closure(const Element<A, T>& a);

} // vcsn

# include <vaucanson/algorithms/closure.hxx>

#endif // ALGORITHMS_CLOSURE_HH
