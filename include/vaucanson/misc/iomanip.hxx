// iomanip.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_MISC_IOMANIP_HXX
# define VCSN_MISC_IOMANIP_HXX

/**
 * @file iomanip.hxx
 *
 * Definitions of the iomanip class and related functions.
 * @see utility::iomanip.
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 */

# include <vaucanson/misc/iomanip.hh>

namespace utility
{

  /*--------.
  | iomanip |
  `--------*/

  template <class Self>
  const Self&
  iomanip<Self>::self() const
  {
    return *static_cast<const Self*> (this);
  }

  template <class IOM>
  std::ostream&
  operator << (std::ostream& ostr, const iomanip<IOM>& m)
  {
    return m.self() (ostr);
  }

  /*-------------.
  | pword_delete |
  `-------------*/

  template <class T>
  void
  pword_delete(std::ios_base::event ev, std::ios_base &io, int idx)
  {
    if (ev == std::ios_base::erase_event)
      delete static_cast<T*> (io.pword(idx));
  }

} // End of namespace utility.

#endif // ! VCSN_MISC_IOMANIP_HXX
