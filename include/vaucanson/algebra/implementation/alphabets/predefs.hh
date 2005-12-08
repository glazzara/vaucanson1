// predefs.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_PREDEFS_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_PREDEFS_HH

# include <vaucanson/algebra/implementation/letter/char_letter.hh>
# include <vaucanson/algebra/implementation/letter/range.hh>
# include <vaucanson/algebra/implementation/alphabets/set_alphabet.hh>
# include <vaucanson/algebra/implementation/alphabets/decorated_alphabet.hh>

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

    namespace char_pair {

      typedef std::pair<char, char>    				 Letter;
      typedef AlphabetSet<Letter>			         Alphabets;
      typedef Element<Alphabets, std::set<Letter> >		  Alphabet;
      typedef AlphabetDecorator<Letter, std::set<Letter> >	 DAlphabetImpl;
      typedef Element<Alphabets, DAlphabetImpl>			 DAlphabet;

    } // char_pair

    namespace weighted_letter {

      typedef std::pair<int, char>	      			 Letter;
      typedef AlphabetSet<Letter>			         Alphabets;
      typedef Element<Alphabets, std::set<Letter> >		  Alphabet;
      typedef AlphabetDecorator<Letter, std::set<Letter> >	 DAlphabetImpl;
      typedef Element<Alphabets, DAlphabetImpl>			 DAlphabet;

    } // weighted_letter

    namespace int_letter {

      typedef int						 Letter;
      typedef AlphabetSet<Letter>				 Alphabets;
      typedef Element<Alphabets, std::set<Letter> >		 Alphabet;
      typedef AlphabetDecorator<Letter, std::set<Letter> >	 DAlphabetImpl;
      typedef Element<Alphabets, DAlphabetImpl>			 DAlphabet;

    } // int_letter

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_PREDEFS_HH
