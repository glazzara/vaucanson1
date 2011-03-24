// q_number.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HXX

# include <vaucanson/algebra/implementation/semiring/q_number.hh>
# include <vaucanson/misc/algebra.hh>
# include <vaucanson/misc/contract.hh>

# include <iostream>
# include <cassert>

namespace vcsn {

  namespace algebra {

    inline
    RationalNumber::RationalNumber ()
      : num_ (0), // 0 or 1
	den_ (1)
    {
    }

    inline
    RationalNumber::RationalNumber (const int num)
      : num_ (num),
	den_ (1)
    {
    }

    inline
    RationalNumber::RationalNumber (const int num, const unsigned int den)
    {
      set_rational (num, den);
    }

    inline
    RationalNumber::RationalNumber (const RationalNumber& nb)
    {
      set_rational (nb.num_, nb.den_);
    }

    inline
    RationalNumber::~RationalNumber ()
    {
    }

    inline
    RationalNumber&
    RationalNumber::den_set (const unsigned int den)
    {
      set_rational (num_, den);
      return (*this);
    }

    inline
    RationalNumber&
    RationalNumber::set (const int num, const unsigned int den)
    {
      set_rational (num, den);
      return (*this);
    }

    inline
    RationalNumber&
    RationalNumber::set (const int num)
    {
      set_rational (num, 1);
      return (*this);
    }

    inline
    int
    RationalNumber::num_get () const
    {
      return num_;
    }

    inline
    unsigned int
    RationalNumber::den_get () const
    {
      return den_;
    }

    inline
    std::ostream&
    RationalNumber::print (std::ostream& ostr) const
    {
      if (den_ != 1)
	return ostr << num_ << '/' << den_;
      return ostr << num_;
    }

    inline
    RationalNumber
    RationalNumber::operator+ (const RationalNumber& nb) const
    {
      return RationalNumber (num_ * nb.den_ + nb.num_ * den_, den_ * nb.den_);
    }

    inline
    RationalNumber
    RationalNumber::operator- (const RationalNumber& nb) const
    {
      return RationalNumber (num_ * nb.den_ - nb.num_ * den_, den_ * nb.den_);
    }

    inline
    RationalNumber
    RationalNumber::operator- () const
    {
      return RationalNumber (- num_, den_);
    }

    inline
    RationalNumber
    RationalNumber::operator* (const RationalNumber& nb) const
    {
      unsigned int d1 = vcsn::misc::gcd (num_, nb.den_get ());
      unsigned int d2 = vcsn::misc::gcd (den_, nb.num_get ());
      return RationalNumber ((num_ / d1) * (nb.num_get () / d2), (den_ / d2) * (nb.den_get () / d1));
      // return RationalNumber (num_ * nb.num_, den_ * nb.den_);
    }

    inline
    RationalNumber
    RationalNumber::operator/ (const RationalNumber& nb) const
    {
      int numgcd = vcsn::misc::gcd (vcsn::misc::abs (num_), vcsn::misc::abs (nb.num_));
      int dengcd = vcsn::misc::gcd (den_, nb.den_);
      return RationalNumber ((num_ / numgcd) * (nb.den_ / dengcd),
			     (den_ / dengcd) * (nb.num_ / numgcd));
    }

    inline
    RationalNumber&
    RationalNumber::operator+= (const RationalNumber& nb)
    {
      // unsigned int d1 = vcsn::misc::gcd (den_, nb.den_);
      // if (d1 == 1)
      // {
      // 	set_unsafe_rational ((num_ * nb.den_) + (den_ * nb.num_), den_ * nb.den_);
      // }
      // else
      // {
      // 	unsigned int t = num_ * (nb.den_ / d1) + nb.num_ * (den_ / d1);
      // 	unsigned int d2 = vcsn::misc::gcd (t, d1);
      // 	set_unsafe_rational (t / d2, (den_ * d1) * (nb.den_ * d2));
      // }

      set_rational (num_ * nb.den_ + nb.num_ * den_, den_ * nb.den_);
      return (*this);
    }

    inline
    RationalNumber&
    RationalNumber::operator-= (const RationalNumber& nb)
    {
      // unsigned int d1 = vcsn::misc::gcd (den_, nb.den_);
      // if (d1 == 1)
      // {
      // 	set_unsafe_rational ((num_ * nb.den_) + (den_ * nb.num_), den_ * nb.den_);
      // }
      // else
      // {
      // 	unsigned int t = num_ * (nb.den_ / d1) + nb.num_ * (den_ / d1);
      // 	unsigned int d2 = vcsn::misc::gcd (t, d1);
      // 	set_unsafe_rational (t / d2, (den_ * d1) * (nb.den_ * d2));
      // }
      set_rational (num_ * nb.den_ - nb.num_ * den_, den_ * nb.den_);
      return (*this);
    }

