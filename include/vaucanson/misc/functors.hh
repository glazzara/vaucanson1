// functors.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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

#ifndef VCSN_MISC_FUNCTORS_HH
# define VCSN_MISC_FUNCTORS_HH

# include <functional>

namespace utility
{

  template <typename T>
  struct pair : public std::binary_function<T, T, std::pair<T, T > >
  {
    std::pair<T, T>	operator()(T x, T y) const;
  };


  template <typename T>
  struct discrepancy : public std::binary_function<T, T, std::pair<T, T> >
  {
    std::pair<T, T>	operator()(T x, T y) const;
  };

} // End of namespace utility.


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/functors.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_MISC_FUNCTORS_HH
