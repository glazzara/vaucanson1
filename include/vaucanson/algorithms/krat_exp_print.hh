// krat_exp_print.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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

#ifndef VCSN_ALGORITHMS_KRAT_EXP_PRINT_HH
# define VCSN_ALGORITHMS_KRAT_EXP_PRINT_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file krat_exp_print.hh
 *
 * This file contains the declarations for the krat_exp_print() algorithm.
 *
 * @see krat_exp_print()
 */
/** @} */

# include <vaucanson/design_pattern/element.hh>

# include <ostream>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  enum print_modes {
    MODE_NONE, ///<<  a+b+c, a.b.c
    MODE_ADD,  ///<<  (a+b)+c
    MODE_MUL,  ///<<  (a.b).c
    MODE_ALL   ///<<  (a+b)+c, (a.b).c
  };

  /// Print a rational expression under several formats.
  template<class S, class T>
  std::ostream&
  krat_exp_print(const Element<S, T>& kexp,
		 std::ostream& ostr = std::cout,
		 const print_modes mode = MODE_NONE);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/krat_exp_print.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_KRAT_EXP_PRINT_HH
