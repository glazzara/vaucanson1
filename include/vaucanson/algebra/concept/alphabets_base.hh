// alphabets_base.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGEBRA_ALPHABETS_BASE_HH
# define VCSN_ALGEBRA_ALPHABETS_BASE_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/misc/container_ops.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup alphabet *//** @{ */

    /*----------------------.
    | AlphabetSetBase<Self> |
    `----------------------*/

    /**
     * @brief Base class for structural elements of alphabets.
     *
     * This class is empty and should be used for typing purposes only.
     *
     * Note that implementation types for alphabets should provide:
     * <ul>
     * <li> @c op_choose(AlphabetSet, T), which creates a random alphabet.
     * <li> @c op_eq(AlphabetSet, T), which tests for equality between alphabets.
     * </ul>
     */
    template<class S>
    struct AlphabetSetBase 
      : Structure<S>
    {
    protected:

      /** @{ */
      /// Protected constructor.
      AlphabetSetBase();
      AlphabetSetBase(const AlphabetSetBase& other);
      /** @} */
    };

    /*----------------.
    | alphabet_traits |
    `----------------*/

    /** 
     * @brief Trait for virtual types of structural elements for alphabets.
     *
     * This trait contains a definition of @c letter_t, the type of
     * any letter in an alphabet. It should be specialized for all
     * derivated structures.
     */
    template<typename S, typename T>
    struct alphabet_traits 
    {
      /// The type of letters in any alphabet.
typedef undefined_type	letter_t;

      /// Whether an alphabet contains dynamic data.
static const bool dynamic_data = false;
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup alphabet *//** @{ */
 

  /*---------------.
  | dynamic_traits |
  `---------------*/
  
  /// Specialization of @c dynamic_traits for @c AlphabetSetBase.
  template<typename S>
  struct dynamic_traits<algebra::AlphabetSetBase<S> > 
    : dynamic_traits<Structure<S> >
  { };
  
  
  /*--------------------------------------.
  | MetaElement<AlphabetSetBase<Self>, T> |
  `--------------------------------------*/

  /**
   * @brief Specialization of @c MetaElement for @c AlphabetSetBase.
   * 
   * This class defines services shared by all alphabets.
   */
  template<class S, typename T>
  struct MetaElement<algebra::AlphabetSetBase<S>, T>
    : MetaElement<Structure<S>, T>
  {
    
    /// The type of letters in the alphabet.
typedef typename algebra::alphabet_traits<S, T>::letter_t letter_t;
    
    /// The type of the letter iterator for constant alphabets.
    typedef typename op_begin_traits<S, T>::const_ret_t	const_iterator;
    
    /// The type of the letter iterator for mutable alphabets.
    typedef typename op_begin_traits<S, T>::ret_t iterator;

    /// Add a letter to the alphabet.
    void insert(const letter_t& l);

    /// Randomly choose a letter in the alphabet.
    letter_t choose() const;

    /// Retrieve the number of letters in the alphabet.
    size_t size()                      const;

    /// Test for matching letters modulo the alphabet meta-symbols.
    bool letter_equality(letter_t, letter_t) const;

    /// Tell whether the alphabet contains a specified letter.
    bool contains(const letter_t& l) const;

    /// Tell whether the alphabet contains a finite number of letters.
    bool is_finite() const;

    /** @{ */
    /// Retrieve a begin iterator.
    iterator begin();
    const_iterator begin() const;
    /** @} */

    /** @{ */
    /// Retrieve an end iterator.
    iterator end();
    const_iterator end() const;
    /** @} */

  protected:
    /** @{ */
    /// Protected constructors.
    MetaElement();
    MetaElement(const MetaElement& other);
  };

  /// Implementation of generic stream output operator for alphabets.
  template<typename S, typename St, typename T>
  St& op_rout(const algebra::AlphabetSetBase<S>& s, St& st, const T& a);
 
  /// Implementation of generic letter equality modulo meta-characters.
  template <typename S, typename T, typename L>
  bool op_letter_equality(const algebra::AlphabetSetBase<S>& s, 
			  const T& a, 
			  L lhs,
			  L rhs);

  /** @} */
  /** @} */

} // vcsn

# include <vaucanson/algebra/concept/alphabets_base.hxx>

#endif // VCSN_ALGEBRA_ALPHABETS_BASE_HH
