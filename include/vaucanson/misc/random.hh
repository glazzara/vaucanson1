// random.hh
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

#ifndef VCSN_MISC_RANDOM_HH
# define VCSN_MISC_RANDOM_HH

# include <cstdlib>

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
	unsigned r = rand() * 2 / RAND_MAX;
	if (r < 1) 
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
	return rand();
      }

    };

    template <class InputIterator, class OutputIterator>
    void random_sample_n(InputIterator first, InputIterator end, 
			 OutputIterator out, unsigned n);

  } // misc

} // vcsn

# include <vaucanson/misc/random.hxx>

#endif // VCSN_MISC_RANDOM_HH
