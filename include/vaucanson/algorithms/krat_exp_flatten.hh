// krat_exp_flatten.hh: this file is part of the Vaucanson project.
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
 * @brief This file holds the declaration of the flatten algorithm.
 *
 * This is the  header file for the flatten  algorithm. This algorithm
 * extracts the letters from a rational expression and store them in a
 * list.
 *
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 * @see flatten()
 */

#ifndef VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HH
# define VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HH

# include <vaucanson/design_pattern/element.hh>

# include <list>

namespace vcsn
{

  /** @addtogroup algorithms */ /** @{ */

  /**
   * @brief This algorithm extracts the letters from a rational expression.
   *
   * The  flatten()  function  extracts  the  letters  of  a  rational
   * expression,  keeping  the  order  in  which they  appear  in  the
   * expression.   The result  is just  a std::list  of  letters, with
   * letters  having the same  type as  the expression's  letter, i.e.
   * Element<S, T>::monoid_elt_t::set_t::alphabet_t::letter_t.
   *
   * @param exp The expression to work on.
   *
   * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
   */

  template <class Series, class T>
  std::list<typename Series::monoid_t::alphabet_t::letter_t>
  flatten(const Element<Series, T>& exp);

  /** @} */

} // end of namespace vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/krat_exp_flatten.hxx>
# endif

#endif // VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HH
