// iomanip.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_IOMANIP_HH
# define VCSN_MISC_IOMANIP_HH

/**
 * @file iomanip.hh
 *
 * Declarations of the iomanip class and related functions.
 * @see utility::iomanip.
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 */

# include <ostream>

namespace utility
{

  /**
   * Base class for IO manipulators.
   *
   * @see pword_delete().
   * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
   */
  template <class Self>
  struct iomanip : public std::unary_function<std::ostream, std::ostream>
  {
    const Self& self() const;
  };

  template <class IOM>
  std::ostream&
  operator << (std::ostream& ostr, const iomanip<IOM>& m);

  /**
   * Delete memory associated with a stream upon its destruction.
   *
   * Some manipulators allocate memory and use the internal extensible
   * array to store pointers to the allocated zone. Upon the stream's
   * destruction, the memory must be freed to avoid memory leaks.
   *
   * This function is a generic callback that will perform such a
   * destruction. idx is used as an index in the internal extensible
   * array to an element of type T*. When an erase_event is received,
   * the element idx refers to in the stream is deleted.
   *
   * @param T	Type of the pointed element.
   *
   * @arg ev	IO event.
   * @arg io	Related stream.
   * @arg idx	Index in the internal extensible array of a pointer to delete.
   *
   * @see iomanip
   * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
   */
  template <class T>
  void
  pword_delete(std::ios_base::event ev, std::ios_base &io, int idx);

} // End of namespace utility.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/iomanip.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_MISC_IOMANIP_HH
