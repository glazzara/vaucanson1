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

# include <iostream>
# include <cassert>

namespace vcsn {

  namespace algebra {

    inline
    RationalNumber::RationalNumber ()
      : num_ (1), // 0 or 1
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
      return ostr << num_ << '/' << den_;
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
      return RationalNumber (num_ * nb.num_, den_ * nb.den_);
    }

    inline
    RationalNumber
    RationalNumber::operator/ (const RationalNumber& nb) const
    {
      return RationalNumber (num_ * nb.den_, den_ * nb.num_);
    }

    inline
    RationalNumber&
    RationalNumber::operator+= (const RationalNumber& nb)
    {
      set_rational (num_ * nb.den_ + nb.num_ * den_, den_ * nb.den_);
      return (*this);
    }

    inline
    RationalNumber&
    RationalNumber::operator-= (const RationalNumber& nb)
    {
      set_rational (num_ * nb.den_ - nb.num_ * den_, den_ * nb.den_);
      return (*this);
    }

    inline
    RationalNumber&
    RationalNumber::operator*= (const RationalNumber& nb)
    {
      set_rational (num_ * nb.num_, den_ * nb.den_);
      return (*this);
    }

    inline
    RationalNumber&
    RationalNumber::operator/= (const RationalNumber& nb)
    {
      set_rational (num_ * nb.den_, den_ * nb.num_);
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
      return (static_cast<float> (num_)) / den_;
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
      assertion (den != 0);

      unsigned int div = vcsn::misc::gcd (num, den);
      num_ = num / div;
      den_ = den / div;
      assertion (vcsn::misc::is_coprime (num_, den_));
    }

    inline
    void
    RationalNumber::set_rational ()
    {
      set_rational (num_, den_);
    }

  } // !algebra

} // !vcsn

inline
std::ostream& operator<< (std::ostream& ostr, vcsn::algebra::RationalNumber& nb)
{
  nb.print (ostr);
  return ostr; 
}

inline
std::istream&
operator>> (std::istream& istr, vcsn::algebra::RationalNumber& a)
{
  int num;
  int den;
  char slash;

  istr >> num;
  istr >> slash;
  assert ('/' == slash);
  istr >> den;
  a.set (num, den);

  return istr;
}

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HXX
