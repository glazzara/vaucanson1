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

/** @addtogroup algebra *//* @{ */
/** @addtogroup semiring *//* @{ */
/**
 * @file   q_number.hh
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

  /** @addtogroup algebra *//* @{ */
  namespace algebra
  {
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

    template<typename IntType>
    class TRationalNumber
    {
    public:
      /// @name Standart constructors.
      /// @{
      /// Default constructor.
      inline
      TRationalNumber ();
      /// Constructor define numerator. Denominator set at 1.
      inline
      TRationalNumber (const IntType num);
      /// Constructor define numerator and denominator.
      inline
      TRationalNumber (const IntType num, const IntType den);
      /// Copy Constructor
      inline
      TRationalNumber (const TRationalNumber<IntType>& nb);
      // Object destructor.
      inline
      ~TRationalNumber ();
      ///  @}
    public:
      /// @name Setters
      /// @{
      /// Set the numerator and the denominator.
      inline
      TRationalNumber& set (const IntType num, const IntType den = 1);
      /// @}
      /// @name Accessors
      /// @{
      /// Get the numerator.
      inline
      IntType num_get () const;
      /// Get the denominator.
      inline
      IntType den_get () const;
      /// Printing method.
      inline
      std::ostream& print (std::ostream& ostr) const;

      /// @}
    public:
      /// @name Usual Operator
      /// @{
      /// Usual Arithemetics Operator.
      inline
      TRationalNumber<IntType> operator+ (const TRationalNumber<IntType>& nb) const;
      inline
      TRationalNumber<IntType> operator- (const TRationalNumber<IntType>& nb) const;
      inline
      TRationalNumber<IntType> operator- () const;
      inline
      TRationalNumber<IntType> operator* (const TRationalNumber<IntType>& nb) const;
      inline
      TRationalNumber<IntType> operator/ (const TRationalNumber<IntType>& nb) const;

      inline
      TRationalNumber<IntType>& operator+= (const TRationalNumber<IntType>& nb);
      inline
      TRationalNumber<IntType>& operator-= (const TRationalNumber<IntType>& nb);
      inline
      TRationalNumber<IntType>& operator*= (const TRationalNumber<IntType>& nb);
      inline
      TRationalNumber<IntType>& operator/= (const TRationalNumber<IntType>& nb);

      /// Usual Boolean Opertor.
      inline
      bool operator== (const TRationalNumber<IntType>& nb) const;
      inline
      bool operator!= (const TRationalNumber<IntType>& nb) const;
      inline
      bool operator< (const TRationalNumber<IntType>& nb) const;
      inline
      bool operator<= (const TRationalNumber<IntType>& nb) const;
      inline
      bool operator> (const TRationalNumber<IntType>& nb) const;
      inline
      bool operator>= (const TRationalNumber<IntType>& nb) const;

      // @}

      /// @name Cast function
      /// @{
      /// Implicit cast
      // operator int () const;
      //operator float () const;
      inline
      operator double () const;

      /// Explecit cast
      inline
      IntType to_integer () const;
      inline
      float to_float () const;
      inline
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
      inline void set_rational (const IntType num, const IntType den);
      inline void set_unsafe_rational (const IntType num, const IntType den);
      /// @}
    protected:
      /// @name TRationalNumber<IntType> attributs
      /// @{
      /// Fraction's numerator.
      IntType num_;
      /// Fraction's denominator.
      IntType den_;
      //// @}
    }; // TRationalNumber<IntType>

    template<typename IntType>
    inline
    std::ostream& operator<< (std::ostream&, const TRationalNumber<IntType>&);

    template<typename IntType>
    inline
    std::istream& operator>> (std::istream&, TRationalNumber<IntType>&);

    typedef TRationalNumber<long long> RationalNumber;

    /// @}
  } // !algebra

  /// @}
} // !vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/semiring/q_number.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HH
