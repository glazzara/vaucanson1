// range.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#ifndef VCSN_ALGEBRA_CONCRETE_LETTER_RANGE_HXX
# define VCSN_ALGEBRA_CONCRETE_LETTER_RANGE_HXX

namespace vcsn {

  namespace algebra {

    template <class T, class Interval>
    static_ranged<T, Interval>::static_ranged()
    {}

    template <class T, class Interval>
    static_ranged<T, Interval>::static_ranged(const T& v)
    {
      if (Interval::check(v))
	value_ = v;
      else
	value_ = Interval::from();
    }

    template <class T, class Interval>
    static_ranged<T, Interval>::static_ranged(const static_ranged& o) :
      value_(o.value_)
    {}

    template <class T, class Interval>
    static_ranged<T, Interval>::operator T() const
    {
      return value_;
    }

    template <class T, class Interval>
    bool operator<(const static_ranged<T, Interval>& lhs, 
		   const static_ranged<T, Interval>& rhs)
    {
      return lhs.value() < rhs.value();
    }

    template <class T, class Interval>
    bool operator==(const static_ranged<T, Interval>& lhs, 
		   const static_ranged<T, Interval>& rhs)
    {
      return lhs.value() == rhs.value();
    }

    template <class T, class Interval>
    const T& static_ranged<T, Interval>::value() const
    {
      return value_;
    }

    template <class T, class Interval>
    T& static_ranged<T, Interval>::value()
    {
      return value_;
    }

    template <class T, class Interval>
    static_ranged<T, Interval>
    static_ranged<T, Interval>::randomized()
    {
      value_ = Interval::random();
      return *this;
    }

    template <char From, char To>
    inline
    bool
    static_char_interval<From, To>::check(char c)
    {
      return ((c >= From) && (c <= To));
    }

    template <char From, char To>
    inline
    char static_char_interval<From, To>::from()
    {
      return From;
    }

    template <char From, char To>
    inline
    char static_char_interval<From, To>::to()
    {
      return To;
    }

    template <char From, char To>
    inline
    char static_char_interval<From, To>::random()
    {
      unsigned r = 
      (unsigned) floor(((float) rand() / (float) RAND_MAX) * (To - From + 1));
      return (char)(From + r);
    }

  } // algebra

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_LETTER_RANGE_HXX
