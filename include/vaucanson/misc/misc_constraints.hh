// misc_constraints.hh
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

#ifndef UTILITY_MISC_CONSTRAINTS_HH
#define UTILITY_MISC_CONSTRAINTS_HH

#include <vaucanson/misc/constraints.hh>

namespace utility
{

  namespace concepts
  {

    /*-----------------------------------------------.
    | SameValue, SameType and DifferentType concepts |
    `-----------------------------------------------*/

#ifndef __ICC
    template <typename T, T A, T B>
    struct SameValue_chooser {};

    template <typename T, T A>
    struct SameValue_chooser<T, A, A> 
    { typedef void t; };
#endif
    template <typename T, T A, T B>
    struct SameValue 
    {
      void constraints() 
      {
#ifndef __ICC       
	typedef typename SameValue_chooser<T, A, B>::t required; 
#endif
      }
    };

    template <typename T, typename U>
    struct SameType_chooser { };
    template <typename T>
    struct SameType_chooser<T, T> { typedef void t; };

    template <typename T, typename U>
    struct SameType
    {
      void constraints() 
      {	typedef typename SameType_chooser<T, U>::t required; }
    };

    template <typename T, typename U>
    struct DifferentType_chooser { typedef int t; };
    template <typename T>
    struct DifferentType_chooser<T, T> { typedef void t; };

    template <typename T, typename U>
    struct DifferentType
    {
      void constraints() 
      {
	function_requires<
	  SameType<int, typename DifferentType_chooser<T, U>::t> >();
      }
    };


  }

}


#endif
