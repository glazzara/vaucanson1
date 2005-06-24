// char_letter.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_CHAR_LETTER_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_CHAR_LETTER_HH

# include <vaucanson/algebra/concept/letter.hh>

namespace vcsn {

  namespace algebra {

    template <>
    struct letter_traits<char>
    {
      enum
	{
	  // Here we use 255  and not 256 since random::generate<char>
	  // does not generates 0 to avoid conflicts with 0 terminated
	  // C strings. Therefore char  alphabets will never hold more
	  // than 255 different letters.
	  cardinal = 255
	};

      static const char default_joker() { return '?'; }
      static const char default_other() { return '#'; }
    };

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_CHAR_LETTER_HH
