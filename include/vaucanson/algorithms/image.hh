// image.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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

#ifndef VCSN_ALGORITHMS_IMAGE_HH
# define VCSN_ALGORITHMS_IMAGE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file image.hh
 *
 * @brief Image projection for transducers.
 *
 * @author Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
 */
/** @} */

// INTERFACE: void image(const Automaton& a, OutputProjection& b) { return vcsn::image(*a, *b); }

# include <map>

# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>

# include <vaucanson/algebra/implementation/monoid/free_monoid.hh>
# include <vaucanson/algebra/implementation/series/series.hh>

# include <vaucanson/algorithms/projection.hh>

namespace vcsn
{

  template <typename S, typename T>
  void
  image(const Element<S, T>& aut, typename output_projection_helper<S, T>::ret& res);

  template <class S, class T>
  typename output_projection_helper<S, T>::ret
  image(const Element<S, T>&,
	std::map<typename T::hstate_t, typename T::hstate_t>& m);


  /// @todo FIXME: Write a version for transducers.
  template <class S, class T>
  typename output_projection_helper<S, T>::ret
  image(const Element<S, T>&);

} // End of namespace vcsn.


# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/image.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGORITHMS_IMAGE_HH
