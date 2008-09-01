// realtime_decl.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_REALTIME_DECL_HH
# define VCSN_ALGORITHMS_REALTIME_DECL_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file  realtime_decl.hh
 *
 * Declaration of the realtime() function.
 *
 * Actually, the realtime() function may appear in two headers:
 * realtime.hh  and krat_exp_realtime.hh.  In both header files, this
 * function has the same prototype, but different meanings, and expect
 * to be called with different types.
 *
 * This is the unique declaration of realtime(), which will
 * then do the dispatch onto the right do_realtime() in function of
 * its parameter.
 *
 * *Please note that you should not include this file directly. Use
 * realtime.hh or krat_exp_realtime.hh*.
 *
 * @see realtime(), realtime.hh, krat_exp_realtime.hh
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Compute the realtime version of a rational expression or an automata.
   *
   * This function is a wrapper which selects the realtime function
   * either from realtime.hh or from krat_exp_realtime.hh.
   *
   * When called upon an automaton, this function uses the functions
   * declared in realtime.hh to make this automaton realtime using the
   * forward epsilon removal.
   *
   * When called with a rational expression, a function from
   * krat_exp_realtime.hh is selected to expand words in the
   * expression as a product of a letters.
   *
   * @see krat_exp_realtime.hh, realtime.hh
   */
  template<typename S, typename T>
  Element<S, T>
  realtime(const Element<S, T>& e);

  /**
   * Modify a rational expression or automata in place to make it realtime.
   *
   * This function is a wrapper thest selects the realtime() function
   * from either realtime.hh or from krat_exp_realtime.hh.
   *
   * It behaves exactly as realtime(), but do the operation in place.
   *
   * @see realtime()
   */
  template <typename S, typename T>
  void
  realtime_here(Element<S, T>& e);


  /**
   * Test whether an automaton or a rational expression is realtime.
   *
   * This function returns true if the input is realtime.
   *
   * An automaton over a free monoid @f$A^\star@f$ is realtime
   * if all its transitions are labeled by single letters of
   * @f$A@f$.  (Weights do not matter.)
   *
   * A rational expression is realtime if its litterals are
   * only single letters of @f$A@f$.  E.g. "ab.ab*" is not
   * rational while "a.b.(a.b)*" is.
   *
   * @param e The automaton or rational expression to test.
   *
   * @see realtime()
   */
  template <typename S, typename T>
  bool
  is_realtime(const Element<S, T>& e);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/realtime_decl.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_REALTIME_DECL_HH
