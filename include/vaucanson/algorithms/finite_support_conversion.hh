// finite_support_conversion.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_FINITE_SUPPORT_CONVERSION_HH
# define VCSN_ALGORITHMS_FINITE_SUPPORT_CONVERSION_HH

/**
 * @file finite_support_conversion.hh
 * @brief Conversion between finite support application types.
 *
 * This file contains a generic algorithm to convert 
 * finite support applications from one type to another.
 */

# include <vaucanson/fundamental/fundamental.hh>

namespace vcsn
{

  /** @addtogroup algorithms *//** @{ */

  /**
   * @brief Finite support conversion.
   *
   * This algorithm copies the  value of a finite  support application
   * to another, possibly changing its type.
   *
   * @param org The source application to convert.
   * @param dst The destination application.
   */
  // INTERFACE: void finite_support_convert(Exp& dst, const Serie& org) { return vcsn::finite_support_convert(dst, org); }
  // INTERFACE: void finite_support_convert(Serie& dst, const Exp& org) { return vcsn::finite_support_convert(dst, org); }
  template<typename S, typename T, typename Ss, typename Ts>
  void finite_support_convert(Element<S, T>& dst, const Element<Ss, Ts>& org);

  /** @} */

}

#include <vaucanson/algorithms/finite_support_conversion.hxx>

#endif // VCSN_ALGORITHMS_FINITE_SUPPORT_CONVERSION_HH
