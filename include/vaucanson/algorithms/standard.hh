// standard.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_STANDARD_HH
# define VCSN_ALGORITHMS_STANDARD_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file standard.hh
 *
 * Several algorithms concerning standard automata.
 *
 * This  file contains different  operations which  can be  applied on
 * standard automata.
 *
 * @see standardize(), is_standard(), concat_of_standard(),
 *      union_of_standard(), star_of_standard()
 */
/** @} */

// INTERFACE: void standardize(Automaton& a) { return vcsn::standardize(*a); }
// INTERFACE: void standardize(GenAutomaton& a) { return vcsn::standardize(*a); }

// INTERFACE: bool is_standard(Automaton& a) { return vcsn::is_standard(*a); }
// INTERFACE: bool is_standard(GenAutomaton& a) { return vcsn::is_standard(*a); }

// INTERFACE: void union_of_standard_here(Automaton& a1, const Automaton& a2) { return vcsn::union_of_standard_here(*a1, *a2); }
// INTERFACE: void union_of_standard_here(GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::union_of_standard_here(*a1, *a2); }

// INTERFACE: Automaton union_of_standard(const Automaton& a1, const Automaton& a2) { return vcsn::union_of_standard(*a1, *a2); }
// INTERFACE: GenAutomaton union_of_standard(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::union_of_standard(*a1, *a2); }

// INTERFACE: void concat_of_standard_here(Automaton& a1, const Automaton& a2) { return vcsn::concat_of_standard_here(*a1, *a2); }
// INTERFACE: void concat_of_standard_here(GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::concat_of_standard_here(*a1, *a2); }

// INTERFACE: Automaton concat_of_standard(const Automaton& a1, const Automaton& a2) { return vcsn::concat_of_standard(*a1, *a2); }
// INTERFACE: GenAutomaton concat_of_standard(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::concat_of_standard(*a1, *a2); }

// INTERFACE: void star_of_standard_here(Automaton& a) { return vcsn::star_of_standard_here(*a); }
// INTERFACE: void star_of_standard_here(GenAutomaton& a) { return vcsn::star_of_standard_here(*a); }

// INTERFACE: Automaton star_of_standard(const Automaton& a) { return vcsn::star_of_standard(*a); }
// INTERFACE: GenAutomaton star_of_standard(const GenAutomaton& a) { return vcsn::star_of_standard(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Returns a standard automaton associated to the input.
   *
   * @param a The automaton to standardize
   *
   * @see is_standard()
   *
   * @bug Not implemented yed
   */
  template<typename A, typename T>
  void
  standardize(Element<A, T>& a);

  /**
   * Returns true if the input automaton is standard.
   *
   * @param a The automaton to test
   *
   * @see standardize()
   */
  template<typename A, typename T>
  bool
  is_standard(const Element<A, T>& a);

  /**
   * In-place union of two standard automata.
   *
   * This function make the union of two standard automata. The result is a
   * standard automaton.
   *
   * @param lhs The first automaton (will contain the result)
   * @param rhs The second automaton
   *
   * @see standardize(), is_standard(), union_of_standard()
   */
  template<typename A, typename T, typename U>
  void
  union_of_standard_here(Element<A, T>& lhs,
			 const Element<A, U>& rhs);

  /**
   * Return a fresh union of two standard automata.
   *
   * As @c union_of_standard_here, this function build the union of two
   * automatons, but it builds a new one.
   *
   * @param lhs The first automaton
   * @param rhs The second automaton
   *
   * @see standardize(), is_standard(), union_of_standard_here()
   */
  template<typename A, typename T, typename U>
  Element<A, T>
  union_of_standard(const Element<A, T>& lhs,
		    const Element<A, U>& rhs);

  /**
   * In-place concatenation of two standard automata.
   *
   * This function make the concatenation of two standard automata. The
   * result is a standard automaton.
   *
   * @param lhs The first automaton (will contain the result)
   * @param rhs The second automaton
   *
   * @see standardize(), is_standard(), concat_of_standard()
   */
  template<typename A, typename T, typename U>
  void
  concat_of_standard_here(Element<A, T>& lhs,
			  const Element<A, U>& rhs);

  /**
   * Return a fresh concatenation of two standard automata.
   *
   * As @c concat_of_standard_here, this function build the union of two
   * automatons, but it builds a new one.
   *
   * @param lhs The first automaton
   * @param rhs The second automaton
   *
   * @see standardize(), is_standard(), concat_of_standard_here()
   */
  template<typename A, typename T, typename U>
  Element<A, T>
  concat_of_standard(const Element<A, T>& lhs,
		     const Element<A, U>& rhs);

  /**
   * In-place star transformation of a standard automata.
   *
   * This function make the star transformation of a standard automaton,
   * and replace those given by the result.
   *
   * @param a The automaton to transform
   *
   * @see standardize(), is_standard(), star_of_standard()
   */
  template<typename A, typename T>
  void
  star_of_standard_here(Element<A, T>& a);

  /**
   * Return the fresh star transformation of a standard automata.
   *
   * As @c star_of_standard_here, this function applies star on an automaton,
   * but it build a new automaton.
   *
   * @param a The automaton on which star must be applied.
   *
   * @see standardize(), is_standard(), star_of_standard_here()
   */
  template<typename A, typename T>
  Element<A, T>
  star_of_standard(const Element<A, T>& a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/standard.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_STANDARD_HH
