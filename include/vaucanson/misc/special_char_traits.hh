// special_char_traits.hh: this file is part of the Vaucanson project.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_MISC_SPECIAL_CHAR_TRAITS_HH
# define VCSN_MISC_SPECIAL_CHAR_TRAITS_HH

/** @addtogroup utility *//** @{ */
/**
 * @brief This file holds specialized versions of std::char_traits for
 *        a few common types.
 *
 * If you  do not  want to have  to specialize char_traits  for common
 * types, this file may help you.  It provides generic implementations
 * of char_traits for many types. If you only want to have a framework
 * to  do  this kind  of  specialization  easily,  but with  your  own
 * specializations,   you   should   have   a   look   at   the   file
 * vaucanson/misc/char_traits.hh.
 *
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 * @see vaucanson/misc/char_traits.hh
 */
/** @} */

# include <vaucanson/misc/char_traits.hh>

# define VCSN_USE_GENERIC_CHAR_TRAITS_FOR(Type)				\
  template <>								\
  struct char_traits<Type> : public ::utility::char_traits<Type> { }

namespace std
{
  // Specialize char_traits for builtin types.
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(int);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(long int);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(unsigned int);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(unsigned long int);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(float);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(double);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(long double);

  // Specialize char_traits for pointers.
  template <class T>
  struct char_traits<T*> : public ::utility::char_traits<T*> { };

  // Specialize char_traits for pairs.
  template <class U, class V>
  struct char_traits< pair<U, V> > :
    public ::utility::char_traits< pair<U, V> >
  {
  };
} // end of namespace std

#endif // ! VCSN_MISC_SPECIAL_CHAR_TRAITS_HH
