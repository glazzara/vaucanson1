// pair.hh: this file is part of the Vaucanson project.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//

/**
 * @file pair.hh
 *
 * @brief char_traits specialization for std::pair<U, V>.
 *
 * This file contains  char_traits specialization for std::pair<U, V>.
 * So  it   is  possible  to  use  variables   of  type  basic_string<
 * std::pair<U, V> >.
 *
 * @authors Loic Fosse <loic.fosse@lrde.epita.fr>
 * @see char_traits< std::pair<U, V> >
 */

#ifndef VCSN_MISC_CHAR_TRAITS_PAIR_HH
# define VCSN_MISC_CHAR_TRAITS_PAIR_HH

namespace std
{

  /** @addtogroup misc */ /** @{ */

  /**
   * @brief char_traits specialization for std::pair<U, V>.
   *
   * @bug  FIXME:  Only  used   functions  are  re-defined.   So  some
   *               functions and types are missing.
   */
  template <typename U, typename V>
  struct char_traits< pair<U, V> >
  {
    typedef pair<U, V> 	char_type;

    static int
    compare(const char_type* __s1, const char_type* __s2, size_t __n);

    static char_type*
    move(char_type* __s1, const char_type* __s2, size_t __n);

    static char_type*
    copy(char_type* __s1, const char_type* __s2, size_t __n);

    static char_type*
    assign(char_type* __s, size_t __n, char_type __a);
  };

  /** @} */
} // end of namespace std

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/char_traits/pair.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_MISC_CHAR_TRAITS_PAIR_HH
