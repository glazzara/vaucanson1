// complementary.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGORITHMS_COMPLEMENTARY_HH
# define ALGORITHMS_COMPLEMENTARY_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*--------------.
  | Complementary |
  `--------------*/
  template <typename A, typename T>
  void
  auto_in_complementary(Element<A, T>&);

  template <typename A, typename T>
  Element<A, T>
  auto_complementary(const Element<A, T>&);

} // vcsn

# include <vaucanson/algorithms/complementary.hxx>

#endif // ALGO_PRODUCT_HH
