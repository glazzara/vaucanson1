// direction.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_DIRECTION_HH
# define VCSN_MISC_DIRECTION_HH

/**
 * @file direction.hh
 *
 * Definition of direction_type.
 */

namespace vcsn
{
  namespace misc
  {
    
    /** The orientation for some algorithms.
     *
     * @see realtime(), eps_removal()
     */
    enum direction_type { forward, backward };

  } // end of namespace misc.
} // end of namespace vcsn.


#endif // ! VCSN_MISC_DIRECTION_HH
