// product.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGORITHMS_PRODUCT_HH
# define ALGORITHMS_PRODUCT_HH

# include <vaucanson/automata/automata_base.hh>

namespace vcsn {

  /*--------.
  | product |
  `--------*/ 
  template<typename A, typename T, typename U>
  algebra::Element<A, T> 
  auto_product(const algebra::Element<A, T>& lhs, const algebra::Element<A, U>& rhs);

  /*---------.
  | diagonal |
  `---------*/
  template <typename A, typename T>
  void
  auto_in_diagonal(algebra::Element<A, T>&);

  template <typename A, typename T>
  algebra::Element<A, T>
  auto_diagonal(const algebra::Element<A, T>&);

} // vcsn

# include <vaucanson/algorithms/product.hxx>

#endif // ALGO_PRODUCT_HH
