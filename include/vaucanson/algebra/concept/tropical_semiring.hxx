// tropical_semiring.hxx: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HXX
# define VCSN_ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HXX

# include <vaucanson/algebra/concept/tropical_semiring.hh>


namespace vcsn {

  namespace algebra {

    /*-----------------.
    | TropicalSemiring |
    `-----------------*/

    template <class TropicalKind>
    bool
    TropicalSemiring<TropicalKind>::operator == (const TropicalSemiring&) const
    {
      return true;
    }

  } // algebra

} // vcsn


#endif // ! VCSN_ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HXX
