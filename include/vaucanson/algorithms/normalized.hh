// normalized.hh
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

#ifndef VCSN_ALGORITHMS_NORMALIZED_HH
# define VCSN_ALGORITHMS_NORMALIZED_HH

/**
 * @file normalized.hh
 *
 * @brief Thompson normalization operations.
 *
 * This file contains algorithms related to thompson automata normalization, 
 * and thompson-normalized automata operations.
 *
 * @see normalize(), is_normalized(), union_of_normalized(),
 *      concatenate_of_normalized(), star_of_normalized()
 */

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /** @addtogroup algorithms */  /* @{ */

  /**
   * @brief Return the fresh thompson-normalized automaton.
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
   * @brief In-place normalize to the thompson form.
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
   * @brief Return true if the input automaton is thompson-normalized.
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
   * @brief Do the in-place union of two thompson-normalized automata.
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
   * @brief Return the fresh union of two thompson-normalized automata.
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
   * @brief Do the in-place concatenation of two thompson-normalized automata.
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
   * @brief Return the fresh concatenation of two thompson-normalized automata.
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
   * @brief Do in-place star transformation on the thompson-normalized input.
   *
   * This function performs the in-place star transformation of a
   * thompson-normalized automaton. The result is thompson-normalized.
   *
   * @param lhs An in/out parameter which is the automaton to transform as
   *        input, and the operation result as output.
   *
   * @see star_of_normalized(), concatenate_of_normalized(),
   *      union_of_normalized(), normalize(), is_normalized().
   */
  template<typename A, typename T>
  void 
  star_of_normalized_here(Element<A, T>& a);
  
  /**
   * @brief Return the fresh star transformation of its normalized input.
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

# include <vaucanson/algorithms/normalized.hxx>

#endif // VCSN_ALGORITHMS_NORMALIZED_HH
