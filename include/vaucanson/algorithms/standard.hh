// standard.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_ALGORITHMS_STANDARD_HH
# define VCSN_ALGORITHMS_STANDARD_HH

/**
 * @file standard.hh
 * @brief Several algorithms concerning standard automata.
 *
 * This file contains different operations which can be applied on standard
 * automata.
 */

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Returns a standard automaton associated to the input.
   *
   * @param a The automaton to standardize
   * 
   * @see is_standard
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
   * @see standardize
   */
  template<typename A, typename T>
  bool
  is_standard(const Element<A, T>& a);

  /**
   * @brief In-place union of two standard automata.
   *
   * This function make the union of two standard automata. The result is a
   * standard automaton.
   *
   * @param lhs The first automaton (will contain the result)
   * @param rhs The second automaton
   *
   * @see standardize
   * @see is_standard
   * @see union_of_standard
   */
  template<typename A, typename T, typename U>
  void 
  union_of_standard_here(Element<A, T>& lhs, 
			 const Element<A, U>& rhs);

  /**
   * @brief Return a fresh union of two standard automata.
   *
   * As @c union_of_standard_here, this function build the union of two
   * automatons, but it builds a new one.
   *
   * @param lhs The first automaton
   * @param rhs The second automaton
   *
   * @see standardize
   * @see is_standard
   * @see union_of_standard_here
   */
  template<typename A, typename T, typename U>
  Element<A, T> 
  union_of_standard(const Element<A, T>& lhs, 
		    const Element<A, U>& rhs);

  /**
   * @brief In-place concatenation of two standard automata.
   * 
   * This function make the concatenation of two standard automata. The
   * result is a standard automaton.
   *
   * @param lhs The first automaton (will contain the result)
   * @param rhs The second automaton
   *
   * @see standardize
   * @see is_standard
   * @see concat_of_standard
   */
  template<typename A, typename T, typename U>
  void 
  concat_of_standard_here(Element<A, T>& lhs, 
			  const Element<A, U>& rhs);

  /**
   * @fresh Return a fresh concatenation of two standard automata.
   * 
   * As @c concat_of_standard_here, this function build the union of two
   * automatons, but it builds a new one.
   *
   * @param lhs The first automaton
   * @param rhs The second automaton
   *
   * @see standardize
   * @see is_standard
   * @see concat_of_standard_here
   */
  template<typename A, typename T, typename U>
  Element<A, T> 
  concat_of_standard(const Element<A, T>& lhs, 
		     const Element<A, U>& rhs);

  /**
   * @brief In-place star transformation of a standard automata.
   *
   * This function make the star transformation of a standard automaton,
   * and replace those given by the result.
   *
   * @param a The automaton to transform
   *
   * @see standardize
   * @see is_standard
   * @see star_of_standard
   */
  template<typename A, typename T>
  void 
  star_of_standard_here(Element<A, T>& a);

  /**
   * @brief Return the fresh star transformation of a standard automata.
   *
   * As @c star_of_standard_here, this function applies star on an automaton,
   * but it build a new automaton.
   *
   * @param a The automaton on which star must be applied.
   *
   * @see standardize
   * @see is_standard
   * @see star_of_standard_here
   */
  template<typename A, typename T>
  Element<A, T> 
  star_of_standard(const Element<A, T>& a);

  /** @} */
  
} // vcsn

# include <vaucanson/algorithms/standard.hxx>

#endif // VCSN_ALGORITHMS_STANDARD_HH
