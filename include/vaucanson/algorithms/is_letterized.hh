// is_letterized.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_IS_LETTERIZED_HH
# define VCSN_ALGORITHMS_IS_LETTERIZED_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   is_letterized.hh
 *
 * Letter-to-letter feature testing.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Fri Jul  4 13:42:52 2003
 *
 * @see is_letterized_transducer()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Test the letter to letter features.
   *
   * @param t The transducer to test.
   *
   * @return true if the transducer is letter to letter.
   */
  template<typename S, typename A>
  bool
  is_letterized_transducer(const Element<S, A>& t);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/is_letterized.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_IS_LETTERIZED_HH
