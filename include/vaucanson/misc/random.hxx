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

#ifndef VCSN_MISC_RANDOM_HXX
# define VCSN_MISC_RANDOM_HXX

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

#endif // VCSN_MISC_RANDOM_HH
