// normalized.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_NORMALIZED_HH
# define ALGORITHMS_NORMALIZED_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*-----------.
  | normalized |
  `-----------*/
  template<typename A, typename T>
  void
  normalize(Element<A, T>& a);

  template<typename A, typename T>
  bool
  is_normalized(const Element<A, T>& a);

  /*------.
  | Union |
  `------*/
  // precondition : lhs and rhs must be normalized automaton.
  //
  //
  template<typename A, typename T, typename U>
  void 
  normalized_auto_in_union(Element<A, T>& lhs, 
			   const Element<A, U>& rhs);

  template<typename A, typename T, typename U>
  Element<A, T> 
  normalized_auto_union(const Element<A, T>& lhs, 
			const Element<A, U>& rhs);

  /*--------.
  | Concat |
  `--------*/
  // precondition : lhs and rhs must be normalized automaton
  //
  //
  template<typename A, typename T, typename U>
  void 
  normalized_auto_in_concat(Element<A, T>& lhs, 
			     const Element<A, U>& rhs);

  template<typename A, typename T, typename U>
  Element<A, T> 
  normalized_auto_concat(const Element<A, T>& lhs, 
			  const Element<A, U>& rhs);

  /*-----.
  | Star |
  `-----*/
  // precondition : a must be a normalized automaton
  //
  //
  template<typename A, typename T>
  void 
  normalized_auto_in_star(Element<A, T>& a);

  template<typename A, typename T>
  Element<A, T> 
  normalized_auto_star(const Element<A, T>& a);

  
} // vcsn

# include <vaucanson/algorithms/normalized.hxx>

#endif // ALGORITHMS_NORMALIZED_HH
