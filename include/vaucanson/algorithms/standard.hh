// standard.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_STANDARD_HH
# define ALGORITHMS_STANDARD_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*-------------.
  | standardize |
  `-------------*/
  template<typename A, typename T>
  void
  standardize(Element<A, T>& a);

  template<typename A, typename T>
  bool
  is_standard(const Element<A, T>& a);

  /*------.
  | Union |
  `------*/
  // precondition : lhs and rhs must be standard automaton.
  //
  //
  template<typename A, typename T, typename U>
  void 
  standard_auto_in_union(Element<A, T>& lhs, 
			   const Element<A, U>& rhs);

  template<typename A, typename T, typename U>
  Element<A, T> 
  standard_auto_union(const Element<A, T>& lhs, 
			const Element<A, U>& rhs);

  /*--------.
  | Concat  |
  `--------*/
  // precondition : lhs and rhs must be standard automaton
  //
  //
  template<typename A, typename T, typename U>
  void 
  standard_auto_in_concat(Element<A, T>& lhs, 
			  const Element<A, U>& rhs);

  template<typename A, typename T, typename U>
  Element<A, T> 
  standard_auto_concat(const Element<A, T>& lhs, 
		       const Element<A, U>& rhs);

  /*-----.
  | Star |
  `-----*/
  // precondition : a must be a standard automaton
  //
  //
  template<typename A, typename T>
  void 
  standard_auto_in_star(Element<A, T>& a);

  template<typename A, typename T>
  Element<A, T> 
  standard_auto_star(const Element<A, T>& a);

  
} // vcsn

# include <vaucanson/algorithms/standard.hxx>

#endif // ALGORITHMS_NORMALIZED_HH
