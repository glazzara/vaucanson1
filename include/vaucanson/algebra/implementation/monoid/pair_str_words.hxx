// pair_str_words.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2007, 2008, 2010 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_PAIR_STR_WORDS_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_PAIR_STR_WORDS_HXX

# include <vaucanson/algebra/implementation/monoid/pair_str_words.hh>

namespace vcsn {

  namespace algebra {

    template <class Self, typename T>
    typename
    MetaElement<algebra::FreeMonoidProductBase<Self>, T>::first_monoid_elt_t
    op_first(const algebra::FreeMonoidProductBase<Self>& s, T& v)
    {
      return Element<typename virtual_types<Self>::first_monoid_t,
		     typename T::first_type> (s.first_monoid(), v.first);
    }

    template <class Self, typename T>
    typename
    MetaElement<algebra::FreeMonoidProductBase<Self>, T>::second_monoid_elt_t
    op_second(const algebra::FreeMonoidProductBase<Self>& s, T& v)
    {
      return Element<typename virtual_types<Self>::second_monoid_t,
		     typename T::second_type> (s.second_monoid(), v.second);
    }

    template <class F, class S>
    void
    op_in_mul(const algebra::FreeMonoidProduct<F, S>& s,
	      std::pair<std::basic_string<typename F::letter_t>,
			std::basic_string<typename S::letter_t> >& dst,
	      const std::pair<std::basic_string<typename F::letter_t>,
			      std::basic_string<typename S::letter_t> >& src)
    {
      dst.first += src.first;
      dst.second += src.second;
    }

    template<class F, class S>
    std::pair<std::basic_string<typename F::letter_t>,
	      std::basic_string<typename S::letter_t> >
    op_mul(const algebra::FreeMonoidProduct<F, S>&,
	   const std::pair<std::basic_string<typename F::letter_t>,
			   std::basic_string<typename S::letter_t> >& a,
	   const std::pair<std::basic_string<typename F::letter_t>,
			   std::basic_string<typename S::letter_t> >& b)
    {
      return std::pair< std::basic_string<typename F::letter_t>,
			std::basic_string<typename S::letter_t> >
				(a.first + b.first, a.second + b.second);
    }

    template<class F, class S>
    const std::pair<std::basic_string<typename F::letter_t>,
		    std::basic_string<typename S::letter_t> >
    identity_value(SELECTOR2(algebra::FreeMonoidProduct<F, S>),
		   SELECTOR2(std::pair<std::basic_string<typename F::letter_t>,
			     std::basic_string<typename S::letter_t> >))
    {
      static const std::pair<std::basic_string<typename F::letter_t>,
			     std::basic_string<typename S::letter_t> >
	instance;
      return instance;
    }

    template <class F, class S>
    Element<algebra::FreeMonoidProduct<F, S>,
	    std::pair<std::basic_string<typename F::letter_t>,
		      std::basic_string<typename S::letter_t> > >
    op_choose(const algebra::FreeMonoidProduct<F, S>& s,
	      SELECTOR2(std::pair<std::basic_string<typename F::letter_t>,
				 std::basic_string<typename S::letter_t> >))
    {
      typedef std::basic_string<typename F::letter_t> T1;
      typedef std::basic_string<typename S::letter_t> T2;

      std::pair< T1, T2 > res(s.first_monoid().choose(SELECT(T1)).value(),
			      s.second_monoid().choose(SELECT(T2)).value());

      return Element<algebra::FreeMonoidProduct<F, S>,
		     std::pair< T1, T2 > >		(s, res);
    }

    template<typename Self, typename T>
    void
    op_in_mirror(const algebra::FreeMonoidProductBase<Self>& s, T& v)
    {
      op_in_mirror(s.first_monoid(), v.first);
      op_in_mirror(s.second_monoid(), v.second);
    }

    template<typename Self, typename T, typename Ftor>
    typename Ftor::result_type
    op_length(const algebra::FreeMonoidProductBase<Self>&, const T& v, Ftor f)
    {
      return f(v.first.length(), v.second.length());
    }

    template<typename F, typename S,
	     typename A1, typename A2, typename A3, typename A4>
    bool
    op_is_atom(const algebra::FreeMonoidProduct<F, S>&,
	       const std::pair<std::basic_string<typename F::letter_t, A1, A2>,
			       std::basic_string<typename S::letter_t, A3, A4>
			       >& v)
    {
      return (v.first.length() <= 1) && (v.second.length() <= 1);
    }

    template <typename F, typename S, typename St>
    St&
    op_rout(const FreeMonoidProduct<F, S>& s,
	    St& st,
	    const std::pair<std::basic_string<typename F::letter_t>,
			    std::basic_string<typename S::letter_t> >& v)
    {
      if (v.first.empty() && v.second.empty())
	st << s.representation()->empty;
      else
      {
	st << s.representation()->open_par;
	op_rout(s.first_monoid(), st, v.first);
	st << s.representation()->sep;
	op_rout(s.second_monoid(), st, v.second);
	st << s.representation()->close_par;
      }

      return st;
    }

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_PAIR_STR_WORDS_HXX
