// str_words.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson
// Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_STR_WORDS_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_STR_WORDS_HXX

# include <vaucanson/algebra/implementation/monoid/str_words.hh>

# include <vaucanson/misc/char_traits.hh>

namespace vcsn {

  namespace algebra {

    template<typename A>
    void
    op_in_mul(const algebra::FreeMonoid<A>&,
	      std::basic_string<typename A::letter_t>& dst,
	      const std::basic_string<typename A::letter_t>& src)
    {
      dst += src;
    }

    template<typename A>
    std::basic_string<typename A::letter_t>
    op_mul(const algebra::FreeMonoid<A>&,
	   const std::basic_string<typename A::letter_t>& a,
	   const std::basic_string<typename A::letter_t>& b)
    {
      return a + b;
    }

    template <typename A>
    bool
    op_xeq(const algebra::FreeMonoid<A>& s,
	   const std::basic_string<typename A::letter_t>& a,
	   const std::basic_string<typename A::letter_t>& b)
    {
      typename std::basic_string<typename A::letter_t>::const_iterator
	m = b.begin();
      typename std::basic_string<typename A::letter_t>::const_iterator l;
      for (l = a.begin(); m != b.end() && l != a.end(); ++l)
	{
	  if (! s.alphabet().letter_equality(*l, *m))
	    return false;
	  ++m;
	}
      return (m == b.end() && l == a.end());
    }

    template<typename A>
    const std::basic_string<typename A::letter_t>&
    identity_value(SELECTOR(algebra::FreeMonoid<A>),
		   SELECTOR(std::basic_string<typename A::letter_t>))
    {
      static const std::basic_string<typename A::letter_t> instance;
      return instance;
    }

    template<typename A>
    const std::basic_string<typename A::letter_t,
			    misc::char_traits<typename A::letter_t> >&
    identity_value(SELECTOR(algebra::FreeMonoid<A>),
		   SELECTOR2(std::basic_string<typename A::letter_t,
			    misc::char_traits<typename A::letter_t> >))
    {
      static const std::basic_string<typename A::letter_t,
	misc::char_traits<typename A::letter_t> > instance;
      return instance;
    }

    template<typename A>
    std::basic_string<typename A::letter_t>
    op_convert(SELECTOR(algebra::FreeMonoid<A>),
	       SELECTOR(std::basic_string<typename A::letter_t>),
	       const typename A::letter_t& c)
    {
      std::basic_string<typename A::letter_t> str;
      str = c;
      return str;
    }

    template<typename A>
    std::basic_string<typename A::letter_t>
    op_convert(SELECTOR(algebra::FreeMonoid<A>) mon,
	       SELECTOR(std::basic_string<typename A::letter_t>),
	       const std::string& str)
    {
      Element<algebra::FreeMonoid<A>,
	      std::basic_string<typename A::letter_t> > x(mon);
      std::string::const_iterator i = str.begin();
      parse_word(x, str, i, std::set<char>());
      return x.value();
    }

    template<typename A>
    std::basic_string<typename A::letter_t>
    op_convert(SELECTOR(algebra::FreeMonoid<A>) M,
	       SELECTOR(std::basic_string<typename A::letter_t>) bs,
	       const char* str)
    {
      return op_convert(M, bs, std::string(str));
    }

    template <class A>
    Element<algebra::FreeMonoid<A>, std::basic_string<typename A::letter_t> >
    op_choose(const algebra::FreeMonoid<A>& s,
	      SELECTOR(std::basic_string<typename A::letter_t>))
    {
      unsigned length =
	misc::random::generate<unsigned>(0, op_choose_max_word_length);
      std::basic_string<typename A::letter_t> r;
      for (unsigned i = 0; i < length; ++i)
	r = r + s.alphabet().choose();
      return Element<algebra::FreeMonoid<A>,
	std::basic_string<typename A::letter_t> >(s, r);
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

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_STR_WORDS_HXX
