// projections_fmp.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_PROJECTIONS_FMP_HH
# define VCSN_ALGORITHMS_PROJECTIONS_FMP_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file projections_fmp.hh
 *
 * @brief Domain and Image projection for transducers seen as automata
 * over a free monoid product.
 *
 * @author Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
 */
/** @} */

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algebra/implementation/free_monoid/words.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/series/series.hh>

namespace vcsn
{
  /*-------.
  | Domain |
  `-------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  domain(const Element<S,T>& aut, Element<S2, T2>& res);

  template <typename S, typename S2, typename T, typename T2>
  Element<S2, T2>
  domain(const Element<S,T>& aut);


  /*------.
  | Image |
  `------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  image(const Element<S,T>& aut, Element<S2, T2>& res);

  template <typename S, typename S2, typename T, typename T2>
  Element<S2, T2>
  image(const Element<S,T>& aut);


  /*---------.
  | Identity |
  `---------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  identity(const Element<S,T>& aut, Element<S2, T2>& res);

  template <typename S, typename S2, typename T, typename T2>
  Element<S2, T2>
  identity(const Element<S,T>& aut);

} // End of namespace vcsn.


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/projections_fmp.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_PROJECTIONS_FMP_HH
