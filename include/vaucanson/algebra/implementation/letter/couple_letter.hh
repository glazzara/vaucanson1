// couple_letter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson
// Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HH

# include <vaucanson/algebra/concept/letter.hh>

// Needed to get defaults for projections.
# include <vaucanson/algebra/implementation/letter/char_letter.hh>
# include <vaucanson/algebra/implementation/letter/int_letter.hh>

// Here are functions to manipulate pairs.

namespace vcsn
{
  namespace algebra
  {
    // Specialization for pairs.
    template <typename U, typename V>
    struct letter_traits<std::pair<U, V> >;

  } // ! algebra

} // ! vcsn

namespace std
{
  template <typename U, typename V>
  std::ostream& operator<<(std::ostream&, const std::pair<U, V>&);

} // ! std

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/letter/couple_letter.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HH
