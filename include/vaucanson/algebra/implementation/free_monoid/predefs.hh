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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PREDEFS_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PREDEFS_HH

# include <vaucanson/algebra/implementation/alphabets/predefs.hh>
# include <vaucanson/algebra/implementation/free_monoid/str_words.hh>
# include <vaucanson/misc/char_traits.hh>

namespace vcsn {

  namespace algebra {

    namespace small_alpha_letter {

      typedef
      FreeMonoid<Alphabet>					Words;

      typedef std::basic_string<Letter,
				utility::char_traits<Letter> >	WordValue;

      typedef
      Element<Words, WordValue>			     	        Word;

    } // static_alpha_letter

    namespace char_letter {

      typedef
      FreeMonoid<Alphabet>					Words;

      typedef std::basic_string<Letter>				WordValue;

      typedef
      Element<Words, WordValue>					Word;

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

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PREDEFS_HH
