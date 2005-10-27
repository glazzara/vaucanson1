// int_letter.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004 The Vaucanson Group.
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

# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <string>
# include <iostream>

namespace vcsn {
  // Specialization for integers.
  template <typename S, typename U, typename V>
  bool op_parse(const algebra::FreeMonoidBase<S>& set,
		std::list<int>& v,
		const std::string& s,
		typename std::string::const_iterator& i,
		const std::list<char>& escaped);

} // vcsn

namespace std {

  ostream& operator<<(ostream& o, list<int> s);

}

#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/implementation/letter/int_letter.hxx>
#endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_INT_LETTER_HH
