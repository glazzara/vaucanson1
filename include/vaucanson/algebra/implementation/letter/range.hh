// range.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_RANGE_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_RANGE_HH

# include <vaucanson/algebra/concept/letter.hh>

namespace vcsn {

  namespace algebra {

    template <class T, class Interval>
    class static_ranged
    {
    public:
      static_ranged();
      static_ranged(const T& v);
      static_ranged(const static_ranged& r);
      operator T() const;
      static_ranged	randomized();
      T&		value();
      const T&		value() const;

      // FIXME: add operator++ !!! It should loop from 'begin' to 'to' !

    private:
      T	       value_;
    };

    template <char From, char To>
    struct static_char_interval
    {
      static bool check(char c);
      static char from();
      static char to();
      static char random();
      enum
	{
	  from_value = From,
	  to_value = To
	};
    };

    template <class T, class Interval>
    struct letter_traits< static_ranged<T, Interval> >
    {
      enum
	{
	  local_to_value = Interval::to_value,
	  local_from_value = Interval::from_value,
	  cardinal = local_to_value - local_from_value + 1
	};
    };

    // FIXME: op_leq may be more adapted.
    template <class T, class Interval>
    bool operator<(const static_ranged<T, Interval>& lhs,
		   const static_ranged<T, Interval>& rhs);

    template <class T, class Interval>
    bool operator==(const static_ranged<T, Interval>& lhs,
		    const static_ranged<T, Interval>& rhs);

    template <class Stream, class T, class Interval>
    Stream& operator<<(Stream& s, static_ranged<T, Interval>& sr)
    {
      s << sr.value ();
      return s;
    }

  } // algebra

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/letter/range.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_RANGE_HH
