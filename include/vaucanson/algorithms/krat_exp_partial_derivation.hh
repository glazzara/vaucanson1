// krat_exp_partial_derivation.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HH
# define VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HH

# include <utility>
# include <set>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/algebra/concept/series_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  //! The partial derivative of the krat expression w.r.t to a letter.
  template <class Series, class T, class Letter>
  std::pair<std::set<Element<Series, T> >, bool>
  partial_derivate(const Element<Series, T>& exp, 
	   	   Letter a);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/krat_exp_partial_derivation.hxx>

#endif // VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HH
