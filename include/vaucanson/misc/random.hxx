// random.hxx
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

#ifndef VCSN_MISC_RANDOM_HXX
# define VCSN_MISC_RANDOM_HXX

# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/limits.hh>

# include <cstdlib>
# include <vector>

namespace utility {
  namespace random {

    template<>
    char generate<char>()
    { 
      // We do not want any 0, because it could generate errors in strings.
      return char (1 + unsigned(rand()) % ((1 << (sizeof(char) * 8)) - 1));
    }

    template<>
    char generate<char>(char min, char max)
    {
      unsigned range = unsigned(max - min) + 1;
      return char(min + rand() % range);
    }

    char generate_letter()
    {
      return generate<char>('a', 'z'); 
    }

    char generate_digit()
    {
      return generate<char>('0', '9'); 
    }

    template<>
    bool generate<bool>()
    { 
      return rand() % 1; 
    }

    template<>
    int generate<int>()
    {
      return rand() % utility::limits<int>::max();
    }

    template<>
    int generate<int>(int min, int max)
    {
      unsigned range = unsigned(max - min) + 1;
      return min + rand() % range;
    }

    template<>
    float generate<float>()
    {
      // This formula comes from the caml stdlib.
      return ((static_cast<float> (rand()) / RAND_MAX + 
	       static_cast<float> (rand())) / RAND_MAX +
	      static_cast<float> (rand())) / RAND_MAX;
    }

    template <class Iterator, class OutputIterator>
    void sample_n(Iterator first, Iterator end, 
		  OutputIterator out, unsigned n)
    {
      std::vector<int> from;
      for (Iterator i = first; i != end; ++i)
	  from.push_back(*i);

      while ((from.size () > 0) && (n > 0))
	{
	  int  c = generate<int>(0, from.size() - 1);
	  *out = from[c];
	  ++out;
	  from.erase(from.begin() + c);
	  --n;
	}
    }

  } // random

} // vcsn

#endif // VCSN_MISC_RANDOM_HXX
