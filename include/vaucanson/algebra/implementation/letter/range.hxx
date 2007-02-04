// range.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_RANGE_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_RANGE_HXX

# include <cstdlib>
# include <cmath>

namespace vcsn
{

  namespace algebra
  {

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
    bool
    static_char_interval<From, To>::check(char c)
    {
      return ((c >= From) && (c <= To));
    }

    template <char From, char To>
    char static_char_interval<From, To>::from()
    {
      return From;
    }

    template <char From, char To>
    char static_char_interval<From, To>::to()
    {
      return To;
    }

    template <char From, char To>
    char static_char_interval<From, To>::random()
    {
      unsigned r = floor((float (rand()) / RAND_MAX) * (To - From + 1));
      return (char)(From + r);
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_RANGE_HXX
