// tropical_semiring.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_CYCLIC_SEMIRING_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_CYCLIC_SEMIRING_HXX
# include <vaucanson/config/system.hh>
# include <vaucanson/algebra/implementation/semiring/cyclic_semiring.hh>
# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/limits.hh>

namespace vcsn {

  namespace algebra {

    /*---------------.
    | Identity value |
    `---------------*/
    template<unsigned int n, typename T>
    T identity_value(SELECTOR(algebra::CyclicSemiring<n>), SELECTOR(T))
    {
      return T(1);
    }

    template<unsigned int n, typename T>
    bool show_identity_value(SELECTOR(algebra::CyclicSemiring<n>),
			     SELECTOR(T))
    {
      return false;
    }

    template<unsigned int n, typename T>
    bool
    is_positive_semiring(SELECTOR(algebra::CyclicSemiring<n>), SELECTOR(T))
    {
      return false;
    }

    template<unsigned int n, typename T>
    T zero_value(SELECTOR(algebra::CyclicSemiring<n>), SELECTOR(T))
    {
      return T(0);
    }

    /*------------.
    | op_contains |
    `------------*/
    template<unsigned int n, typename T>
    bool op_contains(const algebra::CyclicSemiring<n>&, T c)
    {
      return true;
    }

    /*--------------------.
    | Multiplication is * |
    `--------------------*/
    template<unsigned int n, typename T, typename U>
    void op_in_mul(const algebra::CyclicSemiring<n>&,
		   T& dst, U arg)
    {
      dst = (dst * arg) % n;
      dst = (dst < 0) ? dst + n : dst;
    }

    template<unsigned int n, typename T, typename U>
    T op_mul(const algebra::CyclicSemiring<n>&, T a, U b)
    {
      T res = (a * b) % n;
      return ((res < 0) ? res + n : res);
    }

    /*---------.
    | Addition |
    `---------*/
    template<unsigned int n, typename T, typename U>
    void op_in_add(const algebra::CyclicSemiring<n>&,
		   T& dst, U arg)
    {
      dst = ((dst + arg) + (2 * n)) % n;
    }

    template<unsigned int n, typename T, typename U>
    T op_add(const algebra::CyclicSemiring<n>&, T a, U b)
    {
      return ((a + b) + (2 * n)) % n;
    }

    /*---------.
    | Division |
    `---------*/

    template<unsigned int n, typename T, typename U>
    void op_in_div(const algebra::CyclicSemiring<n>& s1,
		   T& dst, U arg)
    {
      dst = (dst / arg) % n;
      dst = (dst < 0) ? dst + n : dst;
    }

    template<unsigned int n, typename T, typename U>
    T op_div(const algebra::CyclicSemiring<n>& s, T a, U b)
    {
      T res = (a / b) % n;
      return ((res < 0) ? res + n : res);
    }

    /*-------------.
    | Substraction |
    `-------------*/

    template<unsigned int n, typename T, typename U>
    void op_in_sub(const algebra::CyclicSemiring<n>& s1,
		   T& dst, U arg)
    {
      dst = (dst - arg) % n;
      dst = (dst < 0) ? dst + n : dst;
    }

    template<unsigned int n, typename T, typename U>
    T op_sub(const algebra::CyclicSemiring<n>& s,
	     T a, U b)
    {
      T res = (a - b) % n;
      return ((res < 0) ? res + n : res);
    }

    /*-----.
    | Star |
    `-----*/
    template <unsigned int n, typename T>
    bool
    op_starable(const algebra::CyclicSemiring<n>&, T b)
    {
      if (b == T(0))
	return true;
      return false;
    }

    template <unsigned int n, class T>
    void
    op_in_star(const algebra::CyclicSemiring<n>&, T& b)
    {
      if (b == T(0))
	{
	  b = T(0);
	  return;
	}
      assertion(! "star not defined.");
    }

    template <unsigned int n, class T>
    Element<algebra::CyclicSemiring<n>, T>
    op_choose(const algebra::CyclicSemiring<n>& set, SELECTOR(T))
    {
      return Element<algebra::CyclicSemiring<n>, T>
	(set, misc::random::generate<T>());
    }

    template <unsigned int n, typename T>
    bool
    op_can_choose_non_starable(const algebra::CyclicSemiring<n>&,
			       SELECTOR(T))
    {
      return true;
    }

    template <unsigned int n, class T>
    Element<algebra::CyclicSemiring<n>, T>
    op_choose_starable(const algebra::CyclicSemiring<n>& set,
		       SELECTOR(T))
    {
      T r;
      do
	r = op_choose(set, SELECT(T));
      while (!op_starable(set, r));
      return r;
    }

    template <unsigned int n, class T>
    Element<algebra::CyclicSemiring<n>, T>
    op_choose_non_starable(const algebra::CyclicSemiring<n>& set,
			   SELECTOR(T))
    {
      T r;
      do
	r = op_choose(set, SELECT(T));
      while (!op_starable(set, r));
      return r;
    }

    /*---------------.
    | Pretty printer |
    `---------------*/
    template<unsigned int n, typename St, typename T>
    St& op_rout(const algebra::CyclicSemiring<n>&, St& st, const T& v)
    {
      st << v;
      return st;
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_CYCLIC_SEMIRING_HXX
