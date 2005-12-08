// krat_exp_expand.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_EXPAND_HH
# define VCSN_ALGORITHMS_KRAT_EXP_EXPAND_HH

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  namespace algebra {

    template <class Series, class T>
    Element<Series, T>
    expand(const Element<Series, T>& exp);

  } // algebra

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/krat_exp_expand.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_EXPAND_HH
