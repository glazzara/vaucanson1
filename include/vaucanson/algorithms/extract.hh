// extract.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_EXTRACT_HH
# define ALGORITHMS_EXTRACT_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*----------------------------------------.
  | SubAutomaton defined by a set of states |
  `----------------------------------------*/
 
  template<typename A, typename T, typename StatesSet>
  Element<A, T> 
  auto_extract(const Element<A, T>& a, const StatesSet& s, bool check_states = true);

  template<typename A, typename T, typename StatesSet>
  void auto_in_extract(Element<A, T>& a, const StatesSet& s, bool check_states = true);

} // vcsn

# include <vaucanson/algorithms/extract.hxx>

#endif // ALGO_EXTRACT_HH
