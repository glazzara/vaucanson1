// numerical_semiring.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_NUMERICAL_SEMIRING_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_NUMERICAL_SEMIRING_HXX

# include <cmath>
# include <vaucanson/algebra/concept/semiring_base.hh>
# include <vaucanson/algebra/implementation/semiring/numerical_semiring.hh>

# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/limits.hh>
# include <vaucanson/misc/contract.hh>

namespace vcsn {

  namespace algebra {

    template<typename T>
    bool op_contains(const algebra::NumericalSemiring&, T)
    {
      return true;
    }

    template<typename T, typename U>
    void op_in_mul(const algebra::NumericalSemiring&,
		   T& dst, U arg)
    {
      dst *= arg;
    }

    template<typename T, typename U>
    void op_in_add(const algebra::NumericalSemiring&,
		   T& dst, U arg)
    {
      dst += arg;
    }

    // FIXME: there should be specializations of op_add_traits and
    // op_mul_traits giving the type of the result depending on the
    // type of the arguments.

    template<typename T, typename U>
    T op_mul(const algebra::NumericalSemiring&, T a, U b)
    {
      return a * b;
    }

    template<typename T, typename U>
    T op_add(const algebra::NumericalSemiring&, T a, U b)
    {
      return a + b;
    }

    template<typename T>
    T identity_value(SELECTOR(algebra::NumericalSemiring), SELECTOR(T))
    {
      return T(1);
    }

    template<typename T>
    bool show_identity_value(SELECTOR(algebra::NumericalSemiring), SELECTOR(T))
    {
      return false;
    }

    template<typename T>
    T zero_value(SELECTOR(algebra::NumericalSemiring), SELECTOR(T))
    {
      return T(0);
    }

    template <class T>
    Element<algebra::NumericalSemiring, T>
    op_choose(const algebra::NumericalSemiring& set, SELECTOR(T))
    {
      return
	Element<algebra::NumericalSemiring, T>
	  (set, misc::random::generate<T>());
    }

    template<typename T>
    bool
    is_positive_semiring(SELECTOR(algebra::NumericalSemiring), SELECTOR(T))
    {
      return false;
    }

    /*-----------------------------.
    | specializations for integers |
    `-----------------------------*/

    inline
    bool
    op_can_choose_non_starable(const algebra::NumericalSemiring&,
				SELECTOR(int))
    {
      return true; // Every integer excepted Zero is non-starable
    }

    inline
    Element<algebra::NumericalSemiring, int>
    op_choose_starable(const algebra::NumericalSemiring& set, SELECTOR(int))
    {
      // 0 is the only one integer to be starable. So we have no choice !
      return Element<algebra::NumericalSemiring, int>(set, 0);
    }

    inline
    Element<algebra::NumericalSemiring, int>
    op_choose_non_starable(const algebra::NumericalSemiring& set,
			   SELECTOR(int))
    {
      int r = misc::random::generate<int>();
      if (!r)
	r = 1;
      return Element<algebra::NumericalSemiring, int>(set, r);
    }

    /*-----------------------------.
    | specializations for Booleans |
    `-----------------------------*/
    template <typename T>
    void op_in_mul(const algebra::NumericalSemiring&, bool& dst, bool src)
    {
      dst = dst && src;
    }

    inline bool op_mul(const algebra::NumericalSemiring&, bool a, bool b)
    {
      return a && b;
    }

    inline void op_in_add(const algebra::NumericalSemiring&,
			  bool& dst, bool src)
    {
      dst = dst || src;
    }

    inline bool op_add(const algebra::NumericalSemiring&, bool a, bool b)
    {
      return a || b;
    }

    inline bool identity_value(SELECTOR(algebra::NumericalSemiring),
			       SELECTOR(bool))
    {
      return true;
    }

    inline bool zero_value(SELECTOR(algebra::NumericalSemiring),
			   SELECTOR(bool))
    {
      return false;
    }

    inline bool op_starable(const algebra::NumericalSemiring&, bool)
    {
      return true;
    }

    inline void op_in_star(const algebra::NumericalSemiring&, bool& b)
    {
      b = true;
    }

    inline
    Element<algebra::NumericalSemiring, bool>
    op_choose_starable(const algebra::NumericalSemiring& set, SELECTOR(bool))
    {
      // Every Boolean is starable !
      return op_choose(set, SELECT(bool));
    }

    inline
    Element<algebra::NumericalSemiring, bool>
    op_choose_non_starable(const algebra::NumericalSemiring& set,
			   SELECTOR(bool))
    {
      assertion_(false, "Cannot choose non-starable boolean: all boolean are starable.");
      return Element<algebra::NumericalSemiring, bool>(set, false);
    }

    inline bool
    is_positive_semiring(SELECTOR(algebra::NumericalSemiring), SELECTOR(bool))
    {
      return true;
    }

    /*--------------------------------------------.
    | specialization for floating point numbers.  |
    `--------------------------------------------*/

    inline float op_sub(const algebra::NumericalSemiring&, const float& a, const float& b)
    {
      return a - b;
    }

    inline double op_sub(const algebra::NumericalSemiring&, const double& a, const double& b)
    {
      return a - b;
    }

    inline float op_div(const algebra::NumericalSemiring&, const float& a, const float& b)
    {
      return a / b;
    }

    inline double op_div(const algebra::NumericalSemiring&, const double& a, const double& b)
    {
      return a / b;
    }

    inline bool op_eq(const algebra::NumericalSemiring&, float& a, float& b)
    {
      return std::abs(a - b) < 0.00001;
    }

    inline bool op_eq(const algebra::NumericalSemiring&, double& a, double& b)
    {
      return std::abs(a - b) < 0.00001;
    }

