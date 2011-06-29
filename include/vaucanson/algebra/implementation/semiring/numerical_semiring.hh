// numerical_semiring.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2011 The Vaucanson Group.
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
# include <vaucanson/algebra/implementation/semiring/q_number.hh>

namespace vcsn {

  namespace algebra {

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
    bool show_identity_value(SELECTOR(algebra::NumericalSemiring), SELECTOR(T));

    template<typename T>
    T zero_value(SELECTOR(algebra::NumericalSemiring), SELECTOR(T));

    template <class T>
    Element<algebra::NumericalSemiring, T>
    op_choose(const algebra::NumericalSemiring& s, SELECTOR(T));

    template<typename T>
    bool
    is_positive_semiring(SELECTOR(algebra::NumericalSemiring), SELECTOR(T));

    /*-----------------------------.
    | specializations for integers |
    `-----------------------------*/

    bool
    op_can_choose_non_starable(const algebra::NumericalSemiring& set,
			       SELECTOR(int));

    Element<algebra::NumericalSemiring, int>
    op_choose_starable(const algebra::NumericalSemiring& set, SELECTOR(int));

    Element<algebra::NumericalSemiring, int>
    op_choose_non_starable(const algebra::NumericalSemiring& set,
			   SELECTOR(int));

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
    op_choose_non_starable(const algebra::NumericalSemiring& set,
			   SELECTOR(bool));

    inline bool
    is_positive_semiring(SELECTOR(algebra::NumericalSemiring), SELECTOR(bool));

    /*-------------------------.
    | goodies for real numbers |
    `-------------------------*/

    /* Operators only available for fields */
    inline float op_sub(const algebra::NumericalSemiring&, const float& a, const float& b);

    inline double op_sub(const algebra::NumericalSemiring&, const double& a, const double& b);

    inline float op_div(const algebra::NumericalSemiring&, const float& a, const float& b);

    inline double op_div(const algebra::NumericalSemiring&, const double& a, const double& b);
    /**/

    inline bool op_eq(const algebra::NumericalSemiring&, float& a, float& b);

    inline bool op_eq(const algebra::NumericalSemiring&, double& a, double& b);

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


    inline RationalNumber
    op_sub(const algebra::NumericalSemiring&, const RationalNumber&, const RationalNumber&);

    inline RationalNumber
    op_div(const algebra::NumericalSemiring&, const RationalNumber&, const RationalNumber&);


    inline algebra::RationalNumber
    identity_value(SELECTOR(algebra::NumericalSemiring),
		   SELECTOR(algebra::RationalNumber));


    inline algebra::RationalNumber
    zero_value(SELECTOR(algebra::NumericalSemiring),
	       SELECTOR(algebra::RationalNumber));

    inline
    bool op_starable(const algebra::NumericalSemiring& s, RationalNumber& v);

    inline bool op_starable(const algebra::NumericalSemiring& s,
			    const algebra::RationalNumber& r);

    inline void op_in_star(const algebra::NumericalSemiring& s,
			   algebra::RationalNumber& r);

    inline
    bool
    op_can_choose_non_starable(const algebra::NumericalSemiring& set,
			       SELECTOR(algebra::RationalNumber));

    inline
    Element<algebra::NumericalSemiring, algebra::RationalNumber>
    op_choose_starable(const algebra::NumericalSemiring& set,
		       SELECTOR(algebra::RationalNumber));

    inline
    Element<algebra::NumericalSemiring, algebra::RationalNumber>
    op_choose_non_starable(const algebra::NumericalSemiring& set,
			   SELECTOR(algebra::RationalNumber));

  } // algebra

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/algebra/implementation/semiring/numerical_semiring.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_NUMERICAL_SEMIRING_HH
