// predefs.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCRETE_FREE_MONOID_PREDEFS_HH
# define VCSN_ALGEBRA_CONCRETE_FREE_MONOID_PREDEFS_HH

# include <vaucanson/algebra/concrete/alphabets/predefs.hh>
# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>

namespace vcsn {
  
  namespace algebra {

    namespace small_alpha_letter {

      typedef 
      FreeMonoid<Alphabet>					Words;

      typedef std::basic_string<Letter>				WordValue;
      
      typedef
      Element<Words, WordValue>			     	        Word;

    } // static_alpha_letter

    namespace char_letter {

      typedef 
      FreeMonoid<Alphabet>					Words;
      
      typedef std::string					WordValue;

      typedef
      Element<Words, std::string>			        Word;
    
    } // char_letter

    namespace char_pair {

      typedef 
      FreeMonoid<Alphabet>					Words;
      
      typedef std::basic_string<Letter>			        WordValue;

      typedef
      Element<Words, WordValue>			                Word;
    
    } // char_pair

    namespace weighted_letter {

      typedef 
      FreeMonoid<Alphabet>					Words;
      
      typedef std::basic_string<Letter>			        WordValue;

      typedef
      Element<Words, WordValue>			                Word;
    
    } // weighted_letter

    namespace int_letter {

      typedef 
      FreeMonoid<Alphabet>					Words;
      
      typedef std::list<Letter>			                WordValue;

      typedef
      Element<Words, WordValue>			                Word;
    
    } // int_letter

  } // algebra

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_FREE_MONOID_PREDEFS_HH
