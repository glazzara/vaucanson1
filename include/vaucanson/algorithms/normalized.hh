// normalized.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_NORMALIZED_HH
# define VCSN_ALGORITHMS_NORMALIZED_HH

/** @addtogroup algorithms *//* @{ */
/**
 * @file normalized.hh
 *
 * @brief Thompson normalization operations.
 *
 * Algorithms related to Thompson automata normalization,
 * and Thompson-normalized automata operations.
 *
 * @see normalize(), is_normalized(), union_of_normalized(),
 *      concatenate_of_normalized(), star_of_normalized()
 */
/** @} */

// INTERFACE: Automaton normalize(const Automaton& a) { return vcsn::normalize(*a); }
// INTERFACE: GenAutomaton normalize(const GenAutomaton& a) { return vcsn::normalize(*a); }

// INTERFACE: void normalize_here(Automaton& a) { return vcsn::normalize_here(*a); }
// INTERFACE: void normalize_here(GenAutomaton& a) { return vcsn::normalize_here(*a); }

// INTERFACE: bool is_normalized(const Automaton& a) { return vcsn::is_normalized(*a); }
// INTERFACE: bool is_normalized(const GenAutomaton& a) { return vcsn::is_normalized(*a); }

// INTERFACE: void union_of_normalized_here(Automaton& a1, const Automaton& a2) { return vcsn::union_of_normalized_here(*a1, *a2); }
// INTERFACE: void union_of_normalized_here(GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::union_of_normalized_here(*a1, *a2); }

// INTERFACE: Automaton union_of_normalized(const Automaton& a1, const Automaton& a2) { return vcsn::union_of_normalized(*a1, *a2); }
// INTERFACE: GenAutomaton union_of_normalized(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::union_of_normalized(*a1, *a2); }

// INTERFACE: void concatenate_of_normalized_here(Automaton& a1, const Automaton& a2) { return vcsn::concatenate_of_normalized_here(*a1, *a2); }
// INTERFACE: void concatenate_of_normalized_here(GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::concatenate_of_normalized_here(*a1, *a2); }

// INTERFACE: Automaton concatenate_of_normalized(const Automaton& a1, const Automaton& a2) { return vcsn::concatenate_of_normalized(*a1, *a2); }
// INTERFACE: GenAutomaton concatenate_of_normalized(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::concatenate_of_normalized(*a1, *a2); }

// INTERFACE: void star_of_normalized_here(Automaton& a) { return vcsn::star_of_normalized_here(*a); }
// INTERFACE: void star_of_normalized_here(GenAutomaton& a) { return vcsn::star_of_normalized_here(*a); }

// INTERFACE: Automaton star_of_normalized(const Automaton& a) { return vcsn::star_of_normalized(*a); }
// INTERFACE: GenAutomaton star_of_normalized(const GenAutomaton& a) { return vcsn::star_of_normalized(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//* @{ */

  /**
   * Return the fresh thompson-normalized automaton.
   *
   * This function returns the thompson-normalized automaton corresponding
   * to its input.
   *
   * @param a The automaton to normalize.
   *
   * @see normalize_here(), is_normalized(), union_of_normalized(),
   *      concatenate_of_normalized(), star_of_normalized().
   */
  template <typename A, typename T>
  Element<A, T>
  normalize(const Element<A, T>& a);

  /**
   * In-place normalize to the thompson form.
   *
   * This function performs the in-place thompson-normalization of its input.
   *
   * @param a An in/out parameter containing the automaton to normalize as
   *          input, and the normalized automaton as output.
   *
   * @see normalize, is_normalized(), union_of_normalized(),
   *      concatenate_of_normalized(), star_of_normalized().
   */
  template<typename A, typename T>
  void
  normalize_here(Element<A, T>& a);

  /**
   * Return true if the input automaton is thompson-normalized.
   *
   * This function indicates whether its input automaton is
   * thompson-normalized or not.
   *
   * @param a The automaton to test.
   *
   * @see normalize(), union_of_normalized(), concatenate_of_normalized(),
   *      star_of_normalized().
   */
  template<typename A, typename T>
  bool
  is_normalized(const Element<A, T>& a);

  /**
   * Do the in-place union of two thompson-normalized automata.
   *
   * This function performs the in-place union of two
   * thompson-normalized automata. The result is thompson-normalized.
   *
   * @param lhs An in/out parameter which is the left hand side of the union
   *            as input, and the operation result as output.
   * @param rhs Right hand side of the union.
   *
   * @see union_of_normalized(), concatenate_of_normalized(),
   *      star_of_normalized(), normalize(), is_normalized().
   */
  template<typename A, typename T, typename U>
  void
  union_of_normalized_here(Element<A, T>& lhs,
			   const Element<A, U>& rhs);

  /**
   * Return the fresh union of two thompson-normalized automata.
   *
   * This function returns a fresh automaton which is the union of
   * input automata. It is thompson-normalized.
   *
   * @param lhs Left hand side of the union.
   * @param rhs Right hand side of the union.
   *
   * @see union_of_normalized_here(), concatenate_of_normalized(),
   *      star_of_normalized(), normalize(), is_normalized().
   */
  template<typename A, typename T, typename U>
  Element<A, T>
  union_of_normalized(const Element<A, T>& lhs,
		      const Element<A, U>& rhs);

  /**
   * Do the in-place concatenation of two thompson-normalized automata.
   *
   * This function performs the in-place concatenation of two
   * thompson-normalized automata. The result is thompson-normalized.
   *
   * @param lhs An in/out parameter which is the left hand side of the
   *            concatenation as input, and the operation result as output.
   * @param rhs Right hand side of the concatenation.
   *
   * @see concatenate_of_normalized(), union_of_normalized(),
   *      star_of_normalized(), normalize(), is_normalized().
   */
  template<typename A, typename T, typename U>
  void
  concatenate_of_normalized_here(Element<A, T>& lhs,
				 const Element<A, U>& rhs);

  /**
   * Return the fresh concatenation of two thompson-normalized automata.
   *
   * This function returns a fresh automaton which is the concatenation of
   * input automata. It is thompson-normalized.
   *
   * @param lhs Left hand side of the concatenation.
   * @param rhs Right hand side of the concatenation.
   *
   * @see concatenate_of_normalized_here(), union_of_normalized(),
   *      star_of_normalized(), normalize, is_normalized().
   */
  template<typename A, typename T, typename U>
  Element<A, T>
  concatenate_of_normalized(const Element<A, T>& lhs,
			    const Element<A, U>& rhs);

  /**
   * Do in-place star transformation on the thompson-normalized input.
   *
   * This function performs the in-place star transformation of a
   * thompson-normalized automaton. The result is thompson-normalized.
   *
   * @param a An in/out parameter which is the automaton to transform as
   *        input, and the operation result as output.
   *
   * @see star_of_normalized(), concatenate_of_normalized(),
   *      union_of_normalized(), normalize(), is_normalized().
   */
  template<typename A, typename T>
  void
  star_of_normalized_here(Element<A, T>& a);

  /**
   * Return the fresh star transformation of its normalized input.
   *
   * This function performs a star transformation on its input, and returns
   * it as a fresh automaton. The input must be thompson-normalized, and
   * the result is thompson-normalized.
   *
   * @param a The automaton to run star transformation on.
   *
   * @see star_of_normalized_here(), concatenate_of_normalized(),
   *      union_of_normalized(), normalize(), is_normalized().
   */
  template<typename A, typename T>
  Element<A, T>
  star_of_normalized(const Element<A, T>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/normalized.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_NORMALIZED_HH