    inline
    RationalNumber&
    RationalNumber::operator*= (const RationalNumber& nb)
    {
      // Delete overflow of 'num_ * nb.num_get ()' and 'den_ * nb.den_get ()'
      unsigned int d1 = vcsn::misc::gcd (num_, nb.den_get ());
      unsigned int d2 = vcsn::misc::gcd (den_, nb.num_get ());
      set_unsafe_rational ((num_ / d1) * (nb.num_get () / d2), (den_ / d2) *
			   (nb.den_get () / d1));
      // set_rational (num_ * nb.num_get (), den_ * nb.den_get ());
      return (*this);
    }

    inline
    RationalNumber&
    RationalNumber::operator/= (const RationalNumber& nb)
    {
      // Delete overflow of 'num_ * nb.den_get ()' and 'den_ * nb.num_get ()'
      unsigned int d1 = vcsn::misc::gcd (num_, nb.num_get ());
      unsigned int d2 = vcsn::misc::gcd (den_, nb.den_get ());
      set_unsafe_rational ((num_ / d1) * (nb.den_get () / d1), (den_ / d2) *
			   (nb.num_get () / d1));
      // set_rational (num_ * nb.den_, den_ * nb.num_);
      return (*this);
    }

    inline
    bool
    RationalNumber::operator== (const RationalNumber& nb) const
    {
      return (den_ == nb.den_) && (num_ == nb.num_);
    }

    inline
    bool
    RationalNumber::operator!= (const RationalNumber& nb) const
    {
      return (den_ != nb.den_) || (num_ != nb.num_);
    }

    inline
    bool
    RationalNumber::operator< (const RationalNumber& nb) const
    {
      return num_ * nb.den_ < nb.num_ * den_;
    }

    inline
    bool
    RationalNumber::operator<= (const RationalNumber& nb) const
    {
      return num_ * nb.den_ <= nb.num_ * den_;
    }

    inline
    bool
    RationalNumber::operator> (const RationalNumber& nb) const
    {
      return num_ * nb.den_ > nb.num_ * den_;
    }

    inline
    bool
    RationalNumber::operator>= (const RationalNumber& nb) const
    {
      return num_ * nb.den_ >= nb.num_ * den_;
    }

    inline
    RationalNumber::operator float () const
    {
      return to_float ();
      // return (static_cast<float> (num_)) / den_;
    }

    inline
    int
    RationalNumber::to_int () const
    {
      return num_ / den_;
    }

    inline
    float
    RationalNumber::to_float () const
    {
      return (static_cast<float> (num_)) / den_;
    }

    inline
    double
    RationalNumber::to_double () const
    {
      return (static_cast<double> (num_)) / den_;
    }

    inline
    void
    RationalNumber::set_rational (const int num, const unsigned den)
    {
      if (den)
      {
	assert (den);

	int div = vcsn::misc::gcd (vcsn::misc::abs (num), den);

	num_ = num / div;
	den_ = den / div;

	assert (1 == vcsn::misc::gcd (vcsn::misc::abs (num_), den_));
      }
      else
	{
	  num_ = 0;
	  den_ = 1;
	}
    }

    inline
    void
    RationalNumber::set_unsafe_rational (const int num, const unsigned den)
    {
      assert (den != 0);

      num_ = num;
      den_ = den;

      assert (vcsn::misc::is_coprime (num_, den_));
    }

    inline
    void
    RationalNumber::set_rational ()
    {
      set_rational (num_, den_);
    }

    inline
    std::ostream& operator<< (std::ostream& ostr, const RationalNumber& nb)
    {
      nb.print (ostr);
      return ostr;
    }

    inline
    std::istream&
    operator>> (std::istream& istr, RationalNumber& a)
    {
      int num;

      istr >> num;
      char slash;
      istr.read (&slash, 1);
      if ('/' != slash) // Test if a slash is present.
      {
       	istr.unget ();
       	a.set (num, 1);
       	return istr;
       }

      // Otherwise read the denominator.
      int den;
      istr >> den;
      a.set (num, den);

      return istr;
    }

  } // !algebra

} // !vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HXX
