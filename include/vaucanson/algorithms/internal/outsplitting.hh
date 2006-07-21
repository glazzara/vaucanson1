// outsplitting.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_OUTSPLITTING_HH
# define VCSN_ALGORITHMS_OUTSPLITTING_HH

/** @addtogroup algorithms *//** @{ */
/**
    * @file outsplitting.hh
    *
    * @brief Outsplitting and insplitting algorithms for normalized and
    * sub-normalized fmp_transducers.
    *
    * These functions allow the construction of a composed
    * transducers that respects the multiplicities.
    * (cf. the paper Inside Vaucanson, CIAA 2005)
    *
    * @author Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
    */
/** @} */

# include <set>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {
  namespace splitting {

    template <typename S, typename T>
    Element<S, T>
    outsplitting(const Element<S, T>& aut, std::set<hstate_t>& m);

    template <typename S, typename T>
    Element<S, T>
    insplitting(const Element<S, T>& aut, std::set<hstate_t>& m);

    template <typename S, typename T>
    Element<S, T>
    outsplitting(const Element<S, T>& aut);

    template <typename S, typename T>
    Element<S, T>
    insplitting(const Element<S, T>& aut);
  }
} // End of namespace vcsn.


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/internal/outsplitting.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_OUTSPLITTING_HH
