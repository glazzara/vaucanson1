// partial_rat_exp_derivation.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_DERIVATION_HH
# define VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_DERIVATION_HH

/**
 * @file partial_rat_exp_derivation.hh
 * @author Loic Fosse <loic@lrde.epita.fr>
 * @date   Fri Jul  4 11:53:07 CEST 2003
 *
 * @brief The @c derivation of @c PartialExp. (undocumented)
 *
 * This file describes the derivation on PartialExp.
 * It is for this algorithm that PartialExp was created.
 */

# include <list>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algorithms/internal/partial_rat_exp.hh>

namespace vcsn {


  // Be carefull: the exp must be realtime !
  template <class Series, class T, class Letter>
  std::pair<std::list<PartialExp<Series, T> >, bool>
  prat_exp_derivate(const Element<Series, T>& exp,
 	  	    Letter a);

  template <class Series, class T, class Letter>
  std::pair<std::list<PartialExp<Series, T> >, bool>
  prat_exp_derivate(const PartialExp<Series, T>& exp,
 	  	    Letter a);

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY && defined VCSN_USE_LIB
# include <vaucanson/algorithms/internal/partial_rat_exp_derivation.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_DERIVATION_HH
