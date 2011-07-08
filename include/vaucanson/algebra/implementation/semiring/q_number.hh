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

    template<typename NUMType, typename DENType>
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
      TRationalNumber (const NUMType num);
      /// Constructor define numerator and denominator.
      inline
      TRationalNumber (const NUMType num, const DENType den);
      /// Copy Constructor
      inline
      TRationalNumber (const TRationalNumber<NUMType, DENType>& nb);
      // Object destructor.
      inline
      ~TRationalNumber ();
      ///  @}
    public:
      /// @name Setters
      /// @{
      /// Set the numerator and the denominator.
      inline
      TRationalNumber& set (const NUMType num, const DENType den = 1);
      /// @}
      /// @name Accessors
      /// @{
      /// Get the numerator.
      inline
      NUMType num_get () const;
      /// Get the denominator.
      inline
      DENType den_get () const;
      /// Printing method.
      inline
      std::ostream& print (std::ostream& ostr) const;

      /// @}
    public:
      /// @name Usual Operator
      /// @{
      /// Usual Arithemetics Operator.
      inline
      TRationalNumber<NUMType, DENType> operator+ (const TRationalNumber<NUMType, DENType>& nb) const;
      inline
      TRationalNumber<NUMType, DENType> operator- (const TRationalNumber<NUMType, DENType>& nb) const;
      inline
      TRationalNumber<NUMType, DENType> operator- () const;
      inline
      TRationalNumber<NUMType, DENType> operator* (const TRationalNumber<NUMType, DENType>& nb) const;
      inline
      TRationalNumber<NUMType, DENType> operator/ (const TRationalNumber<NUMType, DENType>& nb) const;

      inline
      TRationalNumber<NUMType, DENType>& operator+= (const TRationalNumber<NUMType, DENType>& nb);
      inline
      TRationalNumber<NUMType, DENType>& operator-= (const TRationalNumber<NUMType, DENType>& nb);
      inline
      TRationalNumber<NUMType, DENType>& operator*= (const TRationalNumber<NUMType, DENType>& nb);
      inline
      TRationalNumber<NUMType, DENType>& operator/= (const TRationalNumber<NUMType, DENType>& nb);

      /// Usual Boolean Opertor.
      inline
      bool operator== (const TRationalNumber<NUMType, DENType>& nb) const;
      inline
      bool operator!= (const TRationalNumber<NUMType, DENType>& nb) const;
      inline
      bool operator< (const TRationalNumber<NUMType, DENType>& nb) const;
      inline
      bool operator<= (const TRationalNumber<NUMType, DENType>& nb) const;
      inline
      bool operator> (const TRationalNumber<NUMType, DENType>& nb) const;
      inline
      bool operator>= (const TRationalNumber<NUMType, DENType>& nb) const;

      // @}

      /// @name Cast function
      /// @{
      /// Implicit cast
      // operator int () const;
      inline
      operator float () const;
      // operator double () const;

      /// Explecit cast
      inline
      int to_int () const;
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
      inline void set_rational (const NUMType num, const DENType den);
      inline void set_unsafe_rational (const NUMType num, const DENType den);
      /// @}
    protected:
      /// @name TRationalNumber<NUMType, DENType> attributs
      /// @{
      /// Fraction's numerator.
      NUMType num_;
      /// Fraction's denominator.
      DENType den_;
      //// @}
    }; // TRationalNumber<NUMType, DENType>

    template<typename NUMType, typename DENType>
    inline
    std::ostream& operator<< (std::ostream&, const TRationalNumber<NUMType, DENType>&);

    template<typename NUMType, typename DENType>
    inline
    std::istream& operator>> (std::istream&, TRationalNumber<NUMType, DENType>&);

    typedef TRationalNumber<long long, unsigned long long> RationalNumber;

    /// @}
  } // !algebra

  /// @}
} // !vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/semiring/q_number.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HH
