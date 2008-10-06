// freemonoid_product_pair_str.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PRODUCT_FREEMONOID_PRODUCT_PAIR_STR_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PRODUCT_FREEMONOID_PRODUCT_PAIR_STR_HH

# include <vaucanson/algebra/concept/freemonoid_product.hh>

# include <utility>
# include <string>

namespace vcsn {

  namespace algebra {

    /*----------------------------------------------------------.
    | Implementation of freemonoid_product with pair of strings |
    `----------------------------------------------------------*/

    template <class Self, typename T>
    typename
    MetaElement<algebra::FreeMonoidProductBase<Self>, T>::first_monoid_elt_t
    op_first(const algebra::FreeMonoidProductBase<Self>& s, T& v);

    template <class Self, typename T>
    typename
    MetaElement<algebra::FreeMonoidProductBase<Self>, T>::second_monoid_elt_t
    op_second(const algebra::FreeMonoidProductBase<Self>& s, T& v);

    template <class F, class S>
    void
    op_in_mul(const algebra::FreeMonoidProduct<F, S>& s,
	      std::pair<std::basic_string<typename F::letter_t>,
			std::basic_string<typename S::letter_t> >& dst,
	      const std::pair<std::basic_string<typename F::letter_t>,
			      std::basic_string<typename S::letter_t> >& src);

    template<class F, class S>
    std::pair<std::basic_string<typename F::letter_t>,
	      std::basic_string<typename S::letter_t> >
    op_mul(const algebra::FreeMonoidProduct<F, S>& s,
	   const std::pair<std::basic_string<typename F::letter_t>,
			   std::basic_string<typename S::letter_t> >& a,
	   const std::pair<std::basic_string<typename F::letter_t>,
			   std::basic_string<typename S::letter_t> >& b);

    template<class F, class S>
    const std::pair<std::basic_string<typename F::letter_t>,
		    std::basic_string<typename S::letter_t> >
    identity_value(SELECTOR2(algebra::FreeMonoidProduct<F, S>),
		   SELECTOR2(std::pair<std::basic_string<typename F::letter_t>,
			           std::basic_string<typename S::letter_t> >));

    template<class F, class S>
    Element<algebra::FreeMonoidProduct<F, S>,
	    std::pair<std::basic_string<typename F::letter_t>,
		      std::basic_string<typename S::letter_t> > >
    op_choose(const algebra::FreeMonoidProduct<F, S>& s,
	      SELECTOR2(std::pair<std::basic_string<typename F::letter_t>,
				  std::basic_string<typename S::letter_t> >));

    template<typename Self, typename T>
    void op_in_mirror (const algebra::FreeMonoidProductBase<Self>& s, T& v);

    template<typename Self, typename T, typename Ftor>
    typename Ftor::result_type
    op_length(const algebra::FreeMonoidProductBase<Self>&, const T& v, Ftor f);

    template <typename Self, typename St, typename T>
    St&
    op_rout(const algebra::FreeMonoidProductBase<Self>& s,
	    St& st,
	    const T& v);

  } // algebra

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/free_monoid_product/freemonoid_product_pair_str.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PRODUCT_FREEMONOID_PRODUCT_PAIR_STR_HH
