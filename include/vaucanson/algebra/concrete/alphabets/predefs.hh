// predefs.hh
//
// $Id$
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
#ifndef VCSN_ALGEBRA_CONCRETE_ALPHABETS_PREDEFS_HH
# define VCSN_ALGEBRA_CONCRETE_ALPHABETS_PREDEFS_HH

# include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>

namespace vcsn {

  namespace algebra {

    namespace char_letter {

      typedef algebra::SetAlphabets<char>			   Alphabets;
      typedef Element<Alphabets, std::set<char> >		   Alphabet;

    } // char_letter

    namespace int_letter {

      typedef algebra::SetAlphabets<int>			   Alphabets;
      typedef Element<Alphabets, std::set<int> >		   Alphabet;

    } // int_letter

  } // algebra

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_ALPHABETS_PREDEFS_HH
