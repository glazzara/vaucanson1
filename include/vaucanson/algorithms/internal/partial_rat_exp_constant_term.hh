// partial_rat_exp_constant_term.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_CONSTANT_TERM_HH
# define VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_CONSTANT_TERM_HH

/**
 * @file partial_rat_exp_constant_term.hh
 * @author Loic Fosse <loic@lrde.epita.fr>
 * @date   Fri Jul  4 11:53:07 CEST 2003
 *
 * @brief The @c constant_term of @c PartialExp. (undocumented)
 *
 * This file described overloaded version of constant_term applied
 * on @c PartialExp.
 */

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/algorithms/internal/partial_rat_exp.hh>
# include <utility>

namespace vcsn {

  template <class Series, class T>
  std::pair<typename Element<Series, T>::semiring_elt_t, bool>
  constant_term(const PartialExp<Series, T>& exp);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algorithms/internal/partial_rat_exp_constant_term.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_CONSTANT_TERM_HH
