// partial_rat_exp_derivation.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_DERIVATION_HH
# define VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_DERIVATION_HH

/**
 * @file partial_rat_exp_constant_term.hh
 * @author Loic Fosse <loic@lrde.epita.fr>
 * @date   Fri Jul  4 11:53:07 CEST 2003
 * 
 * @brief The @c derivation of @c PartialExp. (undocumented)
 *
 * This file described the derivation on PartialExp.
 * It is for this algorithm that PartialExp was created.
 */

# include <list>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algorithms/internal/partial_rat_exp.hh>

namespace vcsn {


  // Be carefull: the exp must be realtime !
  template <class Series, class T, class Letter>
  std::pair<std::list<PartialExp<Series, T> >, bool>
  prat_exp_derivate(const Element<Series, T>& exp, 
 	  	    Letter a);

  template <class Series, class T, class Letter>
  std::pair<std::list<PartialExp<Series, T> >, bool>
  prat_exp_derivate(const PartialExp<Series, T>& exp, 
 	  	    Letter a);

} // vcsn

# include <vaucanson/algorithms/internal/partial_rat_exp_derivation.hxx>

#endif // VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_DERIVATION_HH