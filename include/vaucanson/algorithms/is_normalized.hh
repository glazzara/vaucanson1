// is_normalized.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_IS_NORMALIZED_HH
# define VCSN_ALGORITHMS_IS_NORMALIZED_HH

# include <vaucanson/fundamental/fundamental.hh>

/**
 * @file   is_normalized.hh
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Fri Jul  4 13:49:07 2003
 * 
 * @brief  This file contains a test for transducer normalization.
 * 
 */

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  /** 
   * @brief Test the normalization of transducer.
   * 
   * @param t the transducer to test.
   * 
   * @return true if the transducer is normalized.
   */

  template<typename S, typename A>
  bool
  is_normalized_transducer(const Element<S, A>& t);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/is_normalized.hxx>
#endif // VCSN_ALGORITHMS_IS_NORMALIZED_HH
