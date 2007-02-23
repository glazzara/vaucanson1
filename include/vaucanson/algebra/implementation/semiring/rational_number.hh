// rational_number.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_RATIONAL_NUMBER_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_RATIONAL_NUMBER_HH

# include <iostream>

# include <vaucanson/misc/limits.hh>

/** @addtogroup algebra *//* @{ */
/** @addtogroup semiring *//* @{ */
/**
 * @file   rational_number.hh
 *
 * RationalNumber class declaration.
 *
 * @author Sarah O'Connor <sarah@lrde.epita.fr>
 * @see RationalNumber
 */
/** @} */
/** @} */

namespace vcsn
{
  namespace algebra
  {

    /** @addtogroup algebra *//* @{ */
    /** @addtogroup semiring *//* @{ */

    /**
     * Rational numbers class.
     *
     * This is a rational numbers implementation.
     *
     * The way the constructor works ables us to work only on simplified
     * fractions. So, the numerator (num_) and denominator (denom_)
     * are always relatively prime.
     *
     * Even after operations, the obtained fraction is simplified.
     *
     * @author Sarah O'Connor <sarah@lrde.epita.fr>
     */

    class RationalNumber
    {
      public:

	/// @name Standard constructors.
	///@{
	/// Constructor from numerator and denominator.
	RationalNumber (int num, unsigned int denom);
	/// Default constructor. Initialize to zero.
	RationalNumber ();
	/// Copy constructor.
	RationalNumber (const RationalNumber& nb);
	/**
	 * Generic constructor.
	 *
	 * @pre
	 * - T should be implicitly convertible into an integer representation.
	 * - T should be implicitly constructible from an integer.
	 * - T should conform the following prerequisite:
	 *	int (T (n)) / int (T (1)) == n
	 */
	template <typename T>
	explicit RationalNumber (const T num);
	///@}

	/// @name Accessors
	///@{
	/// Get the numerator.
	const int& num () const;
	/// Get the denominator.
	const unsigned& denom () const;
	///@}

	std::ostream&	print (std::ostream& ostr) const;

	/// @name Usual Operators.
	///@{
	/// Usual numerical operator.
	RationalNumber	operator+ (const RationalNumber& nb) const;
	RationalNumber	operator- (const RationalNumber& nb) const;
	RationalNumber	operator- () const;
	RationalNumber	operator* (const RationalNumber& nb) const;
	RationalNumber	operator/ (const RationalNumber& nb) const;

	RationalNumber&	operator+= (const RationalNumber& nb);
	RationalNumber&	operator-= (const RationalNumber& nb);
	RationalNumber&	operator*= (const RationalNumber& nb);
	RationalNumber&	operator/= (const RationalNumber& nb);

	bool operator<  (const RationalNumber& nb) const;
	bool operator>  (const RationalNumber& nb) const;
	bool operator<= (const RationalNumber& nb) const;
	bool operator>= (const RationalNumber& nb) const;
	bool operator== (const RationalNumber& nb) const;
	bool operator!= (const RationalNumber& nb) const;
	///@}

	/// @name Type conversion methods.
	///@{
	/**
	 * Provide Explicit cast operator.
	 *
	 * to_int() and to_double() allow us  to get respectively
	 * an  integer and  a  double from  the	 rational number.  These
	 * numbers are obtained by dividing the fraction's numerator and
	 * denominator.
	 */
	int    to_int () const;
	double to_double () const;
	///@}

      protected:
	int num_;
	unsigned int denom_;

	/// @name Fraction simplification
	///@{
	/**
	 * Simplifies the fraction.
	 *
	 * set_result() is used to simplify the fraction. We use the
	 * GCD (Greatest  Common Divisor)  algorithm. When there  are no
	 * arguments, it simply checks the numerator and denominator and
	 * modifies them if needed.
	 */
	RationalNumber&	set_result ();
	RationalNumber&	set_result (int num, unsigned int denom);
	///@}
    };

    // Provides generic operators on rational (calls the explicit generic
    // constructor for rational).
# define RATIONAL_NUMBER_OPERATOR(type, op)			\
    template <class T>						\
    type							\
    operator op (const RationalNumber& nb, const T nb2)		\
    {								\
      return nb op RationalNumber (nb2);			\
    }								\
								\
    template <class T>						\
    type							\
    operator op (const T nb2, const RationalNumber& nb)		\
    {								\
      return RationalNumber (nb2) op nb;			\
    }

    RATIONAL_NUMBER_OPERATOR (bool, <);
    RATIONAL_NUMBER_OPERATOR (bool, <=);
    RATIONAL_NUMBER_OPERATOR (bool, >);
    RATIONAL_NUMBER_OPERATOR (bool, >=);
    RATIONAL_NUMBER_OPERATOR (bool, ==);
    RATIONAL_NUMBER_OPERATOR (bool, !=);

    RATIONAL_NUMBER_OPERATOR (RationalNumber, +);
    RATIONAL_NUMBER_OPERATOR (RationalNumber, -);
    RATIONAL_NUMBER_OPERATOR (RationalNumber, *);
    RATIONAL_NUMBER_OPERATOR (RationalNumber, /);

# undef RATIONAL_NUMBER_OPERATOR


# define RATIONAL_NUMBER_IN_PLACE_OPERATOR(op)				\
    template <class T>							\
    RationalNumber&							\
    operator op (RationalNumber& nb, const T nb2)			\
    {									\
      return nb op RationalNumber (nb2);				\
    }

    RATIONAL_NUMBER_IN_PLACE_OPERATOR (+=);
    RATIONAL_NUMBER_IN_PLACE_OPERATOR (-=);
    RATIONAL_NUMBER_IN_PLACE_OPERATOR (*=);
    RATIONAL_NUMBER_IN_PLACE_OPERATOR (/=);

# undef RATIONAL_NUMBER_IN_PLACE_OPERATOR

    // @todo FIXME: Add other goodies for standard library.
    std::ostream& operator<< (std::ostream& ostr, const RationalNumber& nb);

    // @todo FIXME: We might prefer to define gcd and lcm somewhere else.
    int gcd (int a, unsigned int b);
    int lcm (int a, unsigned int b);

    /** @} */
    /** @} */

  } // End of namespace algebra.
} // End of namespace vcsn.

namespace std
{
  template <>
  struct numeric_limits< ::vcsn::algebra::RationalNumber >
  {
      static inline ::vcsn::algebra::RationalNumber min ();
      static inline ::vcsn::algebra::RationalNumber max ();
  };

} // End of namespace std.

/// @bug FIXME: misc::limits should be removed, or std::numeric_limits should
/// not be used/specialized.
namespace vcsn
{
  namespace misc
  {
    template <>
    struct limits< ::vcsn::algebra::RationalNumber > :
	public std::numeric_limits< ::vcsn::algebra::RationalNumber >
    {
    };
  } // misc
} // vcsn

#  include <vaucanson/algebra/implementation/semiring/rational_number.hxx>

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_RATIONAL_NUMBER_HH
