// words.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_WORDS_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_WORDS_HH

# include <string>
# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <vaucanson/misc/unique.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn
{
  namespace algebra
  {
    /** @addtogroup algebra    */ /** @{ */
    /** @addtogroup freemonoid */ /** @{ */

    /*--------------.
    | FreeMonoid<A> |
    `--------------*/

    /// Implementation of a free monoid which aggregates its alphabet.
    template<typename A>
    struct FreeMonoid
      : FreeMonoidBase<FreeMonoid<A> >
    {
      typedef A alphabets_elt_t;

      /// Constructor based on an alphabet.
      FreeMonoid(const A& a);

      /// Copy constructor.
      FreeMonoid(const FreeMonoid& w);

      /// Alphabet's accessor.
      /// @bug FIXME: this interface should not exist (s.e. are const once instantiated)
      A&	alphabet();

      /// Alphabet's accessor
      const A&	alphabet() const;

    protected:
      A alph_;
    };

    template<typename A>
    bool operator==(const FreeMonoid<A>& a,
		    const FreeMonoid<A>& b);

    /*---------------------------------------------------------------------.
    | word_traits<FreeMonoid<A>, std::basic_string<typename A::letter_t> > |
    `---------------------------------------------------------------------*/

    /**
     * Meta information about the mixing of FreeMonoid with
     * std::basic_string.
     */
    template <typename A>
    struct word_traits<FreeMonoid<A>,
		       std::basic_string<typename A::letter_t> >
    {
      /// The type of the alphabet.
      typedef A alphabet_t;

      /// The type of the word.
      typedef Element<FreeMonoid<A>,
	      std::basic_string<typename alphabet_t::letter_t> > word_t;

      /// The value type of word.
      typedef typename word_t::value_t word_value_t;

      /// The type of the first projection alphabet.
      typedef typename alphabet_traits<typename alphabet_t::set_t,
				       typename alphabet_t::value_t>::
	first_projection_t first_projection_alphabet_t;

      /// The type of the second projection alphabet.
      typedef typename alphabet_traits<typename alphabet_t::set_t,
				       typename alphabet_t::value_t>::
	second_projection_t second_projection_alphabet_t;

      /// The type of the first projection monoid.
      typedef FreeMonoid<first_projection_alphabet_t> first_monoid_t;

      /// The type of the second projection monoid.
      typedef FreeMonoid<second_projection_alphabet_t> second_monoid_t;

      /// The type of the first projection word.
      typedef Element<first_monoid_t,
	      std::basic_string<typename first_projection_alphabet_t::
				letter_t> > first_projection_t;

      /// The value type of the first projection word.
      typedef typename first_projection_t::value_t first_projection_value_t;

      /// The type of the second projection word.
      typedef Element<second_monoid_t,
	      std::basic_string<typename second_projection_alphabet_t::
				letter_t> > second_projection_t;

      /// The value type of the second projection word.
      typedef typename second_projection_t::value_t second_projection_value_t;

      /// The first projection word maker.
      static first_projection_t first_projection(const first_monoid_t&,
						 const word_t&);
      static first_projection_value_t first_projection(const word_value_t&);

      /// The second projection word maker.
      static second_projection_t second_projection(const second_monoid_t&,
						   const word_t&);
      static second_projection_value_t second_projection(const word_value_t&);
    };

    /** @} */
    /** @} */

  } // ! algebra

  /** @addtogroup algebra    */ /** @{ */
  /** @addtogroup freemonoid */ /** @{ */

  /*-------------------------------.
  | dynamic_traits<FreeMonoid<A> > |
  `-------------------------------*/
  /// Meta information about FreeMonoid.
  template<typename A>
  struct dynamic_traits<algebra::FreeMonoid<A> >
    : dynamic_traits<algebra::FreeMonoidBase<algebra::FreeMonoid<A> > >
  {
    /// SetWord is dynamic iff its alphabet is.
    static const bool		ret = A::dynamic;
  };

  /*------------------------------.
  | MetaElement<FreeMonoid<A>, T> |
  `------------------------------*/
  /// Services of an element of a free monoid implemented with
  /// FreeMonoid.
  template<typename A, typename T>
  struct MetaElement<algebra::FreeMonoid<A>, T>
    : MetaElement<algebra::FreeMonoidBase<algebra::FreeMonoid<A> >, T>
  {};

  /** @} */
  /** @} */

  template <class A>
  struct virtual_types<algebra::FreeMonoid<A> >
    : virtual_types<algebra::FreeMonoidBase<algebra::FreeMonoid<A> > >
  {
    /// Commonly a free monoid use the multiplication symbol as operation.
    typedef algebra::mul_kind semigroup_kind;

    typedef A		alphabet_t;
  };

  /**
   * Maximum length of words generated by op_choose.
   *
   * To retrieve  this information, just  use the value named  with
   * @c op_choose_max_word_length.
   */
  enum op_choose_max_word_length_t { op_choose_max_word_length = 32 };

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/free_monoid/words.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_WORDS_HH
