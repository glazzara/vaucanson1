// alphabets_base.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The
// Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_ALPHABETS_BASE_HH
# define VCSN_ALGEBRA_CONCEPT_ALPHABETS_BASE_HH

/**
 * @file   alphabets_base.hh
 * @brief  Definition of the alphabet concept.
 */

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/misc/container_ops.hh>
# include <vaucanson/algebra/concept/letter.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup alphabet *//** @{ */

    /*----------------------.
    | AlphabetSetBase<Self> |
    `----------------------*/

    /**
     * Base class for structural elements of alphabets.
     *
     * This class is empty and should be used for typing purposes only.
     *
     * Note that implementation types for alphabets should provide:
     *
     * - @c op_choose(AlphabetSet, T), which creates a random alphabet.
     * - @c op_eq(AlphabetSet, T), which tests for equality between alphabets.
     *
     */
    template<class S>
    struct AlphabetSetBase
      : Structure<S>
    {
    protected:

      //@{
      /// Protected constructor.
      AlphabetSetBase();
      AlphabetSetBase(const AlphabetSetBase& other);
      //@}
    };

    /*----------------.
    | alphabet_traits |
    `----------------*/

    /**
     * Trait for virtual types of structural elements for alphabets.
     *
     * Contains a definition of @c letter_t, the type of
     * any letter in an alphabet. It should be specialized for all
     * derived structures.
     */
    template<typename S, typename T>
    struct alphabet_traits
    {
      /// The type of letters in any alphabet.
      typedef undefined_type	letter_t;

      /// Whether the alphabet has a first projection computable.
      typedef undefined_type	first_projection_t;

      /// Whether the alphabet has a second projection computable.
      typedef undefined_type	second_projection_t;

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

  /*--------------.
  | virtual_types |
  `--------------*/

  /// Specialization of @c virtual_types for @c AlphabetSetBase.
  template<typename S>
  struct virtual_types<algebra::AlphabetSetBase<S> >
    : virtual_types<Structure<S> >
  { };


  /*--------------------------------------.
  | MetaElement<AlphabetSetBase<Self>, T> |
  `--------------------------------------*/

  /**
   * Specialization of @c MetaElement for @c AlphabetSetBase.
   *
   * Services shared by all alphabets.
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

    /// Add a letter to the alphabet from a literal representation.
    void insert(const std::string& lit);

    /// Randomly choose a letter in the alphabet.
    letter_t choose() const;

    /// Select a random letter in all the possible letters in letter_t.
    letter_t random_letter() const;

    /// Retrieve the number of letters in the alphabet.
    size_t size() const;

    /// Retrieve the maximum number of letters the alphabet can contain.
    size_t max_size() const;

    /// Test for matching letters modulo the alphabet meta-symbols.
    bool letter_equality(letter_t, letter_t) const;

    /// Whether the alphabet contains a specified letter.
    bool contains(const letter_t& l) const;

    /// Whether the alphabet contains a finite number of letters.
    bool is_finite() const;

    /// Retrieve a begin iterator.
    //@{
    iterator begin();
    const_iterator begin() const;
    //@}

    /// Retrieve an end iterator.
    //@{
    iterator end();
    const_iterator end() const;
    //@}

  protected:
    /// Protected constructor.
    //@{
    MetaElement();
    MetaElement(const MetaElement& other);
    //@}
  };

  namespace algebra
  {
    /// Implementation of a parser to return a letter.
    template <typename S, typename L>
    L op_parse(const AlphabetSetBase<S>& s,
	       const std::string&,
	       size_t&);

    /// Implementation of generic stream output operator for alphabets.
    template <typename S, typename St, typename T>
    St& op_rout(const AlphabetSetBase<S>& s, St& st, const T& a);

    /// Implementation of generic letter equality modulo meta-characters.
    template <typename S, typename T, typename L>
    bool op_letter_equality(const AlphabetSetBase<S>& s,
			    const T& a,
			    L lhs,
			    L rhs);
  } // ! algebra

  /// Public interface to the letter parser.
  template <typename S, typename T>
  std::pair<bool, typename Element<S, T>::letter_t>
  parse_letter(const Element<S, T>& alphabet,
	       const std::string& s);

  /** @} */
  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/concept/alphabets_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_CONCEPT_ALPHABETS_BASE_HH
