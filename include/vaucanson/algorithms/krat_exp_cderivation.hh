// krat_exp_cderivation.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HH
# define VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file krat_exp_cderivation.hh
 *
 * This file contains the declaration for the cderivate() algorithms.
 *
 * @see cderivate(), word_cderivate()
 */
/** @} */

// INTERFACE: Exp cderivate(const Exp& e, char l) { return vcsn::cderivate(e, l); }

// INTERFACE: Exp cderivate(const Exp& e, const std::string& w) { return vcsn::word_cderivate(e, Series::monoid_elt_t(e.set().monoid(), w)); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/algebra/concept/series_base.hh>

namespace vcsn {

  /** @addtogroup algorithms */  /** @{ */

  /// The c-derivative of the krat expression w.r.t to a letter.
  template <class Series, class T, class Letter>
  Element<Series, T>
  cderivate(const Element<Series, T>& exp,
	   Letter a);

  /// The c-derivative of the krat expression w.r.t to a word.
  template <class Series, class T, class Word>
  Element<Series, T>
  word_cderivate(const Element<Series, T>& exp,
		Word a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/krat_exp_cderivation.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HH
