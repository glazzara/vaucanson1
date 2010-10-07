// str_words.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2010 The Vaucanson
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

    template <typename A>
    std::pair<bool, int>
    op_parse(const FreeMonoid<A>& s,
	     std::basic_string<typename A::letter_t>& v,
	     const std::string& in)
    {
      if (in.empty())
	return std::make_pair(true, 0);

      std::string& empty = s.representation()->empty;
      int empty_size = empty.size();
      std::string& concat = s.representation()->concat;
      int concat_size = concat.size();
      bool last_token_is_letter = false;

      size_t i;
      for (i = 0; i < in.size();)
	{
	  // Is this a concatenation symbol?
	  if ((concat_size > 0) && !in.compare(i, concat_size, concat))
	    {
	      if (!last_token_is_letter)
		return std::make_pair(false, i);
	      i += concat_size;
	      last_token_is_letter = false;
	      continue;
	    }

	  //// We could make the use of the concatenation symbol
	  //// mandatory with the following two lines.
	  // if (last_token_is_letter && concat_size > 0)
	  //   return std::make_pair(false, i);

	  // Is this the empty word?
	  if (!in.compare(i, empty_size, empty))
	    {
	      i += empty_size;
	      last_token_is_letter = true;
	      continue;
	    }

	  // Finally try to read a real letter.
	  // Note that op_parse will update i.
	  std::pair<bool, typename A::letter_t> letter =
	    op_parse(s.alphabet().structure(), s.alphabet().value(), in, i);
	  if (!letter.first)
	    return std::make_pair(false, i);
	  v.push_back(letter.second);
	  last_token_is_letter = true;
	}
      return std::make_pair(last_token_is_letter, i);
    }

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

    template<typename A, typename St>
    St&
    op_rout(const FreeMonoid<A>& s,
	    St& st,
	    const std::basic_string<typename A::letter_t>& v)
    {
      if (v.empty())
	st << s.representation()->empty;
      else
      {
	// Type helpers.
	typedef typename A::letter_t letter_t;
	typedef algebra::letter_traits<letter_t> letter_traits_t;
	typedef typename std::basic_string<letter_t>::const_iterator iter_t;

	iter_t i = v.begin();

	// Print the first letter.
	st << letter_traits_t::letter_to_literal(*i);
	++i;

	// Print the following letters using the concat string.
	while (i != v.end())
	{
	  st << s.representation()->concat
	     << letter_traits_t::letter_to_literal(*i);
	  ++i;
	}
      }

      return st;
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
    bool
    op_is_atom(const algebra::FreeMonoid<A>&,
	       const std::basic_string<typename A::letter_t>& v)
    {
      return v.size() <= 1;
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
			     undefined_type>::value), need_first_projection);

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
			     undefined_type>::value), need_first_projection);

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
			     undefined_type>::value), need_second_projection);

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
			     undefined_type>::value), need_second_projection);

      second_projection_t R(mon);

      R.value() = second_projection(word.value());

      return R;
    }

# undef WORD_TRAITS

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_STR_WORDS_HXX
