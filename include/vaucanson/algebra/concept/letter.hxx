// letter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_LETTER_HXX
# define VCSN_ALGEBRA_CONCEPT_LETTER_HXX

# include <string>
# include <vector>
# include <utility>

# include <vaucanson/misc/contract.hh>
# include <vaucanson/algebra/concept/letter.hh>

namespace vcsn {

  namespace algebra {

    // Dummy implementation.
    template <typename L>
    std::string
    letter_traits<L>::kind()
    {
      return 0;
    }

    // Dummy implementation.
    template <typename L>
    int
    letter_traits<L>::dim()
    {
      return 0;
    }

    // Dummy implementation.
    template <typename L>
    std::pair<bool, L>
    letter_traits<L>::literal_to_letter(const std::string&)
    {
      return std::make_pair(false, 0);
    }

    // Dummy implementation.
    template <typename L>
    std::string
    letter_traits<L>::letter_to_literal(const L&)
    {
      return 0;
    }

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_LETTER_HXX
