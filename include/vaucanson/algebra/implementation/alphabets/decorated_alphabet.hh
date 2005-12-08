// decorated_alphabet.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_DECORATED_ALPHABET_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_DECORATED_ALPHABET_HH

# include <vaucanson/algebra/implementation/alphabets/alphabets.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup alphabet *//** @{ */

    /*------------------------.
    | AlphabetDecorator<L, T> |
    `------------------------*/

    /**
     * Decorate a given alphabet implementation with meta-symbols.
     *
     * The meta-symbols are:
     *
     * - a 'joker' which symbolizes every letter of the alphabet,
     * - a 'discard' which symbolizes every letter that is not in the
     *   alphabet but of the same letter type.
     *
     * The meta-symbols are encoded using  the type of the letter with
     * a default  value that  has to be  specified with the  traits @c
     * meta_symbol.  For instance, '?' and '#' for char. Yet, if these
     * characters  are already present  in the  alphabet, we  look for
     * another  character  in a  incremental  way. If,  unfortunately,
     * there is not enough place, the program is stopped.
     */
    template <class L, class T>
    class AlphabetDecorator
    {
    public:
      typedef L		letter_t;
      typedef T		alphabet_impl_t;
      typedef typename T::const_iterator const_iterator;
      typedef typename T::iterator iterator;

      AlphabetDecorator();
      AlphabetDecorator(alphabet_impl_t& alphabet);
      ~AlphabetDecorator();

      letter_t joker() const;
      letter_t other() const;
      void insert(L);
      unsigned size() const;
      iterator begin();
      iterator end();
      const_iterator begin() const;
      const_iterator end() const;
      alphabet_impl_t& alphabet();
      const alphabet_impl_t& alphabet() const;

    private:
      alphabet_impl_t* alphabet_;
      letter_t	       joker_;
      letter_t	       other_;
      bool	       alphabet_owner_;
    };


    /*---------------------------------------------------------.
    | alphabet_traits<AlphabetSet<L>, AlphabetDecorator<L, T>> |
    `---------------------------------------------------------*/

    /// Meta information about the mixing of AlphabetSet with AlphabetDecorator.
    template<typename L, typename T>
    struct alphabet_traits<AlphabetSet<L>, AlphabetDecorator<L, T> >
    {
      /// The type of letter hold by the alphabet.
      typedef L			letter_t;
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup alphabet *//** @{ */

  /*-----------------------------------------------------.
  | MetaElement<AlphabetSet<L>, AlphabetDecorator<L, T>> |
  `-----------------------------------------------------*/

  /**
   * Services of every alphabet implemented with AlphabetDecorator<L, T>.
   *
   * @see MetaElement<AlphabetSetBase<Self>, T>
   */
  template<typename L, typename T>
  struct MetaElement<algebra::AlphabetSet<L>, algebra::AlphabetDecorator<L, T> >
    : MetaElement<algebra::AlphabetSetBase<algebra::AlphabetSet<L> >,
		  algebra::AlphabetDecorator<L, T> >
  {
    /// The dynamic properties depends on the implementation one.
    static const bool dynamic_value =
    MetaElement<algebra::AlphabetSet<L>,T >::dynamic_value;

    /// The meta-symbol that symbolizes all the alphabet's symbols.
    L	joker() const;

    /// The meta-symbol that symbolizes the symbol not in the alphabet.
    L	other() const;
  };

  /** @} */
  /** @} */

  template<typename L, typename T>
  bool op_contains(const algebra::AlphabetSet<L>& s,
		   const algebra::AlphabetDecorator<L, T>& a);

  template<typename L, typename T>
  bool op_is_finite(const algebra::AlphabetSet<L>& s,
		    const algebra::AlphabetDecorator<L, T>& a);

  template<typename L, typename T>
  bool op_contains_e(const algebra::AlphabetSet<L>& s,
		     const algebra::AlphabetDecorator<L, T>& a,
		     const L& v);

  template <typename T, typename L>
  bool op_letter_equality(const algebra::AlphabetSet<L>& s,
				 const algebra::AlphabetDecorator<L, T>& a,
				 L lhs,
				 L rhs);


} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/alphabets/decorated_alphabet.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_DECORATED_ALPHABET_HH
