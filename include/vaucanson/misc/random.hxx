// random.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009 The Vaucanson Group.
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
#ifndef VCSN_MISC_RANDOM_HXX
# define VCSN_MISC_RANDOM_HXX

# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/limits.hh>
# include <vaucanson/misc/algebra.hh>

# include <cmath>
# include <cstdlib>
# include <vector>

# include <iostream>

namespace vcsn {
  namespace misc {
    namespace random {

      template<>
      inline char generate<char> ()
      {
	// We do not want any 0, because it could generate errors in strings.
	return char (1 + unsigned (rand ()) % ( (1 << (sizeof (char) * 8)) - 1));
      }

      template<>
      inline char generate<char> (char min, char max)
      {
	unsigned range = unsigned (max - min) + 1;
	return char (min + rand () % range);
      }

      inline char generate_letter ()
      {
	return generate<char> ('a', 'z');
      }

      inline char generate_digit ()
      {
	return generate<char> ('0', '9');
      }

      template<>
      inline bool generate<bool> ()
      {
	return static_cast<bool> (rand () & 1);
      }

      template<>
      inline int generate<int> ()
      {
	int res = rand () % vcsn::misc::limits<int>::max ();
	return generate<bool> () ? res : res * -1;
      }

      template<>
      inline int generate<int> (int min, int max)
      {
	unsigned range = unsigned (max - min) + 1;
	return min + rand () % range;
      }

      template<>
      inline unsigned generate<unsigned> ()
      {
	return rand () % vcsn::misc::limits<unsigned>::max ();
      }

      template<>
      inline unsigned generate<unsigned> (unsigned min, unsigned max)
      {
	unsigned range = unsigned (max - min) + 1;
	return min + rand () % range;
      }

      template<>
      inline float generate<float> ()
      {
	// This formula comes from the caml stdlib. It generates numbers
	// between -2 and 2 (values that can be starable or not).
	return ( ((static_cast<float> (rand ()) / RAND_MAX +
		   static_cast<float> (rand ())) / RAND_MAX +
		  static_cast<float> (rand ())) / RAND_MAX) * 4 - 2;
      }

      template<>
      inline float generate<float> (float min, float max)
      {
	float range = float (max - min);
	float generate_one = ( (static_cast<float> (rand ()) / RAND_MAX +
				static_cast<float> (rand ())) / RAND_MAX +
			       static_cast<float> (rand ())) / RAND_MAX;

	return min + generate_one * range;
      }

      template<>
      inline double generate<double> ()
      {
	// This formula comes from the caml stdlib. It generates numbers
	// between -2 and 2 (values that can be starable or not).
	return ( ((static_cast<double> (rand ()) / RAND_MAX +
		   static_cast<double> (rand ())) / RAND_MAX +
		  static_cast<double> (rand ())) / RAND_MAX) * 4 - 2;
      }

      template<>
      inline double generate<double> (double min, double max)
      {
	double range = double (max - min);
	double generate_one = ( (static_cast<double> (rand ()) / RAND_MAX +
				 static_cast<double> (rand ())) / RAND_MAX +
				static_cast<double> (rand ())) / RAND_MAX;

	return min + generate_one * range;
      }

      template <class IteratorValueType, class Iterator, class OutputIterator>
      void sample_n (const IteratorValueType&, Iterator first, Iterator end,
		     OutputIterator out, unsigned n)
      {
	std::vector<IteratorValueType> from;
	for (Iterator i = first; i != end; ++i)
	  from.push_back (*i);

	while ( (from.size () > 0) && (n > 0))
	{
	  int  c = generate<int> (0, from.size () - 1);
	  *out = from[c];
	  ++out;
	  from.erase (from.begin () + c);
	  --n;
	}
      }

      template<>
      inline
      vcsn::algebra::RationalNumber
      generate<vcsn::algebra::RationalNumber> ()
      {
	const int num = generate<int> ();
	const unsigned denom =
	  generate<unsigned> (1, vcsn::misc::limits<unsigned>::max ());
	return vcsn::algebra::RationalNumber (num, denom);
      }

      template<>
      inline
      vcsn::algebra::RationalNumber
      generate<vcsn::algebra::RationalNumber>
      (const vcsn::algebra::RationalNumber min,
       const vcsn::algebra::RationalNumber max)
      {
	int left = min.num_get () ;
	int right = max.num_get ();
	int den = min.den_get () * max.den_get ();

	const int ratio = right - left;

	int n1 = generate<int> (0, (vcsn::misc::limits<int>::max () - 1) / ratio);
	int n2 = generate<int> (0, (vcsn::misc::limits<int>::max () - 1) / ratio);

	if (n1 > n2)
	  {
	    int swap = n1;
	    n1 = n2;
	    n2 = swap;
	  }

	n2 *= den;

	n1 = n1 * ratio + (left * n2);

	if (n1 == n2)
	  --n1;
	if (-n1 == n2)
	  ++n1;

	return
	  vcsn::algebra::RationalNumber (n1, n2);
      }

# define MAKE_PAIR_SPECIALIZATION(TYPE1, TYPE2) \
      template <> \
      inline \
      std::pair<TYPE1, TYPE2> generate<std::pair<TYPE1, TYPE2> >() \
      { \
	return std::make_pair(generate<TYPE1> (), generate<TYPE2> ()); \
      }

      MAKE_PAIR_SPECIALIZATION(char, char)
      MAKE_PAIR_SPECIALIZATION(char, int)
      MAKE_PAIR_SPECIALIZATION(int,  int)
      MAKE_PAIR_SPECIALIZATION(int,  char)

# undef MAKE_PAIR_SPECIALIZATION

      template <>
      inline
      small_alpha_letter_t
      generate<small_alpha_letter_t> ()
      {
	return generate<char> (small_alpha_interval_t::from_value,
			       small_alpha_interval_t::to_value);
      }

    } // Random
  } // misc
} // vcsn

#endif // ! VCSN_MISC_RANDOM_HXX
