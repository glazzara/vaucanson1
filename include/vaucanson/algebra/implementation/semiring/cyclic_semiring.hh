// cyclic_semiring.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2007, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_CYCLIC_SEMIRING_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_CYCLIC_SEMIRING_HH

# include <vaucanson/algebra/concept/cyclic_semiring.hh>

namespace vcsn {

  namespace algebra {

    // We provide a generic implementation of cyclic semirings
    // formed with C++-builtins and standard operations (+, *, %).

    /*---------------.
    | Identity value |
    `---------------*/
    template<unsigned int n, typename T>
    T identity_value(SELECTOR(algebra::CyclicSemiring<n>),
		     SELECTOR(T));

    template<unsigned int n, typename T>
    bool show_identity_value(SELECTOR(algebra::CyclicSemiring<n>),
			     SELECTOR(T));

    template<unsigned int n, typename T>
    bool
    is_positive_semiring(SELECTOR(algebra::CyclicSemiring<n>), SELECTOR(T));

    template<unsigned int n, typename T>
    T zero_value(SELECTOR(algebra::CyclicSemiring<n>),
		 SELECTOR(T));

    template<unsigned int n, typename T>
    T zero_value(SELECTOR(algebra::CyclicSemiring<n>),
		 SELECTOR(T));

    /*------------.
    | op_contains |
    `------------*/
    template<unsigned int n, typename T>
    bool op_contains(const algebra::CyclicSemiring<n>& s, T c);

    /*---------------.
    | Multiplication |
    `---------------*/
    template<unsigned int n, typename T, typename U>
    void op_in_mul(const algebra::CyclicSemiring<n>& s1,
		   T& dst, U arg);

    template<unsigned int n, typename T, typename U>
    T op_mul(const algebra::CyclicSemiring<n>& s, T a, U b);

    /*---------.
    | Addition |
    `---------*/
    template<unsigned int n, typename T, typename U>
    void op_in_add(const algebra::CyclicSemiring<n>& s1,
		   T& dst, U arg);

    template<unsigned int n, typename T, typename U>
    T op_add(const algebra::CyclicSemiring<n>& s,
	     T a, U b);

    /*---------.
    | Division |
    `---------*/

    template<unsigned int n, typename T, typename U>
    void op_in_div(const algebra::CyclicSemiring<n>& s1,
		   T& dst, U arg);

    template<unsigned int n, typename T, typename U>
    T op_div(const algebra::CyclicSemiring<n>& s, T a, U b);

    /*-------------.
    | Substraction |
    `-------------*/

    template<unsigned int n, typename T, typename U>
    void op_in_sub(const algebra::CyclicSemiring<n>& s1,
		   T& dst, U arg);

    template<unsigned int n, typename T, typename U>
    T op_sub(const algebra::CyclicSemiring<n>& s,
	     T a, U b);

    /*-----.
    | Star |
    `-----*/
    template <unsigned int n, typename T>
    bool
    op_starable(const algebra::CyclicSemiring<n>&, T b);

    template <unsigned int n, class T>
    void
    op_in_star(const algebra::CyclicSemiring<n>& s, T& b);

    template <unsigned int n, class T>
    Element<algebra::CyclicSemiring<n>, T>
    op_choose(const algebra::CyclicSemiring<n>& set, SELECTOR(T));

    template <unsigned int n, typename T>
    bool
    op_can_choose_non_starable(const algebra::CyclicSemiring<n>&
			       set, SELECTOR(T));

    template <unsigned int n, typename T>
    Element<algebra::CyclicSemiring<n>, T>
    op_choose_starable(const algebra::CyclicSemiring<n>& set,
		       SELECTOR(T));

    template <unsigned int n, typename T>
    Element<algebra::CyclicSemiring<n>, T>
    op_choose_non_starable(const algebra::CyclicSemiring<n>& set,
			   SELECTOR(T));

    /*---------------.
    | Pretty printer |
    `---------------*/
    template<unsigned int n, typename St, typename T>
    St& op_rout(const algebra::CyclicSemiring<n>& s,
		St& st, const T& v);

  } // algebra

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/semiring/cyclic_semiring.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_CYCLIC_SEMIRING_HH
