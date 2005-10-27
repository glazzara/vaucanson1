// krat_coefficient.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_COEFFICIENT_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_COEFFICIENT_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/algebra/concept/series_base.hh>

namespace vcsn {

  namespace algebra {

    template <class Series, class T>
    std::pair<typename Element<Series, T>::semiring_elt_t, Element<Series, T> >
    coefficient(const Element<Series, T>& exp);

  } // algebra

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/implementation/series/krat_coefficient.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_COEFFICIENT_HH
