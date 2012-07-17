// q_number.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2011, 2012 The Vaucanson Group.
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

    template<typename IntType>
    inline
    TRationalNumber<IntType>::TRationalNumber ()
    : num_ (IntType(0)), // 0 or 1
      den_ (IntType(1))
    {
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>::TRationalNumber (const IntType num)
    : num_ (num),
      den_ (IntType(1))
    {
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>::TRationalNumber (const IntType num, const IntType den)
    {
      set_rational (num, den);
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>::TRationalNumber (const TRationalNumber<IntType>& nb)
    {
      set_rational (nb.num_, nb.den_);
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>::~TRationalNumber ()
    {}

    template<typename IntType>
    inline
    vcsn::algebra::TRationalNumber<IntType>&
    TRationalNumber<IntType>::set (const IntType num, const IntType den)
    {
      set_rational (num, den);
      return (*this);
    }

    template<typename IntType>
    inline
    IntType
    TRationalNumber<IntType>::num_get () const
    {
      return num_;
    }

    template<typename IntType>
    inline
    IntType
    TRationalNumber<IntType>::den_get () const
    {
      return den_;
    }

    template<typename IntType>
    inline
    std::ostream&
    TRationalNumber<IntType>::print (std::ostream& ostr) const
    {
      if (den_ != 1)
	return ostr << num_ << '/' << den_;
      return ostr << num_;
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>
    TRationalNumber<IntType>::operator+ (const TRationalNumber<IntType>& nb) const
    {
      TRationalNumber<IntType> r(*this);
	  r+=nb;
      return r;
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>
    TRationalNumber<IntType>::operator- (const TRationalNumber<IntType>& nb) const
    {
      TRationalNumber<IntType> r(*this);
	  r-=nb;
      return r;
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>
    TRationalNumber<IntType>::operator- () const
    {
      return TRationalNumber<IntType> (- num_, den_);
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>
    TRationalNumber<IntType>::operator* (const TRationalNumber<IntType>& nb) const
    {
      TRationalNumber<IntType> r(*this);
	  r*=nb;
      return r;
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>
    TRationalNumber<IntType>::operator/ (const TRationalNumber<IntType>& nb) const
    {
      TRationalNumber<IntType> r(*this);
	  r/=nb;
      return r;

    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>&
    TRationalNumber<IntType>::operator+= (const TRationalNumber<IntType>& nb)
    {
      IntType g = vcsn::misc::gcd(den_,nb.den_);
      set_rational (nb.den_ / g * num_+ den_ / g * nb.num_, den_ / g * nb.den_);
      return (*this);
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>&
    TRationalNumber<IntType>::operator-= (const TRationalNumber<IntType>& nb)
    {
      IntType g = vcsn::misc::gcd(den_,nb.den_);
      set_rational (nb.den_ / g * num_ - den_ / g * nb.num_, den_ / g * nb.den_);
      return (*this);
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>&
    TRationalNumber<IntType>::operator*= (const TRationalNumber<IntType>& nb)
    {
      IntType d1 = vcsn::misc::gcd (num_, nb.den_);
      IntType d2 = vcsn::misc::gcd (den_, nb.num_);
      set_unsafe_rational ((num_ / d1) * (nb.num_ / d2),
			   (den_ / d2) * (nb.den_ / d1));
      return (*this);
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>&
    TRationalNumber<IntType>::operator/= (const TRationalNumber<IntType>& nb)
    {
      assert(nb.num_ != 0);
      IntType d1 = vcsn::misc::gcd (num_, nb.num_);// negative iff nb.num_ negative
      IntType d2 = vcsn::misc::gcd (den_, nb.den_);
      set_unsafe_rational ((num_ / d1) * (nb.den_ / d2),
						(nb.num_ / d1) * (den_ / d2));
      return *this;
    }

    template<typename IntType>
    inline
    bool
    TRationalNumber<IntType>::operator== (const TRationalNumber<IntType>& nb) const
    {
       if (!num_)
		 return (!nb.num_);
       return (den_ == nb.den_) && (num_ == nb.num_);
    }

    template<typename IntType>
    inline
    bool
    TRationalNumber<IntType>::operator!= (const TRationalNumber<IntType>& nb) const
    {
      return !(*this == nb);
    }

    template<typename IntType>
    inline
    bool
    TRationalNumber<IntType>::operator< (const TRationalNumber<IntType>& nb) const
    {
      return (num_ * nb.den_ < nb.num_ * den_);
    }

    template<typename IntType>
    inline
    bool
    TRationalNumber<IntType>::operator<= (const TRationalNumber<IntType>& nb) const
    {
      return !(nb<*this);
    }

    template<typename IntType>
    inline
    bool
    TRationalNumber<IntType>::operator> (const TRationalNumber<IntType>& nb) const
    {
      return nb<*this;;
    }

    template<typename IntType>
    inline
    bool
    TRationalNumber<IntType>::operator>= (const TRationalNumber<IntType>& nb) const
    {
      return !(*this<nb);
    }

    template<typename IntType>
    inline
    TRationalNumber<IntType>::operator double () const
    {
      return to_double ();
    }

    template<typename IntType>
    inline
    IntType
    TRationalNumber<IntType>::to_integer () const
    {
      return num_ / den_;
    }

    template<typename IntType>
    inline
    float
    TRationalNumber<IntType>::to_float () const
    {
      return (static_cast<float> (num_)) / den_;
    }

    template<typename IntType>
    inline
    double
    TRationalNumber<IntType>::to_double () const
    {
      return (static_cast<double> (num_)) / den_;
    }
#include <iostream>
    template<typename IntType>
    inline
    void
    TRationalNumber<IntType>::set_rational (const IntType num, const IntType den)
    {
	assert(den);
	IntType div = vcsn::misc::gcd(num, den); //negative iff den negative
	num_ = num / div;
	den_ = den / div;
	}

    template<typename IntType>
    inline
    void
    TRationalNumber<IntType>::set_unsafe_rational (const IntType num, const IntType den)
    {
      assert (den != 0);

      num_ = num;
      den_ = den;

      assert (vcsn::misc::is_coprime (num_, den_));
    }

    template<typename IntType>
    inline
    void
    TRationalNumber<IntType>::set_rational ()
    {
      set_rational (num_, den_);
    }

    template<typename IntType>
    inline
    std::ostream&
    operator<< (std::ostream& ostr, const TRationalNumber<IntType>& nb)
    {
      nb.print (ostr);
      return ostr;
    }

    template<typename IntType>
    inline
    std::istream&
    operator>> (std::istream& istr, TRationalNumber<IntType>& a)
    {
      IntType num;

      istr >> num;
      char slash;
      if (istr.eof())
	{
	  a.set(num, 1);
	  return istr;
	}

      // Do we have a slash?
      istr.get(slash);
      if ('/' != slash)
      {
       	istr.unget();
       	a.set(num, 1);
       	return istr;
       }

      // Read the denominator.
      IntType den;
      istr >> den;
      a.set(num, den);

      return istr;
    }
  } // !algebra

} // !vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HXX
