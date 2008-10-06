// words.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_WORDS_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_WORDS_HXX

# include <vaucanson/algebra/implementation/free_monoid/words.hh>

namespace vcsn
{
  namespace algebra
  {
    /*---------.
    | Words<A> |
    `---------*/

    template <class A>
    FreeMonoid<A>::FreeMonoid(const A& a) : alph_(a)
    {}

    template <class A>
    FreeMonoid<A>::FreeMonoid(const FreeMonoid& w) :
      FreeMonoidBase<FreeMonoid<A> >(w),
      alph_(w.alph_)
    {}

    template <class A>
    A& FreeMonoid<A>::alphabet()
    {
      return alph_;
    }

    template <class A>
    const A& FreeMonoid<A>::alphabet() const
    {
      return alph_;
    }

    template<typename A>
    bool operator==(const FreeMonoid<A>& a,
		    const FreeMonoid<A>& b)
    {
      return a.alphabet() == b.alphabet();
    }

# define WORD_TRAITS \
    word_traits<FreeMonoid<A>, std::basic_string<typename A::letter_t> >

    template <typename A>
    inline typename WORD_TRAITS::first_projection_value_t
    WORD_TRAITS::first_projection(const WORD_TRAITS::word_value_t& str)
    {
      // We can not project if the type does not support it.
      static_assertion_(not (misc::static_eq<first_projection_t,
			     undefined_type>::value), need_first_projection)

      first_projection_value_t R;

      // We assume we can access the first projection with "first".
      for_all_const_(word_value_t, i, str)
	R += (*i).first;

      return R;
    }

    template <typename A>
    inline typename WORD_TRAITS::first_projection_t
    WORD_TRAITS::first_projection(const WORD_TRAITS::first_monoid_t& mon,
				  const WORD_TRAITS::word_t& word)
    {
      // We can not project if the type does not support it.
      static_assertion_(not (misc::static_eq<first_projection_t,
			     undefined_type>::value), need_first_projection)

      first_projection_t R(mon);

      R.value() = first_projection(word.value());

      return R;
    }

    template <typename A>
    inline typename WORD_TRAITS::second_projection_value_t
    WORD_TRAITS::second_projection(const WORD_TRAITS::word_value_t& str)
    {
      // We can not project if the type does not support it.
      static_assertion_(not (misc::static_eq<second_projection_t,
			     undefined_type>::value), need_second_projection)

      second_projection_value_t R;

      // We assume we can access the second projection with "second".
      for_all_const_(word_value_t, i, str)
	R += (*i).second;

      return R;
    }

    template <typename A>
    inline typename WORD_TRAITS::second_projection_t
    WORD_TRAITS::second_projection(const WORD_TRAITS::second_monoid_t& mon,
				   const WORD_TRAITS::word_t& word)
    {
      // We can not project if the type does not support it.
      static_assertion_(not (misc::static_eq<second_projection_t,
			     undefined_type>::value), need_second_projection)

      second_projection_t R(mon);

      R.value() = second_projection(word.value());

      return R;
    }

# undef WORD_TRAITS

  } // ! algebra

} // ! vcsn


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_WORDS_HXX
