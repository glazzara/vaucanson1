// numerical_semiring.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCRETE_SEMIRING_NUMERICAL_SEMIRING_HXX
# define VCSN_ALGEBRA_CONCRETE_SEMIRING_NUMERICAL_SEMIRING_HXX

# include <cmath>
# include <vaucanson/algebra/concept/semiring_base.hh>
# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/limits.hh>
# include <vaucanson/misc/contract.hh>

namespace vcsn {

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
        (set, utility::random::generate<T>());
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
    int r = utility::random::generate<int>();
    if (!r)
      r = 1;
    return Element<algebra::NumericalSemiring, int>(set, r);
  }

  /*-----------------------------.
  | specializations for Booleans |
  `-----------------------------*/
  template<typename T>
  void op_in_mul(const algebra::NumericalSemiring&,
			bool& dst, bool src)
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
    assertion(! "Cannot choose non-starable Boolean: that does not exist");
    return Element<algebra::NumericalSemiring, bool>(set, false);
  }

  /*--------------------------------------------.
  | specialization for floating point numbers.  |
  `--------------------------------------------*/

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
    static_assertion(utility::limits<float>::has_infinity,
		     float_has_infinity);
    if (f < 1.0)
      f = (1.0 / (1.0 - f));
    else
      f = utility::limits<float>::infinity();
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
    return
      Element<algebra::NumericalSemiring, float>
        (set, utility::random::generate<float>());
  }

  inline
  Element<algebra::NumericalSemiring, float>
  op_choose_non_starable(const algebra::NumericalSemiring& set,
			 SELECTOR(float))
  {
    return
      Element<algebra::NumericalSemiring, float>
        (set, utility::random::generate<float>() * 1000. + 1.0);
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
    return
      Element<algebra::NumericalSemiring, double>
        (set, utility::random::generate<double>());
  }

  inline
  Element<algebra::NumericalSemiring, double>
  op_choose_non_starable(const algebra::NumericalSemiring& set,
			 SELECTOR(double))
  {
    return
      Element<algebra::NumericalSemiring, double>
        (set, utility::random::generate<double>() * 1000. + 1.0);
  }
  // FIXME: add some more operators as syntactic sugar


  /*------------------------------------.
  | specialization for rational numbers |
   `------------------------------------*/

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

  inline bool op_starable(const algebra::NumericalSemiring&,
			  const algebra::RationalNumber& r)
  {
    int denom = r.denom();
    return abs(r.num()) < denom;
  }

  inline void op_in_star(const algebra::NumericalSemiring&,
			 algebra::RationalNumber& r)
  {
    int denom = r.denom();
    algebra::RationalNumber one = algebra::RationalNumber(1, 1);
    if (denom > abs(r.num()))
      r = (one / (r - one));
    else
      assertion(! "star not defined.");
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
        (set, utility::random::generate<algebra::RationalNumber>(min, max));
  }

  inline
  Element<algebra::NumericalSemiring, algebra::RationalNumber>
  op_choose_non_starable(const algebra::NumericalSemiring& set,
			 SELECTOR(algebra::RationalNumber))
  {
    algebra::RationalNumber res = algebra::RationalNumber(1, 1);
    int denom;
    do
      {
	res = utility::random::generate<algebra::RationalNumber>();
	denom = res.denom();
      }
    while (denom > abs(res.num()));
    return
      Element<algebra::NumericalSemiring, algebra::RationalNumber>
      (set, res);
  }

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_SEMIRING_NUMERICAL_SEMIRING_HXX
