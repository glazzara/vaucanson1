// product.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGORITHMS_PRODUCT_HH
# define ALGORITHMS_PRODUCT_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*--------.
  | product |
  `--------*/ 
  template<typename A, typename T, typename U>
  Element<A, T> 
  auto_product(const Element<A, T>& lhs, const Element<A, U>& rhs);

  /*---------.
  | diagonal |
  `---------*/
  template <typename A, typename T>
  void
  auto_in_diagonal(Element<A, T>&);

  template <typename A, typename T>
  Element<A, T>
  auto_diagonal(const Element<A, T>&);

} // vcsn

# include <vaucanson/algorithms/product.hxx>

#endif // ALGO_PRODUCT_HH
