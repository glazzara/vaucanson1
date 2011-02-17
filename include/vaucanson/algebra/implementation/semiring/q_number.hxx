// q_semiring.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_SEMIRING_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_SEMIRING_HXX

// # include <cmath>
// # include <vaucanson/algebra/concept/semiring_base.hh>
# include <vaucanson/algebra/implementation/semiring/q_number.hh>
// # include <vaucanson/misc/random.hh>
// # include <vaucanson/misc/limits.hh>
// # include <vaucanson/misc/contract.hh>

#include <iostream>

# include <cassert>

namespace vcsn {

  namespace algebra {

    RationalNumber::RationalNumber ()
      : num_ (1),
	den_ (1)
    {
    }

    RationalNumber::RationalNumber (const int num)
      : num_ (num),
	den_ (1)
    {
    }

    RationalNumber::RationalNumber (const int num, const unsigned int den)
    {
      set_rational (num, den);
    }

    RationalNumber::RationalNumber (const RationalNumber& nb)
    {
      set_rational (nb.num_, nb.den_);
    }

    RationalNumber::~RationalNumber ()
    {
    }

    RationalNumber&
    RationalNumber::den_set (const unsigned int den)
    {
      set_rational (num_, den);
      return (*this);
    }

    RationalNumber&
    RationalNumber::set (const int num, const unsigned int den)
    {
      set_rational (num, den);
      return (*this);
    }

    RationalNumber&
    RationalNumber::set (const int num)
    {
      set_rational (num, 1);
      return (*this);
    }

    int
    RationalNumber::num_get () const
    {
      return num_;
    }

    unsigned int
    RationalNumber::den_get () const
    {
      return den_;
    }

    std::ostream&
    RationalNumber::print (std::ostream& ostr) const
    {
      return ostr << num_ << '/' << den_;
    }

    RationalNumber
    RationalNumber::operator+ (const RationalNumber& nb) const
    {
      return RationalNumber (num_ * nb.den_ + nb.num_ * den_, den_ * nb.den_);
    }

    RationalNumber
    RationalNumber::operator- (const RationalNumber& nb) const
    {
      return RationalNumber (num_ * nb.den_ - nb.num_ * den_, den_ * nb.den_);
    }

    RationalNumber
    RationalNumber::operator- () const
    {
      return RationalNumber (- num_, den_);
    }

    RationalNumber
    RationalNumber::operator* (const RationalNumber& nb) const
    {
      return RationalNumber (num_ * nb.num_, den_ * nb.den_);
    }

    RationalNumber
    RationalNumber::operator/ (const RationalNumber& nb) const
    {
      return RationalNumber (num_ * nb.den_, den_ * nb.num_);
    }

    RationalNumber&
    RationalNumber::operator+= (const RationalNumber& nb)
    {
      set_rational (num_ * nb.den_ + nb.num_ * den_, den_ * nb.den_);
      return (*this);
    }

    RationalNumber&
    RationalNumber::operator-= (const RationalNumber& nb)
    {
      set_rational (num_ * nb.den_ - nb.num_ * den_, den_ * nb.den_);
      return (*this);
    }

    RationalNumber&
    RationalNumber::operator*= (const RationalNumber& nb)
    {
      set_rational (num_ * nb.num_, den_ * nb.den_);
      return (*this);
    }

    RationalNumber&
    RationalNumber::operator/= (const RationalNumber& nb)
    {
      set_rational (num_ * nb.den_, den_ * nb.num_);
      return (*this);
    }

    bool
    RationalNumber::operator== (const RationalNumber& nb) const
    {
      return (den_ == nb.den_) && (num_ == nb.num_);
    }

    bool
    RationalNumber::operator!= (const RationalNumber& nb) const
    {
      return (den_ != nb.den_) || (num_ != nb.num_);
    }

    bool
    RationalNumber::operator< (const RationalNumber& nb) const
    {
      return num_ * nb.den_ < nb.num_ * den_;
    }

    bool
    RationalNumber::operator<= (const RationalNumber& nb) const
    {
      return num_ * nb.den_ <= nb.num_ * den_;
    }

    bool
    RationalNumber::operator> (const RationalNumber& nb) const
    {
      return num_ * nb.den_ > nb.num_ * den_;
    }

    bool
    RationalNumber::operator>= (const RationalNumber& nb) const
    {
      return num_ * nb.den_ >= nb.num_ * den_;
    }

    RationalNumber::operator int () const
    {
      return num_ / den_;
    }

    RationalNumber::operator float () const
    {
      return (static_cast<float> (num_)) / den_;
    }

    RationalNumber::operator double () const
    {
      return (static_cast<double> (num_)) / den_;
    }

    int
    RationalNumber::to_int () const
    {
      return num_ / den_;
    }

    float
    RationalNumber::to_float () const
    {
      return (static_cast<float> (num_)) / den_;
    }

    double
    RationalNumber::to_double () const
    {
      return (static_cast<double> (num_)) / den_;
    }


    void
    RationalNumber::set_rational (const int num, const unsigned den)
    {
      // assert or assertion
      assert (den != 0);

      unsigned int div = gcd (num, den);
      num_ = num / div;
      den_ = den / div;
      // assert or assertion
      assert (is_coprime (num_, den_));
    }

    void
    RationalNumber::set_rational ()
    {
      set_rational (num_, den_);
    }

    unsigned int
    gcd (unsigned int a, unsigned int b)
    {
      if (a)
      {
	int r;
	while (true)
	{
	  r = a % b;
	  if (! (r))
	    return b;
	  a = b;
	  b = r;
	}
      }
      return b;
    }

    unsigned int
    lcm (unsigned int a, unsigned int b)
    {
      unsigned int res = gcd (a, b);
      if (res)
	return a * b / res;
      return a * b;
    }

    bool
    is_coprime (unsigned int a, unsigned int b)
    {
      return 1 == gcd (a, b);
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_SEMIRING_HXX
