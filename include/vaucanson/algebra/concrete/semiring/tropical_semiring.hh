/********************************************
 * <vaucanson/algebra/tropical_semiring.hh> *
 ********************************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef ALGEBRA_TROPICAL_SEMIRING_HH
# define ALGEBRA_TROPICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/tropical_semiring.hh>
# include <vaucanson/misc/numerical_constraints.hh>

namespace vcsn {

  namespace algebra {

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

    /*---------------.
    | Pretty printer |
    `---------------*/
    template<typename St, typename T>
    St& op_rout(const TropicalSemiring<TropicalMax>& s, St& st, const T& v);

    template<typename St, typename T>
    St& op_rout(const TropicalSemiring<TropicalMin>& s, St& st, const T& v);

  } // algebra

} // vcsn

# include <vaucanson/algebra/concrete/semiring/tropical_semiring.hxx>

#endif // ALGEBRA_TROPICAL_SEMIRING_HH
