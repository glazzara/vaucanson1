// is_realtime.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_IS_REALTIME_HH
# define VCSN_ALGORITHMS_IS_REALTIME_HH

/** @addtogroup algorithms */  /** @{ */
/**
 * @file   is_realtime.hh
 *
 * Test for realtime transducers.
 *
 * @author Yann R�gis-Gianas <yann@lrde.epita.fr>
 * @date   Fri Jul  4 13:49:07 2003
 *
 * @see is_realtime()
 */
/** @} */

# include <vaucanson/algorithms/realtime.hh>

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/is_realtime.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_IS_REALTIME_HH
