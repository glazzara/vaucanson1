// image.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
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

# include <map>

# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algebra/implementation/free_monoid/words.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/algorithms/projection.hh>

namespace vcsn
{

  template <typename S, typename S2, typename T, typename T2>
  void
  image(const Element<S,T>& aut, Element<S2, T2>& res);


  template <class S, class T>
  typename output_projection_helper<S, T>::ret
  image(const Element<S, T>&,
	std::map<hstate_t, hstate_t>& m);


  /// @todo FIXME: Write a version for transducers.
  template <class S, class T>
  typename output_projection_helper<S, T>::ret
  image(const Element<S, T>&);

} // End of namespace vcsn.


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/image.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGORITHMS_IMAGE_HH
