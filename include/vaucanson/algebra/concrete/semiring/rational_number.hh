// rational_number.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_ALGEBRA_CONCRETE_RATIONAL_NUMBER_HH
# define VCSN_ALGEBRA_CONCRETE_RATIONAL_NUMBER_HH

# include <iostream>

/**
 * @file   rational_number.hh
 * @brief  This file contains a Rational class declaration.
 *
 * @author Sarah O'Connor <sarah@lrde.epita.fr>
 * @see RationalNumber
 */

namespace vcsn
{
  namespace algebra
  {

    /** @addtogroup algebra */  /* @{ */
    /** @addtogroup semiring */ /* @{ */


    /**
     * @brief Rational numbers class.
     *
     * This is a rational numbers implementation.
     *
     * The way the constructor works ables us to work only on simplified
     * fractions. So, the numerator (num_) and denominator(denom_)
     * are always relatively prime.
     *
     * Even after operations, the obtained fraction is simplified.
     *
     * @author Sarah O'Connor <sarah@lrde.epita.fr>
     */

    class RationalNumber
    {
    public:

      /// Standard constructors.
      /** @{ */
      RationalNumber(int num, unsigned int denom);
      RationalNumber(const RationalNumber& nb);
      template <typename T>
      RationalNumber(const T num);
      /** @} */

      /// Accessors.
      /** @{ */
      const int&	num() const;
      const unsigned&	denom() const;

      /** @} */
      std::ostream&	print(std::ostream& ostr) const;

      /// Operators.
      /** @{ */
      RationalNumber	operator+(const RationalNumber& nb) const;
      RationalNumber	operator-(const RationalNumber& nb) const;
      RationalNumber	operator*(const RationalNumber& nb) const;
      RationalNumber	operator/(const RationalNumber& nb) const;
      RationalNumber&	operator+=(const RationalNumber& nb);
      RationalNumber&	operator-=(const RationalNumber& nb);
      RationalNumber&	operator*=(const RationalNumber& nb);
      RationalNumber&	operator/=(const RationalNumber& nb);
      /** @} */

      /**
       * Provide explicit cast operator.
       *
       * To_int and to_double allow us to get respectively an integer and
       * a double from the rational number. These numbers are obtained by
       * dividing the fraction's numerator and denominator.
       */
      /** @{ */
      int		to_int() const;
      double		to_double() const;
      /** @} */

    protected:
      int		num_;
      unsigned int	denom_;

      /**
       * Simplifies the fraction.
       *
       * Set_result is used to simplify the fraction. We use the GCD
       * (Greatest Common Divisor) algorithm. When there are no arguments,
       * it simply checks the numerator and denominator and modifies them
       * if needed.
       */
      /** @{ */
      RationalNumber&	set_result();
      RationalNumber&	set_result(int num, unsigned int denom);
      /** @} */
    };

    std::ostream& operator<<(std::ostream& ostr, const RationalNumber& nb);
    int		gcd(const int& a, const unsigned int& b);
    int		lcm(const int& a, const unsigned int& b);
    // FIXME: Other goodies for standard library.
    // FIXME: We might prefer to define gcd and lcm somewhere else.
    /** @} @} */

  } // end of namespace algebra
} // end of namespace vcsn

#ifndef VCSN_USE_INTERFACE_ONLY
# include <vaucanson/algebra/concrete/semiring/rational_number.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // RATIONAL_NUMBER_HH