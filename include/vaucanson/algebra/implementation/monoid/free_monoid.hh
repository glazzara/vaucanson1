// free_monoid.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_HH

# include <set>

# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <vaucanson/algebra/implementation/monoid/monoid_rep.hh>
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
      // Type helpers.
      typedef A alphabets_elt_t;
      typedef MonoidRep<FreeMonoid<A> > monoid_rep_t;
      typedef boost::shared_ptr<monoid_rep_t> shared_monoid_rep_t;

      /// Constructor based on an alphabet, with an adaptative
      /// monoid representation.
      FreeMonoid(const A& a);

      /// Constructor based on an alphabet, with a constraint
      /// monoid representation.
      FreeMonoid(const A& a, monoid_rep_t mr);

      /// Copy constructor (preserve the monoid representation).
      FreeMonoid(const FreeMonoid& w);

      /// Representation's accessor.
      const shared_monoid_rep_t representation() const;

      /// Alphabet's accessor.
      /// @bug FIXME: this interface should not exist (s.e. are const once
      /// instantiated)
      A&	alphabet();

      /// Alphabet's accessor
      const A&	alphabet() const;

    public:
      /// This function is here for xml that doesn't know the
      /// representation when constructing the monoid
      void set_representation(monoid_rep_t mr);

    protected:
      shared_monoid_rep_t rep_;
      A alph_;
    };

    template<typename A>
    bool operator==(const FreeMonoid<A>& a,
		    const FreeMonoid<A>& b);

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
#  include <vaucanson/algebra/implementation/monoid/free_monoid.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_HH
