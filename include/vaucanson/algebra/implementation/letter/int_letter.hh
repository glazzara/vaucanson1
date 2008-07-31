// int_letter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_INT_LETTER_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_INT_LETTER_HH

# include <string>
# include <iostream>

# include <vaucanson/misc/contract.hh>
# include <vaucanson/algebra/concept/letter.hh>
# include <vaucanson/algebra/concept/freemonoid_base.hh>

namespace vcsn {

  namespace algebra {

    // Specialization for int type.
    template <>
    struct letter_traits<int>;

    // Specialization for int type.
    template <typename S, typename CharContainer>
    bool op_parse(const algebra::FreeMonoidBase<S>& set,
		  std::basic_string<int>& v,
		  const std::string& s,
		  typename std::string::const_iterator& i,
		  const CharContainer& escaped);

  } // ! algebra

} // ! vcsn

namespace std {

  ostream& operator<<(ostream&, basic_string<int>);

} // ! std

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/algebra/implementation/letter/int_letter.hxx>
#endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_INT_LETTER_HH