    template<typename T>
    bool op_starable(const algebra::NumericalSemiring&, T v)
    {
      return v == 0;
    }

    inline bool op_starable(const algebra::NumericalSemiring&,
			     const float& f)
    {
      return (-1.0 < f) && (f < 1.0);
    }

    inline bool op_starable(const algebra::NumericalSemiring&,
			     const double& f)
    {
      return (-1.0 < f) && (f < 1.0);
    }

    inline void op_in_star(const algebra::NumericalSemiring&, float& f)
    {
      static_assertion(misc::limits<float>::has_infinity,
		       float_has_infinity);
      if (f < 1.0)
	f = (1.0 / (1.0 - f));
      else
	f = misc::limits<float>::infinity();
    }

    inline void op_in_star(const algebra::NumericalSemiring&, double& f)
    {
      if (f < 1.0)
	f = (1.0 / (1.0 - f));
      else
	assertion(! "star not defined.");
    }

    inline
    bool
    op_can_choose_non_starable(const algebra::NumericalSemiring&,
				SELECTOR(float))
    {
      return true; // Every float which is less than -1 or greater than 1 is
		   // non-starable.
    }

    inline
    Element<algebra::NumericalSemiring, float>
    op_choose_starable(const algebra::NumericalSemiring& set,
		       SELECTOR(float))
    {
      float res = misc::random::generate<float>(-1, 1);

      while (res == -1)
	res = misc::random::generate<float>(-1, 1);
      return
	Element<algebra::NumericalSemiring, float>
	  (set, res);
    }

    inline
    Element<algebra::NumericalSemiring, float>
    op_choose_non_starable(const algebra::NumericalSemiring& set,
			   SELECTOR(float))
    {
      float res = misc::random::generate<float>() * 1000.;
      while (op_starable(set, res))
	res = misc::random::generate<float>() * 1000.;
      return Element<algebra::NumericalSemiring, float>(set, res);
    }

    inline
    bool
    op_can_choose_non_starable(const algebra::NumericalSemiring&,
				SELECTOR(double))
    {
      return true; // Every float which is less than -1 or greater than 1 is
		   // non-starable.
    }

    inline
    Element<algebra::NumericalSemiring, double>
    op_choose_starable(const algebra::NumericalSemiring& set,
		       SELECTOR(double))
    {
      double res = misc::random::generate<double>(-1, 1);

      while (res == -1)
	res = misc::random::generate<double>(-1, 1);
      return
	Element<algebra::NumericalSemiring, double>
	  (set, res);
   }

    inline
    Element<algebra::NumericalSemiring, double>
    op_choose_non_starable(const algebra::NumericalSemiring& set,
			   SELECTOR(double))
    {
      double res = misc::random::generate<double>() * 1000.;
      while (op_starable(set, res))
	res = misc::random::generate<double>() * 1000.;
      return Element<algebra::NumericalSemiring, double>(set, res);
    }
    // FIXME: add some more operators as syntactic sugar


    /*------------------------------------.
    | specialization for rational numbers |
     `------------------------------------*/


    inline RationalNumber
    op_sub(const algebra::NumericalSemiring&, const RationalNumber& a, const RationalNumber& b)
    {
      return a - b;
    }

    inline RationalNumber
    op_div(const algebra::NumericalSemiring&, const RationalNumber& a, const RationalNumber& b)
    {
      return a / b;
    }


    inline algebra::RationalNumber
    identity_value(SELECTOR(algebra::NumericalSemiring),
		   SELECTOR(algebra::RationalNumber))
    {
      return algebra::RationalNumber(1);
    }

    inline algebra::RationalNumber
    zero_value(SELECTOR(algebra::NumericalSemiring),
	       SELECTOR(algebra::RationalNumber))
    {
      return algebra::RationalNumber(0);
    }

    inline bool
    op_starable(const algebra::NumericalSemiring&,
		const algebra::RationalNumber& r)
    {
      return std::abs(r.num_get()) < r.den_get ();
    }

    inline bool
    op_starable(const algebra::NumericalSemiring&,
		algebra::RationalNumber& r)
    {
      return std::abs(r.num_get()) < r.den_get ();
    }

    inline void op_in_star(const algebra::NumericalSemiring&,
			   algebra::RationalNumber& r)
    {
      if (std::abs(r.num_get()) < r.den_get ())
      {
	algebra::RationalNumber one = algebra::RationalNumber(1);
	r = one / (one - r);
      }
      else
	assertion(! "vcsn::algebra::RationalNumber: star not defined.");
    }

    inline
    bool
    op_can_choose_non_starable(const algebra::NumericalSemiring&,
				SELECTOR(algebra::RationalNumber))
    {
      return true; // Every rational number which is greater than 1 and
		   // less than -1 is non-starable
    }

    inline
    Element<algebra::NumericalSemiring, algebra::RationalNumber>
    op_choose_starable(const algebra::NumericalSemiring& set,
		       SELECTOR(algebra::RationalNumber))
    {
      algebra::RationalNumber min = algebra::RationalNumber(-1, 1);
      algebra::RationalNumber max = algebra::RationalNumber(1, 1);
      return
 	Element<algebra::NumericalSemiring, algebra::RationalNumber>
	(set, misc::random::generate<algebra::RationalNumber>(min, max));
   }

    inline
    Element<algebra::NumericalSemiring, algebra::RationalNumber>
    op_choose_non_starable(const algebra::NumericalSemiring& set,
			   SELECTOR(algebra::RationalNumber))
    {
      algebra::RationalNumber res;
      do
	{
	  res = misc::random::generate<algebra::RationalNumber> ();
	}
      while (res.den_get () >= std::abs(res.num_get ()));
      return Element<algebra::NumericalSemiring, algebra::RationalNumber> (set, res);
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_NUMERICAL_SEMIRING_HXX
