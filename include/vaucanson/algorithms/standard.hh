// standard.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009, 2010 The Vaucanson Group.
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
 * This file contains different operations which can be applied on
 * standard automata.
 *
 * For Boolean automata, see ETA Chapter 1, Section 5.1.
 * For K-automata, see ETA Chapter 3, Section 2.
 * See also the correction of the exercice 2.24 p.540.
 * You can also find a page about standard automata at:
 * https://trac.lrde.org/vaucanson/wiki/StandardNormalizedAutomata
 *
 * @see standardize(), is_standard(), concat_of_standard(),
 *      sum_of_standard(), star_of_standard(), union_()
 */
/** @} */

// INTERFACE: void union_here(Automaton& a1, const Automaton& a2) { return vcsn::union_here(*a1, *a2); }
// INTERFACE: void union_here(GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::union_here(*a1, *a2); }

// INTERFACE: Automaton union_(const Automaton& a1, const Automaton& a2) { return vcsn::union_(*a1, *a2); }
// INTERFACE: GenAutomaton union_(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::union_(*a1, *a2); }

// INTERFACE: bool is_standard(const Automaton& a) { return vcsn::is_standard(*a); }
// INTERFACE: bool is_standard(const GenAutomaton& a) { return vcsn::is_standard(*a); }

// INTERFACE: void standardize(Automaton& a) { return vcsn::standardize(*a); }
// INTERFACE: void standardize(GenAutomaton& a) { return vcsn::standardize(*a); }

// INTERFACE: void sum_of_standard_here(Automaton& a1, const Automaton& a2) { return vcsn::sum_of_standard_here(*a1, *a2); }
// INTERFACE: void sum_of_standard_here(GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::sum_of_standard_here(*a1, *a2); }

// INTERFACE: Automaton sum_of_standard(const Automaton& a1, const Automaton& a2) { return vcsn::sum_of_standard(*a1, *a2); }
// INTERFACE: GenAutomaton sum_of_standard(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::sum_of_standard(*a1, *a2); }

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
   * In place union of two automata.
   *
   * This function adds states and transitions of a second automaton
   * to states and transitions of a first automaton.
   *
   * @param lhs  First automaton and destination of the union
   * @param rhs  Second automaton of the union
   *
   * @see union_()
   */
  template<typename A, typename AI1, typename AI2>
  void
  union_here(Element<A, AI1>& lhs, const Element<A, AI2>& rhs);

  /**
   * Union of two automata.
   *
   * This function returns the fresh union of two automata.  It puts
   * transitions and states of the two automata together, and create
   * a new one with the result.
   *
   * @param lhs  First automaton of the union
   * @param rhs  Second automaton of the union
   *
   * @note the name is @c union_ instead of @c union because the
   * latter is a reserved keyword.
   *
   * @see union_here()
   */
  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  union_(const Element<A, AI1>& lhs, const Element<A, AI2>& rhs);


  /**
   * Returns true iff the input automaton is standard.
   *
   * @param a The automaton to test
   *
   * @see standardize()
   */
  template<typename A, typename AI>
  bool
  is_standard(const Element<A, AI>& a);

  /**
   * Returns a standard automaton associated to the input.
   *
   * @param a The automaton to standardize
   *
   * @see is_standard()
   */
  template<typename A, typename AI>
  void
  standardize(Element<A, AI>& a);

  /**
   * In-place sum of two standard automata.
   *
   * This function makes the sum of two standard automata.
   * The result is a standard automaton.
   *
   * @param lhs The first automaton (it will contain the result)
   * @param rhs The second automaton
   *
   * @see standardize(), is_standard(), sum_of_standard()
   */
  template<typename A, typename AI1, typename AI2>
  void
  sum_of_standard_here(Element<A, AI1>& lhs,
		       const Element<A, AI2>& rhs);

  /**
   * Return a fresh sum of two standard automata.
   *
   * As @c sum_of_standard_here, this function build the sum of two
   * standard automata, but it builds a new one.
   *
   * @param lhs The first automaton
   * @param rhs The second automaton
   *
   * @see standardize(), is_standard(), sum_of_standard_here()
   */
  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  sum_of_standard(const Element<A, AI1>& lhs,
		  const Element<A, AI2>& rhs);

  /**
   * In-place concatenation of two standard automata.
   *
   * This function makes the concatenation of two standard
   * automata. The result is a standard automaton.
   *
   * @param lhs The first automaton (it will contain the result)
   * @param rhs The second automaton
   *
   * @see standardize(), is_standard(), concat_of_standard()
   */
  template<typename A, typename AI1, typename AI2>
  void
  concat_of_standard_here(Element<A, AI1>& lhs,
			  const Element<A, AI2>& rhs);

  /**
   * Return a fresh concatenation of two standard automata.
   *
   * As @c concat_of_standard_here, this function builds the union of
   * two automata, but it builds a new one.
   *
   * @param lhs The first automaton
   * @param rhs The second automaton
   *
   * @see standardize(), is_standard(), concat_of_standard_here()
   */
  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  concat_of_standard(const Element<A, AI1>& lhs,
		     const Element<A, AI2>& rhs);
  /**
   * In-place star transformation of a standard automaton.
   *
   * This function makes the star transformation of a standard
   * automaton, and replaces those given by the result.
   *
   * @param a The automaton to transform
   *
   * @see standardize(), is_standard(), star_of_standard()
   */
  template<typename A, typename AI>
  void
  star_of_standard_here(Element<A, AI>& a);

  /**
   * Return the fresh star transformation of a standard automata.
   *
   * As @c star_of_standard_here, this function applies star on an
   * automaton, but it builds a new automaton.
   *
   * @param a The automaton on which star must be applied.
   *
   * @see standardize(), is_standard(), star_of_standard_here()
   */
  template<typename A, typename AI>
  Element<A, AI>
  star_of_standard(const Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/standard.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_STANDARD_HH
