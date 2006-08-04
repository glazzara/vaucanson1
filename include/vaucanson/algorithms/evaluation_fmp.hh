// evaluation_fmp.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_EVALUATION_FMP_HH
# define VCSN_ALGORITHMS_EVALUATION_FMP_HH

# include <vaucanson/automata/concept/automata_base.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file evaluation_fmp.hh
 *
 * @brief Evaluation over normalized and sub-normalized transducers
 * seen as automata over a free monoid product.
 *
 * @author Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
 *
 * @see evaluation_fmp()
 */
/** @} */

namespace vcsn {

 /** @addtogroup algorithms *//** @{ */

 /**
   * Evaluation over normalized and sub-normalized transducers, seen
   * as automata over a free monoid product.
   */

  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename SARET, typename TARET>
  void
  evaluation_fmp(const Element<ST, TT>&,
		 const Element<SA, TA>&,
		 Element<SARET, TARET>&);

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/evaluation_fmp.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_EVALUATION_FMP_HH
