// rational_number.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGEBRA_CONCRETE_SEMIRING_RATIONAL_NUMBER_HXX
# define VCSN_ALGEBRA_CONCRETE_SEMIRING_RATIONAL_NUMBER_HXX

# include <vaucanson/misc/contract.hh>
# include <vaucanson/misc/limits.hh>
# include <cmath>

/**
 * @file   rational_number.hxx
 * @brief  This file contains a Rational class implementation.
 *
 * @author Sarah O'Connor <sarah@lrde.epita.fr>
 */

namespace vcsn
{
  namespace algebra
  {
    // Default constructor.
    inline
    RationalNumber::RationalNumber(int num, unsigned int denom):
      num_ (num),
      denom_ (denom)
    {
      precondition(denom != 0);
      set_result();
    }

    inline
    RationalNumber::RationalNumber():num_ (0), denom_ (1)
    {
    }

    // Copy constructor.
    inline
    RationalNumber::RationalNumber(const RationalNumber& nb) :
      num_ (nb.num_), denom_ (nb.denom_)
    {
      set_result();
    }


    template <typename T>
    RationalNumber::RationalNumber(const T num) : num_ (num),
						  denom_ (T(1))
    {
    }

    inline
    const int&		RationalNumber::num() const
    {
      return num_;
    }

    inline
    const unsigned int&	RationalNumber::denom() const
    {
      return denom_;
    }

    inline
    RationalNumber&	RationalNumber::set_result(int num,unsigned int denom)
    {
      const int n = gcd(abs(num), denom);
      num_ = num/n;
      denom_ = denom/n;
      return *this;
    }

    inline
    RationalNumber&	RationalNumber::set_result()
    {
      const int n = gcd(abs(num_), denom_);
      num_ /= n;
      denom_ /= n;
      return *this;
    }

    inline
    std::ostream&	RationalNumber::print(std::ostream& ostr) const
    {
      return ostr << num_ << "/" << denom_;
    }

    // Operators.

    inline
    RationalNumber
    RationalNumber::operator+(const RationalNumber& nb) const
    {
      const int m = lcm(denom_, nb.denom());

      return RationalNumber(num_ * m / denom_ + nb.num() * m / nb.denom(), m);
    }

    inline
    RationalNumber
    RationalNumber::operator-(const RationalNumber& nb) const
    {
      const int m = lcm(denom_, nb.denom());

      return RationalNumber(num_ * m / denom_ - nb.num() * m / nb.denom(), m);
    }

    inline
    RationalNumber
    RationalNumber::operator-() const
    {
      return RationalNumber(-num_, denom_);
    }

    inline
    RationalNumber
    RationalNumber::operator*(const RationalNumber& nb) const
    {
      return RationalNumber(num_ * nb.num(), denom_ * nb.denom());
    }

    inline
    RationalNumber
    RationalNumber::operator/(const RationalNumber& nb) const
    {
      if (nb.num() < 0)
	return RationalNumber(-num_ * nb.denom(), denom_ * -nb.num());
      return RationalNumber(num_ * nb.denom(), denom_ * nb.num());
    }

    inline
    RationalNumber&	RationalNumber::operator+=(const RationalNumber& nb)
    {
      const int m = lcm(denom_, nb.denom());
      return set_result(num_ * m / denom_ + nb.num() * m / nb.denom(), m);
    }

    inline
    RationalNumber&	RationalNumber::operator-=(const RationalNumber& nb)
    {
      const int m = lcm(denom_, nb.denom());
      return set_result(num_ * m / denom_ - nb.num() * m / nb.denom(), m);
    }

    inline
    RationalNumber&	RationalNumber::operator*=(const RationalNumber& nb)
    {
      return set_result(num_ * nb.num(), denom_ * nb.denom());
    }

    inline
    RationalNumber&	RationalNumber::operator/=(const RationalNumber& nb)
    {
      if (nb.num() < 0)
	return set_result(-num_ * nb.denom(), denom_ * -nb.num());
      return set_result(num_ * nb.denom(), denom_ * nb.num());
    }

    inline
    bool	RationalNumber::operator<(const RationalNumber& nb) const
    {
      const int m = lcm(denom_, nb.denom());
      int num1 = num_ * (m / denom_);
      int num2 = nb.num() * (m / nb.denom());
      return num1 < num2;
    }

    inline
    bool	RationalNumber::operator>(const RationalNumber& nb) const
    {
      const int m = lcm(denom_, nb.denom());
      int num1 = num_ * (m / denom_);
      int num2 = nb.num() * (m / nb.denom());
      return num1 > num2;
    }

    inline
    bool	RationalNumber::operator<=(const RationalNumber& nb) const
    {
      const int m = lcm(denom_, nb.denom());
      int num1 = num_ * (m / denom_);
      int num2 = nb.num() * (m / nb.denom());
      return num1 <= num2;
    }

    inline
    bool	RationalNumber::operator>=(const RationalNumber& nb) const
    {
      const int m = lcm(denom_, nb.denom());
      int num1 = num_ * (m / denom_);
      int num2 = nb.num() * (m / nb.denom());
      return num1 >= num2;
    }

    inline
    bool	RationalNumber::operator==(const RationalNumber& nb) const
    {
      const int m = lcm(denom_, nb.denom());
      int num1 = num_ * (m / denom_);
      int num2 = nb.num() * (m / nb.denom());
      return num1 == num2;
    }

    inline
    bool	RationalNumber::operator!=(const RationalNumber& nb) const
    {
      const int m = lcm(denom_, nb.denom());
      int num1 = num_ * (m / denom_);
      int num2 = nb.num() * (m / nb.denom());
      return num1 != num2;
    }

    // Goodies.

    inline
    int		RationalNumber::to_int() const
    {
      precondition(denom_<static_cast<unsigned>(utility::limits<int>::max()));
      return num_ / static_cast<int> (denom_);
    }

    inline
    double	RationalNumber::to_double() const
    {
      return static_cast<double> (num_) / denom_;
    }

    inline
    std::ostream& operator<<(std::ostream& ostr, const RationalNumber& nb)
    {
      return nb.print(ostr);
    }

    inline
    int	gcd(int a, unsigned int b)
    {
      int n = b;

      while (n != 0)
	{
	  int t = a % n;
	  a = n;
	  n = t;
	}
      return a;
    }

    inline
    int	lcm(int a, unsigned int b)
    {
      int d;
      if (!a || !b || !(d = gcd(a, b)))
	return 0;
      return a * b / d;
    }

  }
}

#endif //VCSN_ALGEBRA_CONCRETE_RATIONAL_NUMBER_HXX
