// iomanip.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004 The Vaucanson Group.
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
# include <functional>

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
