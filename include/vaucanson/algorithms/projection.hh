// projection.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_PROJECTION_HH
# define VCSN_ALGORITHMS_PROJECTION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file projection.hh
 *
 * Undocumented stuff.
 *
 * @bug FIXME: Document!
 */
/** @} */

#include <vaucanson/automata/concept/transducer.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  // Erase input.
  template <class ST, class TT,
	    class SA, class TA>
  void
  output_projection(const Element<ST, TT>&,
		    Element<SA, TA>&);

  template <class S, class T>
  typename output_projection_helper<S, T>::ret
  output_projection(const Element<S, T>&,
		    std::map<hstate_t, hstate_t>& m);

  template <class S, class T>
  typename output_projection_helper<S, T>::ret
  output_projection(const Element<S, T>&);

  template <class S, class T>
  typename input_projection_helper<S, T>::ret
  input_projection(const Element<S, T>&);

  /** @} */

}

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/projection.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_PROJECTION_HH
