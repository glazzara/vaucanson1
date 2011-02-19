// tropical_semiring.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_CYCLIC_SEMIRING_HXX
# define VCSN_ALGEBRA_CONCEPT_CYCLIC_SEMIRING_HXX

# include <vaucanson/algebra/concept/cyclic_semiring.hh>


namespace vcsn {

  namespace algebra {

    /*-----------------.
    |  CyclicSemiring  |
    `-----------------*/

    template <unsigned int n>
    bool
    CyclicSemiring<n>::operator == (const CyclicSemiring&) const
    {
      return true;
    }

  } // algebra

} // vcsn


#endif // ! VCSN_ALGEBRA_CONCEPT_CYCLIC_SEMIRING_HXX
