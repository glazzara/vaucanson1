// tropical_semiring.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and
// Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef ALGEBRA_TROPICAL_SEMIRING_HH
# define ALGEBRA_TROPICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/tropical_semiring.hh>

namespace vcsn {

    // We provide a generic implementation of tropical semirings
    // formed with C++-builtins and standard operations (std::min,
    // std::max, +).

    /*---------------.
    | Identity value |
    `---------------*/
    template<class TropicalKind, typename T> 
    inline
    T identity_value(SELECTOR(algebra::TropicalSemiring<TropicalKind>), SELECTOR(T));
        
    template<typename T>
    inline
    T zero_value(SELECTOR(algebra::TropicalSemiring<algebra::TropicalMax>), SELECTOR(T));

    template<typename T>
    inline
    T zero_value(SELECTOR(algebra::TropicalSemiring<algebra::TropicalMin>), SELECTOR(T));

    /*------------.
    | op_contains |
    `------------*/
    template<class TropicalKind, typename T>
    inline
    bool op_contains(const algebra::TropicalSemiring<TropicalKind>& s, T c);
 
    /*--------------------.
    | Multiplication is + |
    `--------------------*/
    template<class TropicalKind, typename T, typename U>
    inline
    void op_in_mul(const algebra::TropicalSemiring<TropicalKind>& s1,
		   T& dst, U arg);

    template<class TropicalKind, typename T, typename U>
    inline
    T op_mul(const algebra::TropicalSemiring<TropicalKind>& s, T a, U b);

    /*---------.
    | Addition |
    `---------*/
    template<typename T, typename U>
    inline
    void op_in_add(const algebra::TropicalSemiring<algebra::TropicalMax>& s1,
		   T& dst, U arg);

    template<typename T, typename U>
    void op_in_add(const algebra::TropicalSemiring<algebra::TropicalMin>& s1,
		   T& dst, U arg);

    template<typename T, typename U>
    T op_add(const algebra::TropicalSemiring<algebra::TropicalMax>& s, T a, U b);

    template<typename T, typename U>
    T op_add(const algebra::TropicalSemiring<algebra::TropicalMin>& s, T a, U b);

    /*-----.
    | Star |
    `-----*/
    template <typename T>
    static inline bool 
    op_stareable(const algebra::TropicalSemiring<algebra::TropicalMin>& s, T b);

    template <class T>
    static inline void 
    op_in_star(const algebra::TropicalSemiring<algebra::TropicalMin>& s, T& b);

    template <typename T>
    static inline bool 
    op_stareable(const algebra::TropicalSemiring<algebra::TropicalMax>& s, T b);

    template <class T>
    static inline void 
    op_in_star(const algebra::TropicalSemiring<algebra::TropicalMax>& s, T& b);
    
    template <class TropicalKind, class T>
    Element<algebra::TropicalSemiring<TropicalKind>, T>
    op_choose(const algebra::TropicalSemiring<TropicalKind>& set, SELECTOR(T));
    
    template <class TropicalKind, typename T>
    bool
    op_can_choose_non_stareable(const algebra::TropicalSemiring<TropicalKind>& set,
			    SELECTOR(T));

    template <class TropicalKind, typename T>
    Element<algebra::TropicalSemiring<TropicalKind>, T>
    op_choose_stareable(const algebra::TropicalSemiring<TropicalKind>& set,
			SELECTOR(T));

    template <class TropicalKind, typename T>
    Element<algebra::TropicalSemiring<TropicalKind>, T>
    op_choose_non_stareable(const algebra::TropicalSemiring<TropicalKind>& set,
			    SELECTOR(T));

    /*---------------.
    | Pretty printer |
    `---------------*/
    template<typename St, typename T>
    St& op_rout(const algebra::TropicalSemiring<algebra::TropicalMax>& s, St& st, const T& v);

    template<typename St, typename T>
    St& op_rout(const algebra::TropicalSemiring<algebra::TropicalMin>& s, St& st, const T& v);

//  } // algebra

} // vcsn

# include <vaucanson/algebra/concrete/semiring/tropical_semiring.hxx>

#endif // ALGEBRA_TROPICAL_SEMIRING_HH
