// predefs.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

# include <vaucanson/algebra/concrete/letter/char_letter.hh>
# include <vaucanson/algebra/concrete/letter/range.hh>
# include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>
# include <vaucanson/algebra/concrete/alphabets/decorated_alphabet.hh>

namespace vcsn {

  namespace algebra {

    namespace small_alpha_letter {
      
      typedef static_ranged<char, static_char_interval<'a','z'> >  Letter;
      typedef AlphabetSet<Letter>				 Alphabets;
      typedef Element<Alphabets, std::set<Letter> >		 Alphabet;
      typedef AlphabetDecorator<Letter, std::set<Letter> >	 DAlphabetImpl;
      typedef Element<Alphabets, DAlphabetImpl>			 DAlphabet;

    } // small_alpha_letter

    namespace char_letter {

      typedef char						 Letter;
      typedef AlphabetSet<Letter>			         Alphabets;
      typedef Element<Alphabets, std::set<Letter> >		  Alphabet;
      typedef AlphabetDecorator<Letter, std::set<Letter> >	 DAlphabetImpl;
      typedef Element<Alphabets, DAlphabetImpl>			 DAlphabet;

    } // char_letter

    namespace int_letter {

      typedef int						 Letter;
      typedef AlphabetSet<Letter>				 Alphabets;
      typedef Element<Alphabets, std::set<Letter> >		 Alphabet;
      typedef AlphabetDecorator<Letter, std::set<Letter> >	 DAlphabetImpl;
      typedef Element<Alphabets, DAlphabetImpl>			 DAlphabet;

    } // int_letter

  } // algebra

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_ALPHABETS_PREDEFS_HH
