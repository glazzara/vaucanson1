// realtime.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_REALTIME_HH
# define ALGORITHMS_REALTIME_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*------------.
  | is_realtime |
  `------------*/
  template<typename A, typename T>
  bool
  is_realtime(const Element<A, T>& a);

  /*------------.
  | in_realtime |
  `------------*/
  template<typename A, typename T>
  void
  in_realtime(Element<A, T>& a);

  /*---------.
  | realtime |
  `---------*/
  template<typename A, typename T>
  Element<A, T>
  realtime(const Element<A, T>& a);
  
} // vcsn

# include <vaucanson/algorithms/realtime.hxx>

#endif // ALGORITHMS_REALTIME_HH

