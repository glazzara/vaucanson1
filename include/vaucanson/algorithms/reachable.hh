// reachable.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_REACHABLE_HH
# define ALGORITHMS_REACHABLE_HH

# include <set>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  template<typename A, typename T>
  std::set<hstate_t>
  start_reachable_states(const Element<A, T>& a);

  template<typename A, typename T>
  Element<A, T>
  auto_start_reachable(const Element<A, T>& a);

  template<typename A, typename T>
  void
  auto_in_start_reachable(Element<A, T>& a);
  
  template<typename A, typename T>
  std::set<hstate_t>
  final_reachable_states(const Element<A, T>& a);
 
  template<typename A, typename T>
  Element<A, T>
  auto_final_reachable(const Element<A, T>& a);

  template<typename A, typename T>
  void
  auto_in_final_reachable(Element<A, T>& a);
  
} // vcsn

# include <vaucanson/algorithms/reachable.hxx>

#endif // ALGORITHMS_REACHABLE_HH
