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

# include <climits>
# include <string>
# include <iostream>

# include <vaucanson/algebra/concept/letter.hh>
# include <vaucanson/algebra/concept/freemonoid_base.hh>

// Here are functions to manipulate pairs.

namespace vcsn
{

  namespace algebra
  {

    // Specialization for pairs.
    template <typename U, typename V>
    struct letter_traits<std::pair<U, V> >;

    // Specialization for pairs.
    template <typename S, typename U, typename V, typename CharContainer>
    bool op_parse(const algebra::FreeMonoidBase<S>& set,
		  std::basic_string<std::pair<U, V> >& v,
		  const std::string& s,
		  typename std::string::const_iterator& i,
		  const CharContainer& escaped);
  } // ! algebra

} // ! vcsn

namespace std {

  /// Display a single pair.
  ///
  /// It assumes that each element of the pair is printable
  /// (i.e. the operator<< is defined on it).
  template <typename U, typename V>
  std::ostream& operator<< (std::ostream& o, std::pair<U, V> p);

  /// Display a basic_string of pair.
  template <typename U, typename V, class Traits, class Allocator>
  std::ostream&
  operator<< (std::ostream& o,
	      std::basic_string<std::pair<U, V>, Traits, Allocator> s);

  /// Read a single pair.
  template <typename U, typename V>
  std::istream& operator>> (std::istream& i, std::pair<U, V>& p);

} // ! std

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/letter/couple_letter.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HH
