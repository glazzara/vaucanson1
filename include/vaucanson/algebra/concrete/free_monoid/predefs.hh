// predefs.hh
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
#ifndef VCSN_ALGEBRA_CONCRETE_FREE_MONOID_PREDEFS_HH
# define VCSN_ALGEBRA_CONCRETE_FREE_MONOID_PREDEFS_HH

# include <vaucanson/algebra/concrete/alphabets/predefs.hh>
# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>

namespace vcsn {
  
  namespace algebra {

    namespace small_alpha_letter {

      typedef 
      SetWords<Alphabet>					Words;
      
      typedef
      Element<Words, std::basic_string<Letter> >     	        Word;

    } // static_alpha_letter

    namespace char_letter {

      typedef 
      SetWords<Alphabet>					Words;
      
      typedef
      Element<Words, std::string>			        Word;
    
    } // char_letter

  } // algebra

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_FREE_MONOID_PREDEFS_HH
