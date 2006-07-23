// iomanip.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_MISC_IOMANIP_HXX
# define VCSN_MISC_IOMANIP_HXX

/**
 * @file iomanip.hxx
 *
 * Definitions of the iomanip class and related functions.
 * @see vcsn::misc::iomanip.
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 */

# include <vaucanson/misc/iomanip.hh>

namespace vcsn
{
  namespace misc
  {

  /*--------.
  | iomanip |
  `--------*/

    template <class Self>
    const Self&
    iomanip<Self>::self () const
    {
      return *static_cast<const Self*> (this);
    }

    template <class IOM>
    std::ostream&
    operator<< (std::ostream& ostr, const iomanip<IOM>& m)
    {
      return m.self () (ostr);
    }

  /*-------------.
  | pword_delete |
  `-------------*/

    template <class T>
    void
    pword_delete (std::ios_base::event ev, std::ios_base &io, int idx)
    {
      if (ev == std::ios_base::erase_event)
	delete static_cast<T*> (io.pword (idx));
    }

  } // End of namespace misc.
} // End of namespace vcsn.

#endif // ! VCSN_MISC_IOMANIP_HXX
