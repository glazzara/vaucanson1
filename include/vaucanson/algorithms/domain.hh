// domain.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_DOMAIN_HH
# define VCSN_ALGORITHMS_DOMAIN_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file domain.hh
 *
 * @brief Domain algorithm.
 *
 * @author Florent Terrones <florent.terrones@lrde.epita.fr>
 */
/** @} */

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algebra/implementation/free_monoid/words.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/series/series.hh>


#include <vaucanson/automata/concept/transducer.hh>


namespace vcsn
{
  /*-------.
  | Domain |
  `-------*/


  template <typename S, typename S2, typename T, typename T2>
  void
  domain(const Element<S,T>& src, Element<S2, T2>& dst);

  // FMP version of domain.
  template <typename src_t, typename dst_t>
  void
  do_fmp_domain(const src_t& src, dst_t& dst);

  // RW version of domain.
  template <typename src_t, typename dst_t>
  void
  do_rw_domain(const src_t& src, dst_t& dst);

} // End of namespace vcsn.


# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/domain.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_DOMAIN_HH
