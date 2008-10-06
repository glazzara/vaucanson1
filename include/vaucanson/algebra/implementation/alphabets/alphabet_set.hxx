// alphabet_set.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_ALPHABET_SET_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_ALPHABET_SET_HXX

# include <vaucanson/algebra/concept/letter.hh>
# include <vaucanson/algebra/implementation/alphabets/alphabet_set.hh>

# include <limits>

namespace vcsn
{

  namespace algebra
  {

    /*----------------------------------------.
    | Projections for types that support them |
    `----------------------------------------*/

# define ALPHABET_TRAITS \
    alphabet_traits<AlphabetSet<L>, std::set<L> >

    template <typename L>
    inline typename ALPHABET_TRAITS::first_projection_t
    ALPHABET_TRAITS::first_projection(const ALPHABET_TRAITS::alphabet_t& A)
    {
      // We can not project if the type does not support it.
      static_assertion_(not (misc::static_eq<first_projection_t,
			     undefined_type>::value), need_first_projection)

      first_projection_t R;

      for_all_const_(alphabet_t, i, A)
      {
	// We assume we can access the first projection with "first".
	R.insert((*i).first);
      }

      return R;
    }

    template <typename L>
    inline typename ALPHABET_TRAITS::second_projection_t
    ALPHABET_TRAITS::second_projection(const ALPHABET_TRAITS::alphabet_t& A)
    {
      // We can not project if the type does not support it.
      static_assertion_(not (misc::static_eq<second_projection_t,
			     undefined_type>::value), need_second_projection)

      second_projection_t R;

      for_all_const_(alphabet_t, i, A)
      {
	// We assume we can access the second projection with "second".
	R.insert((*i).second);
      }

      return R;
    }

# undef ALPHABET_TRAITS

    /*-----------------------------------------------------------.
    | Definition of an alphabet implementation based on std::set |
    `-----------------------------------------------------------*/

    template <typename L>
    size_t
    op_max_size(const algebra::AlphabetSet<L>&, const std::set<L>&)
    {
      return algebra::letter_traits<L>::cardinal;
    }

    template<typename L>
    bool op_contains(const algebra::AlphabetSet<L>&, const std::set<L>&)
    {
      return true;
    }

    template<typename L>
    bool op_is_finite(const algebra::AlphabetSet<L>&, const std::set<L>&)
    {
      return true;
    }

    template<typename L>
    bool op_contains_e(const algebra::AlphabetSet<L>&, const std::set<L>& a,
		       const L& v)
    {
      return a.find(v) != a.end();
    }

  }

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_ALPHABET_SET_HXX
