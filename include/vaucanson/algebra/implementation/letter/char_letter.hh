// char_letter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_CHAR_LETTER_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_CHAR_LETTER_HH

# include <string>
# include <iostream>

# include <vaucanson/misc/contract.hh>
# include <vaucanson/algebra/concept/letter.hh>
# include <vaucanson/algebra/implementation/monoid/free_monoid.hh>

namespace vcsn
{
  namespace algebra
  {
    // Specialization for char type.
    template <>
    struct letter_traits<char>;

  } // ! algebra

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/letter/char_letter.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_CHAR_LETTER_HH
