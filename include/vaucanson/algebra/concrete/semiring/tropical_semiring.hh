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
# include <vaucanson/misc/numerical_constraints.hh>
# include <vaucanson/misc/random.hh>

namespace vcsn {

//  FIXME: problem with namespaces
//  namespace algebra {

    // We provide a generic implementation of tropical semirings
    // formed with C++-builtins and standard operations (std::min,
    // std::max, +).

    /*---------------.
    | Identity value |
    `---------------*/
    template<class TropicalKind, typename T> 
    inline
    T identity_value(SELECTOR(TropicalSemiring<TropicalKind>), SELECTOR(T));
        
    template<typename T>
    inline
    T zero_value(SELECTOR(TropicalSemiring<TropicalMax>), SELECTOR(T));

    template<typename T>
    inline
    T zero_value(SELECTOR(TropicalSemiring<TropicalMin>), SELECTOR(T));

    /*------------.
    | op_contains |
    `------------*/
    template<class TropicalKind, typename T>
    inline
    bool op_contains(const TropicalSemiring<TropicalKind>& s, T c);
 
    /*--------------------.
    | Multiplication is + |
    `--------------------*/
    template<class TropicalKind, typename T, typename U>
    inline
    void op_in_mul(const TropicalSemiring<TropicalKind>& s1,
		   T& dst, U arg);

    template<class TropicalKind, typename T, typename U>
    inline
    T op_mul(const TropicalSemiring<TropicalKind>& s, T a, U b);

    /*---------.
    | Addition |
    `---------*/
    template<typename T, typename U>
    inline
    void op_in_add(const TropicalSemiring<TropicalMax>& s1,
		   T& dst, U arg);

    template<typename T, typename U>
    void op_in_add(const TropicalSemiring<TropicalMin>& s1,
		   T& dst, U arg);

    template<typename T, typename U>
    T op_add(const TropicalSemiring<TropicalMax>& s, T a, U b);

    template<typename T, typename U>
    T op_add(const TropicalSemiring<TropicalMin>& s, T a, U b);

    /*-----.
    | Star |
    `-----*/
    template <typename T>
    static inline bool 
    op_stareable(const TropicalSemiring<TropicalMin>& s, T b);

    template <class T>
    static inline void 
    op_in_star(const TropicalSemiring<TropicalMin>& s, T& b);

    template <typename T>
    static inline bool 
    op_stareable(const TropicalSemiring<TropicalMax>& s, T b);

    template <class T>
    static inline void 
    op_in_star(const TropicalSemiring<TropicalMax>& s, T& b);
    
    template <class TropicalKind, class T>
    Element<TropicalSemiring<TropicalKind>, T>
    op_choose(const TropicalSemiring<TropicalKind>& set, SELECTOR(T));
    
    template <class TropicalKind, typename T>
    bool
    op_can_choose_non_stareable(const TropicalSemiring<TropicalKind>& set,
			    SELECTOR(T));

    template <class TropicalKind, typename T>
    Element<TropicalSemiring<TropicalKind>, T>
    op_choose_stareable(const TropicalSemiring<TropicalKind>& set,
			SELECTOR(T));

    template <class TropicalKind, typename T>
    Element<TropicalSemiring<TropicalKind>, T>
    op_choose_non_stareable(const TropicalSemiring<TropicalKind>& set,
			    SELECTOR(T));

    /*---------------.
    | Pretty printer |
    `---------------*/
    template<typename St, typename T>
    St& op_rout(const TropicalSemiring<TropicalMax>& s, St& st, const T& v);

    template<typename St, typename T>
    St& op_rout(const TropicalSemiring<TropicalMin>& s, St& st, const T& v);

//  } // algebra

} // vcsn

# include <vaucanson/algebra/concrete/semiring/tropical_semiring.hxx>

#endif // ALGEBRA_TROPICAL_SEMIRING_HH
