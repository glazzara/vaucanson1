// numerical_semiring.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_NUMERICAL_SEMIRING_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_NUMERICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/numerical_semiring.hh>
# include <vaucanson/algebra/implementation/semiring/rational_number.hh>

namespace vcsn {

  template<typename T>
  bool op_contains(const algebra::NumericalSemiring& s, T c);

  template<typename T, typename U>
  void op_in_mul(const algebra::NumericalSemiring& s1, T& dst, U arg);

  template<typename T, typename U>
  void op_in_add(const algebra::NumericalSemiring& s1, T& dst, U arg);

  template<typename T, typename U>
  T op_mul(const algebra::NumericalSemiring& s, T a, U b);

  template<typename T, typename U>
  T op_add(const algebra::NumericalSemiring& s, T a, U b);

  template<typename T>
  T identity_value(SELECTOR(algebra::NumericalSemiring), SELECTOR(T));

  template<typename T>
  T zero_value(SELECTOR(algebra::NumericalSemiring), SELECTOR(T));

  template <class T>
  Element<algebra::NumericalSemiring, T>
  op_choose(const algebra::NumericalSemiring& s, SELECTOR(T));

  /*-----------------------------.
  | specializations for integers |
  `-----------------------------*/

  bool
  op_can_choose_non_starable(const algebra::NumericalSemiring& set, SELECTOR(int));

  Element<algebra::NumericalSemiring, int>
  op_choose_starable(const algebra::NumericalSemiring& set, SELECTOR(int));

  Element<algebra::NumericalSemiring, int>
  op_choose_non_starable(const algebra::NumericalSemiring& set, SELECTOR(int));

  /*-----------------------------.
  | specializations for Booleans |
  `-----------------------------*/
  template<typename T>
  void op_in_mul(const algebra::NumericalSemiring& s1,
			bool& dst, bool src);

  inline bool op_mul(const algebra::NumericalSemiring& s, bool a, bool b);

  inline void op_in_add(const algebra::NumericalSemiring& s1,
			bool& dst, bool src);

  inline bool op_add(const algebra::NumericalSemiring& s, bool a, bool b);

  inline bool identity_value(SELECTOR(algebra::NumericalSemiring),
			     SELECTOR(bool));

  inline bool zero_value(SELECTOR(algebra::NumericalSemiring),
			 SELECTOR(bool));

  inline bool op_starable(const algebra::NumericalSemiring& s, bool b);

  inline void op_in_star(const algebra::NumericalSemiring& s, bool& b);

  Element<algebra::NumericalSemiring, bool>
  op_choose_starable(const algebra::NumericalSemiring& set, SELECTOR(bool));

  Element<algebra::NumericalSemiring, bool>
  op_choose_non_starable(const algebra::NumericalSemiring& set, SELECTOR(bool));

  /*-------------------------.
  | goodies for real numbers |
  `-------------------------*/
  template<typename T>
  bool op_starable(const algebra::NumericalSemiring& s, T v);

  inline bool op_starable(const algebra::NumericalSemiring& s,
			  const float& f);

  inline bool op_starable(const algebra::NumericalSemiring& s,
			  const double& f);

  inline void op_in_star(const algebra::NumericalSemiring& s, float& f);

  inline void op_in_star(const algebra::NumericalSemiring& s, double& f);

  bool
  op_can_choose_non_starable(const algebra::NumericalSemiring& set,
			      SELECTOR(float));

  Element<algebra::NumericalSemiring, float>
  op_choose_starable(const algebra::NumericalSemiring& set,
		     SELECTOR(float));

  Element<algebra::NumericalSemiring, float>
  op_choose_non_starable(const algebra::NumericalSemiring& set,
			 SELECTOR(float));

  bool
  op_can_choose_non_starable(const algebra::NumericalSemiring& set,
			      SELECTOR(double));

  Element<algebra::NumericalSemiring, double>
  op_choose_starable(const algebra::NumericalSemiring& set,
		     SELECTOR(double));

  Element<algebra::NumericalSemiring, double>
  op_choose_non_starable(const algebra::NumericalSemiring& set,
			 SELECTOR(double));

  /*-------------------------------------.
  | specializations for rational numbers |
  `-------------------------------------*/

  inline algebra::RationalNumber
  identity_value(SELECTOR(algebra::NumericalSemiring),
		 SELECTOR(algebra::RationalNumber));

  inline algebra::RationalNumber
  zero_value(SELECTOR(algebra::NumericalSemiring),
	     SELECTOR(algebra::RationalNumber));

  template<typename T>
  bool op_starable(const algebra::NumericalSemiring& s, T v);

  inline bool op_starable(const algebra::NumericalSemiring& s,
			  const algebra::RationalNumber& r);

  inline void op_in_star(const algebra::NumericalSemiring& s,
			 algebra::RationalNumber& r);

  bool
  op_can_choose_non_starable(const algebra::NumericalSemiring& set,
			     SELECTOR(algebra::RationalNumber));

  Element<algebra::NumericalSemiring, algebra::RationalNumber>
  op_choose_starable(const algebra::NumericalSemiring& set,
		     SELECTOR(algebra::RationalNumber));

  Element<algebra::NumericalSemiring, algebra::RationalNumber>
  op_choose_non_starable(const algebra::NumericalSemiring& set,
			 SELECTOR(algebra::RationalNumber));

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/implementation/semiring/numerical_semiring.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_NUMERICAL_SEMIRING_HH
