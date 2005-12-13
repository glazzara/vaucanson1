// is_normalized.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_IS_NORMALIZED_HH
# define VCSN_ALGORITHMS_IS_NORMALIZED_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   is_normalized.hh
 *
 * Test for transducer normalization.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Fri Jul  4 13:49:07 2003
 *
 * @see is_normalized_transducer()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Test the normalization of transducer.
   *
   * @param t The transducer to test.
   *
   * @return true if the transducer is normalized.
   */
  template<typename S, typename A>
  bool
  is_normalized_transducer(const Element<S, A>& t);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/is_normalized.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_IS_NORMALIZED_HH
