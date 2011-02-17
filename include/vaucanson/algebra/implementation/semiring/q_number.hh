// q_number.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HH

#include <iostream>

// # include <vaucanson/algebra/concept/q_number.hh>

/** @addtogroup algebra *//* @{ */
/** @addtogroup semiring *//* @{ */
/**
 * @file   rational_number.hh
 *
 * RationalNumber class declaration.
 *
 * @author David Moreira <david.moreira@epita.fr>
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
     * Implementation of rational numbers
     *
     * Constructors are able to product simplified rational
     * number. 
     *
     * Operation maintain num_ and den_ coprime.
     *
     * num_ and den_ are always coprime
     *
     * @author David Moreira <david.moreira@epita.fr>
     */

    class RationalNumber
    {
    public:
      /// @name Standart constructors.
      /// @{
      /// Default constructor.
      RationalNumber ();
      /// Constructor define numerator. Denominator set at 1.
      RationalNumber (const int num);
      /// Constructor define numerator and denominator.
      RationalNumber (const int num, const unsigned int den);
      /// Copy Constructor
      RationalNumber (const RationalNumber& nb);
      // Object destructor.
      ~RationalNumber ();
      ///  @}
    public:
      /// @name Setters
      /// @{
      /// Set the numerator and the denominator.
      RationalNumber& set (const int num, const unsigned int den);
      /// Set the numerator.
      RationalNumber& set (const int num);
      /// Set the denominator.
      RationalNumber& den_set (const unsigned int den);
      /// @}
      /// @name Accessors
      /// @{
      /// Get the numerator.
      int num_get () const;
      /// Get the denominator.
      unsigned int den_get () const;
      /// Printing method.
      std::ostream& print (std::ostream& ostr) const;
      /// @}
    public:
      /// @name Usual Operator
      /// @{
      /// Usual Arithemetics Operator.
      RationalNumber operator+ (const RationalNumber& nb) const;
      RationalNumber operator- (const RationalNumber& nb) const;
      RationalNumber operator- () const;
      RationalNumber operator* (const RationalNumber& nb) const;
      RationalNumber operator/ (const RationalNumber& nb) const;

      RationalNumber& operator+= (const RationalNumber& nb);
      RationalNumber& operator-= (const RationalNumber& nb);
      RationalNumber& operator*= (const RationalNumber& nb);
      RationalNumber& operator/= (const RationalNumber& nb);

      /// Usual Boolean Opertor.
      bool operator== (const RationalNumber& nb) const;
      bool operator!= (const RationalNumber& nb) const;
      bool operator< (const RationalNumber& nb) const;
      bool operator<= (const RationalNumber& nb) const;
      bool operator> (const RationalNumber& nb) const;
      bool operator>= (const RationalNumber& nb) const;
      // @}

      /// @name Cast function
      /// @{
      /// Implicit cast
      operator int () const;
      operator float () const;
      operator double () const;

      /// Explecit cast
      int to_int () const;
      float to_float () const;
      double to_double () const;
      /// @}
    protected:
      /// @name Fraction simplification
      /// @{
      /**
       * Simplifies the fraction
       * Procedure set and simplifies the num_ and the den_ fraction.
       *
       * Set the num_ and the den_ with the following property :
       * gcd (num_, den_) = 1
       *
       */
      inline void set_rational ();
      inline void set_rational (const int num, const unsigned int den);
      /// @}
    protected:
      /// @name RationalNumber attributs
      /// @{
      /// Fraction's numerator.
      int num_;
      /// Fraction's denominator.
      unsigned int den_;
      //// @}
    }; // RationalNumber

    /// @name Prime Number Operator
    // @{
    /// @todo FIXME: We might prefer to define gcd and lcm somewhere else.
    /// Greatest common divisor.
    unsigned int gcd (unsigned int a, unsigned int b);
    /// Least common multiple.
    unsigned int lpcm (unsigned int a, unsigned int b);
    /// Coprime between to int.
    inline bool is_coprime (unsigned int a, unsigned int b);
    /// @}
  } // algebra

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/semiring/q_number.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HH
