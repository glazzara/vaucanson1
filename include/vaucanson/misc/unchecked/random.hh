// random.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and 
// Regis-Gianas.
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

#ifndef VCSN_MISC_RANDOM_HH
# define VCSN_MISC_RANDOM_HH

# include <cstdlib>
# include <utility>
# include <vaucanson/misc/limits.hh>

namespace vcsn {

  namespace misc {

    #define RANDOM_INT(N) \
       ((unsigned) floor(((float) rand() / (float) RAND_MAX) * N));

    template <class T>
    struct RandomGenerator
    {
      static T do_it();
    };

    template <>
    struct RandomGenerator<char>
    {
      static char do_it()
      {
	float f = float(rand()) / float(RAND_MAX);
	unsigned offs = unsigned((26 * f));
	return ('a' + offs);
      }
    };

    template <>
    struct RandomGenerator<bool>
    {
      static bool do_it()
      {
	unsigned r = rand();
	if (r < RAND_MAX / 2) 
	  return true;
	else
	  return false;
      }
    };

    template <>
    struct RandomGenerator<int>
    {
      static int do_it()
      {
	return RandomGenerator<bool>::do_it() ? rand() : -rand();
      }
    };

    struct RandomGenerator<float>
    {
      static inline
      float
      do_it(bool zero_to_one = false)
      {
	if (zero_to_one)
	  // This formula comes from the caml stdlib.
	  return ((static_cast<float> (rand()) / RAND_MAX + 
		   static_cast<float> (rand())) / RAND_MAX +
		  static_cast<float> (rand())) / RAND_MAX;
	else
	  {
	    union { int i; float f; } u;
	    do
	      {
		// I know this will give an overflow. This is just a trick to
		// ensure high order bits are affected.
		u.i = rand() * std::numeric_limits<int>::max();
	      }
	    while (!is_a_number(u.f));
	    return u.f;
	  }
      }

      // FIXME: There should be only this version of do_it, with a default
      // range. However, there is no simple way of having a good algorithm
      // for both small and wide intervals. Do not use this one with wide
      // intervals.
      static inline
      float
      do_it(const std::pair<float, float>& boundaries)
      {
	const float semi_interval =
	  boundaries.second / 2 - boundaries.first / 2;
	return boundaries.first + do_it(true) * 2.0 * semi_interval;
      }
    protected:
      static inline
      bool
      is_a_number(float f)
      {
	const float inf		= std::numeric_limits<float>::infinity();
	const float neginf	= -std::numeric_limits<float>::infinity();
	const float nan1	= std::numeric_limits<float>::quiet_NaN();
	const float nan2	= std::numeric_limits<float>::signaling_NaN();
	
	return (f != inf) && (f != neginf) && (f != nan1) && (f != nan2);
      }
    };
    
    template <class InputIterator, class OutputIterator>
    void random_sample_n(InputIterator first, InputIterator end, 
			 OutputIterator out, unsigned n);

  } // misc

} // vcsn

# include <vaucanson/misc/random.hxx>

#endif // VCSN_MISC_RANDOM_HH
