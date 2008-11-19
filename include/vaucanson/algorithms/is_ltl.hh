// is_ltl.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_IS_LTL_HH
# define VCSN_ALGORITHMS_IS_LTL_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file is_ltl.hh
 *
 * @brief Letter-to-letter feature testing.
 *
 * @details An FMP transducer T over the free monoid product
 * @f$A^\star\times B^\star@f$ is letter-to-letter (LTL) if and only
 * if (1) the support of the of every of its transitions is in
 * @f$A^\times B@f$, and (2) its initial and final weights are scalar.
 *
 * @remarks Synonyms: ltl, letter-to-letter, lettre-à-lettre
 *
 * @see is_ltl(), is_sub_normalized(), is_normalized()
 */
/** @} */

// INTERFACE: bool is_ltl(const Automaton& a) { return vcsn::is_ltl(*a); }

// The algorithm take any Element as argument. Static checks
// (static_assertion_) will be done at compile time to ensure the Element has
// proper interface.
# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn
{
  /** @addtogroup algorithms *//** @{ */
  /**
   * @brief Test whether an FMP transducer is letter-to-letter.
   *
   * @pre t must be an FMP transducer.
   *
   * @param t The FMP transducer to test.
   *
   * @return true if the FMP transducer is letter-to-letter.
   */
  template<typename S, typename A>
  bool
  is_ltl(const Element<S, A>& t);
  /** @} */

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/is_ltl.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_IS_LTL_HH
