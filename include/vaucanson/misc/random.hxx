// random.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef MISC_RANDOM_HXX
# define MISC_RANDOM_HXX

# include <vaucanson/misc/random.hh>
# include <vector>
# include <cstdlib>

namespace vcsn {

  namespace misc {
    
    template <class T>
    T 
    RandomGenerator<T>::do_it()
    {
      assert(!"No random generator for this type ");
    }

    char 
    RandomGenerator<char>::do_it()
    {
      float f = float(rand()) / float(RAND_MAX);
      unsigned offs = unsigned((26 * f));
      return ('a' + offs);
    }

    bool
    RandomGenerator<bool>::do_it()
    {
      unsigned r = rand() * 2 / RAND_MAX;
      if (r < 1) 
	return true;
      else
	return false;
    }

    int
    RandomGenerator<int>::do_it()
    {
      return rand();
    }

    template <class Iterator, class OutputIterator>
    void random_sample_n(Iterator first, Iterator end, 
			 OutputIterator out, unsigned n)
    {
      std::vector<int> from;
      for (Iterator i = first; i != end; ++i)
	  from.push_back(*i);

      while ((from.size () > 0) && (n > 0))
	{
	  int  c = RANDOM_INT(from.size());
	  *out = from[c];
	  ++out;
	  from.erase(from.begin() + c);
	  --n;
	}
    }

  } // misc

} // vcsn

#endif // MISC_RANDOM_HH
