// tropical_semiring.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2007 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_TROPICAL_SEMIRING_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_TROPICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/tropical_semiring.hh>

namespace vcsn {

  namespace algebra {

    // We provide a generic implementation of tropical semirings
    // formed with C++-builtins and standard operations (std::min,
    // std::max, +).

    /*---------------.
    | Identity value |
    `---------------*/
    template<class TropicalKind, typename T>
    T identity_value(SELECTOR(algebra::TropicalSemiring<TropicalKind>),
		     SELECTOR(T));

    template<typename T>
    T zero_value(SELECTOR(algebra::TropicalSemiring<algebra::TropicalMax>),
		 SELECTOR(T));

    template<typename T>
    T zero_value(SELECTOR(algebra::TropicalSemiring<algebra::TropicalMin>),
		 SELECTOR(T));

    /*------------.
    | op_contains |
    `------------*/
    template<class TropicalKind, typename T>
    bool op_contains(const algebra::TropicalSemiring<TropicalKind>& s, T c);

    /*--------------------.
    | Multiplication is + |
    `--------------------*/
    template<class TropicalKind, typename T, typename U>
    void op_in_mul(const algebra::TropicalSemiring<TropicalKind>& s1,
		   T& dst, U arg);

    template<class TropicalKind, typename T, typename U>
    T op_mul(const algebra::TropicalSemiring<TropicalKind>& s, T a, U b);

    /*---------.
    | Addition |
    `---------*/
    template<typename T, typename U>
    void op_in_add(const algebra::TropicalSemiring<algebra::TropicalMax>& s1,
		   T& dst, U arg);

    template<typename T, typename U>
    void op_in_add(const algebra::TropicalSemiring<algebra::TropicalMin>& s1,
		   T& dst, U arg);

    template<typename T, typename U>
    T op_add(const algebra::TropicalSemiring<algebra::TropicalMax>& s,
	     T a, U b);

    template<typename T, typename U>
    T op_add(const algebra::TropicalSemiring<algebra::TropicalMin>& s,
	     T a, U b);

    /*-----.
    | Star |
    `-----*/
    template <typename T>
    bool
    op_starable(const algebra::TropicalSemiring<algebra::TropicalMin>&, T b);

    template <class T>
    void
    op_in_star(const algebra::TropicalSemiring<algebra::TropicalMin>& s, T& b);

    template <typename T>
    bool
    op_starable(const algebra::TropicalSemiring<algebra::TropicalMax>&, T b);

    template <class T>
    void
    op_in_star(const algebra::TropicalSemiring<algebra::TropicalMax>&, T& b);

    template <class TropicalKind, class T>
    Element<algebra::TropicalSemiring<TropicalKind>, T>
    op_choose(const algebra::TropicalSemiring<TropicalKind>& set, SELECTOR(T));

    template <class TropicalKind, typename T>
    bool
    op_can_choose_non_starable(const algebra::TropicalSemiring<TropicalKind>&
			       set, SELECTOR(T));

    template <class TropicalKind, typename T>
    Element<algebra::TropicalSemiring<TropicalKind>, T>
    op_choose_starable(const algebra::TropicalSemiring<TropicalKind>& set,
		       SELECTOR(T));

    template <class TropicalKind, typename T>
    Element<algebra::TropicalSemiring<TropicalKind>, T>
    op_choose_non_starable(const algebra::TropicalSemiring<TropicalKind>& set,
			   SELECTOR(T));

    /*---------------.
    | Pretty printer |
    `---------------*/
    template<typename St, typename T>
    St& op_rout(const algebra::TropicalSemiring<algebra::TropicalMax>& s,
		St& st, const T& v);

    template<typename St, typename T>
    St& op_rout(const algebra::TropicalSemiring<algebra::TropicalMin>& s,
		St& st, const T& v);

  } // algebra

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/semiring/tropical_semiring.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_TROPICAL_SEMIRING_HH
