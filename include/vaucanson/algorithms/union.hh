/***********************************
 * <vaucanson/algorithms/union.hh> *
 ***********************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef ALGORITHMS_UNION_HH
# define ALGORITHMS_UNION_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*------.
  | union |
  `------*/

  template<typename A, typename T, typename U>
  void 
  auto_in_union(Element<A, T>& lhs, 
		const Element<A, U>& rhs);

  template<typename A, typename T, typename U>
  Element<A, T> 
  auto_union(const Element<A, T>& lhs, 
	     const Element<A, U>& rhs);

} // vcsn

# include <vaucanson/algorithms/union.hxx>

#endif // ALGO_UNION_HH
