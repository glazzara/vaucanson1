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

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>::TRationalNumber ()
    : num_ (NUMType(0)), // 0 or 1
      den_ (DENType(1))
    {
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>::TRationalNumber (const NUMType num)
    : num_ (num),
      den_ (DENType(1))
    {
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>::TRationalNumber (const NUMType num, const DENType den)
    {
      set_rational (num, den);
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>::TRationalNumber (const TRationalNumber<NUMType, DENType>& nb)
    {
      set_rational (nb.num_, nb.den_);
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>::~TRationalNumber ()
    {}

    template<typename NUMType, typename DENType>
    inline
    vcsn::algebra::TRationalNumber<NUMType, DENType>&
    TRationalNumber<NUMType, DENType>::set (const NUMType num, const DENType den)
    {
      set_rational (num, den);
      return (*this);
    }

    template<typename NUMType, typename DENType>
    inline
    NUMType
    TRationalNumber<NUMType, DENType>::num_get () const
    {
      return num_;
    }

    template<typename NUMType, typename DENType>
    inline
    DENType
    TRationalNumber<NUMType, DENType>::den_get () const
    {
      return den_;
    }

    template<typename NUMType, typename DENType>
    inline
    std::ostream&
    TRationalNumber<NUMType, DENType>::print (std::ostream& ostr) const
    {
      if (den_ != 1)
	return ostr << num_ << '/' << den_;
      return ostr << num_;
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>
    TRationalNumber<NUMType, DENType>::operator+ (const TRationalNumber<NUMType, DENType>& nb) const
    {
      return TRationalNumber<NUMType, DENType> (num_ * nb.den_ + nb.num_ * den_, den_ * nb.den_);
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>
    TRationalNumber<NUMType, DENType>::operator- (const TRationalNumber<NUMType, DENType>& nb) const
    {
      using vcsn::misc::abs;
      NUMType a = den_;
      NUMType b = nb.den_;

      return TRationalNumber<NUMType, DENType> ((num_ * b) - (nb.num_ * a), den_ * nb.den_);
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>
    TRationalNumber<NUMType, DENType>::operator- () const
    {
      return TRationalNumber<NUMType, DENType> (- num_, den_);
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>
    TRationalNumber<NUMType, DENType>::operator* (const TRationalNumber<NUMType, DENType>& nb) const
    {
      NUMType d1 = vcsn::misc::gcd (vcsn::misc::abs(num_), nb.den_get ());
      NUMType d2 = vcsn::misc::gcd (den_, vcsn::misc::abs(nb.num_get ()));

      return TRationalNumber<NUMType, DENType> ((num_ / d1) * (nb.num_get () / d2),
			     (den_ / d2) * (nb.den_get () / d1));
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>
    TRationalNumber<NUMType, DENType>::operator/ (const TRationalNumber<NUMType, DENType>& nb) const
    {
      NUMType signe = 1;
      assert(nb.num_ != 0);
      NUMType numgcd = vcsn::misc::gcd (vcsn::misc::abs (num_), vcsn::misc::abs (nb.num_));
      NUMType dengcd = vcsn::misc::gcd (den_, nb.den_);
      if(nb.num_ < 0)
	signe = -1;
      return TRationalNumber<NUMType, DENType> (signe * ((num_ / numgcd)
							 * ((NUMType) nb.den_get() /dengcd)),
						(signe * nb.num_get()
							 / numgcd) *
						(den_ / dengcd));
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>&
    TRationalNumber<NUMType, DENType>::operator+= (const TRationalNumber<NUMType, DENType>& nb)
    {
      // std::cout << "+=" << std::endl;
      // std::cout << *this << '+' << nb << "= " << num_ * nb.den_ +
      // 	nb.num_ * den_ << '\'' << den_ * nb.den_<< std::endl;
      set_rational (num_ * nb.den_ + nb.num_ * den_, den_ * nb.den_);
      return (*this);
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>&
    TRationalNumber<NUMType, DENType>::operator-= (const TRationalNumber<NUMType, DENType>& nb)
    {
      set_rational (num_ * nb.den_ - nb.num_ * den_, den_ * nb.den_);
      return (*this);
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>&
    TRationalNumber<NUMType, DENType>::operator*= (const TRationalNumber<NUMType, DENType>& nb)
    {
      DENType d1 = vcsn::misc::gcd (vcsn::misc::abs(num_), nb.den_get ());
      DENType d2 = vcsn::misc::gcd (den_, vcsn::misc::abs(nb.num_get ()));
      set_unsafe_rational ((num_ / d1) * (nb.num_get () / d2),
			   (den_ / d2) * (nb.den_get () / d1));
      return (*this);
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>&
    TRationalNumber<NUMType, DENType>::operator/= (const TRationalNumber<NUMType, DENType>& nb)
    {
      NUMType signe = 1;
      assert(nb.num_ != 0);
      NUMType numgcd = vcsn::misc::gcd (vcsn::misc::abs (num_), vcsn::misc::abs (nb.num_));
      NUMType dengcd = vcsn::misc::gcd (den_, nb.den_);
      if(nb.num_ < 0)
	signe = -1;
      set_unsafe_rational (signe * ((num_ / numgcd) * ((NUMType) nb.den_get() /dengcd)),
						(signe * nb.num_get() / numgcd) * (den_ / dengcd));
      return *this;
    }

    template<typename NUMType, typename DENType>
    inline
    bool
    TRationalNumber<NUMType, DENType>::operator== (const TRationalNumber<NUMType, DENType>& nb) const
    {
      //return (den_ * nb.num_ == nb.den_ * num_);
       if (!num_)
	 return (!nb.num_);
       return (den_ == nb.den_) && (num_ == nb.num_);
    }

    template<typename NUMType, typename DENType>
    inline
    bool
    TRationalNumber<NUMType, DENType>::operator!= (const TRationalNumber<NUMType, DENType>& nb) const
    {
      // return (den_ * nb.num_ != nb.den_ * num_);
      if (!num_)
	return (!!nb.num_);
      return (den_ != nb.den_) || (num_ != nb.num_);
    }

    template<typename NUMType, typename DENType>
    inline
    bool
    TRationalNumber<NUMType, DENType>::operator< (const TRationalNumber<NUMType, DENType>& nb) const
    {
      return num_ * nb.den_ < nb.num_ * den_;
    }

    template<typename NUMType, typename DENType>
    inline
    bool
    TRationalNumber<NUMType, DENType>::operator<= (const TRationalNumber<NUMType, DENType>& nb) const
    {
      return num_ * nb.den_ <= nb.num_ * den_;
    }

    template<typename NUMType, typename DENType>
    inline
    bool
    TRationalNumber<NUMType, DENType>::operator> (const TRationalNumber<NUMType, DENType>& nb) const
    {
      return num_ * nb.den_ > nb.num_ * den_;
    }

    template<typename NUMType, typename DENType>
    inline
    bool
    TRationalNumber<NUMType, DENType>::operator>= (const TRationalNumber<NUMType, DENType>& nb) const
    {
      return num_ * nb.den_ >= nb.num_ * den_;
    }

    template<typename NUMType, typename DENType>
    inline
    TRationalNumber<NUMType, DENType>::operator float () const
    {
      return to_float ();
    }

    template<typename NUMType, typename DENType>
    inline
    int
    TRationalNumber<NUMType, DENType>::to_int () const
    {
      return num_ / den_;
    }

    template<typename NUMType, typename DENType>
    inline
    float
    TRationalNumber<NUMType, DENType>::to_float () const
    {
      return (static_cast<float> (num_)) / den_;
    }

    template<typename NUMType, typename DENType>
    inline
    double
    TRationalNumber<NUMType, DENType>::to_double () const
    {
      return (static_cast<double> (num_)) / den_;
    }
#include <iostream>
    template<typename NUMType, typename DENType>
    inline
    void
    TRationalNumber<NUMType, DENType>::set_rational (const NUMType num, const DENType den)
    {
      if (num)
      {
	assert(den);
	NUMType div = vcsn::misc::gcd(vcsn::misc::abs(num), den);
	num_ = num / div;
	den_ = den / div;
	assert(1 == vcsn::misc::gcd(vcsn::misc::abs(num_), den_));
	return;
      }
      else
      {
	num_ = 0;
	den_ = 1;
	return;
      }
    }

    template<typename NUMType, typename DENType>
    inline
    void
    TRationalNumber<NUMType, DENType>::set_unsafe_rational (const NUMType num, const DENType den)
    {
      assert (den != 0);

      num_ = num;
      den_ = den;

      assert (vcsn::misc::is_coprime (num_, den_));
    }

    template<typename NUMType, typename DENType>
    inline
    void
    TRationalNumber<NUMType, DENType>::set_rational ()
    {
      set_rational (num_, den_);
    }

    template<typename NUMType, typename DENType>
    inline
    std::ostream&
    operator<< (std::ostream& ostr, const TRationalNumber<NUMType, DENType>& nb)
    {
      nb.print (ostr);
      return ostr;
    }

    template<typename NUMType, typename DENType>
    inline
    std::istream&
    operator>> (std::istream& istr, TRationalNumber<NUMType, DENType>& a)
    {
      NUMType num;

      istr >> num;
      char slash;
      if (!istr.eof())
	istr.get(slash);
      if ('/' != slash) // Test if a slash is present.
      {
       	istr.unget();
       	a.set(num, 1);
       	return istr;
       }

      // Otherwise read the denominator.
      DENType den;
      istr >> den;
      a.set(num, den);

      return istr;
    }
  } // !algebra

} // !vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_NUMBER_HXX
