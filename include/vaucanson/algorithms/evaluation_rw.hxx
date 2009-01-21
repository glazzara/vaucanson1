// evaluation_rw.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2009 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EVALUATION_RW_HXX
# define VCSN_ALGORITHMS_EVALUATION_RW_HXX

# include <vaucanson/algorithms/evaluation_rw.hh>

# include <vaucanson/algorithms/extension.hh>
# include <vaucanson/algorithms/product.hh>
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/algorithms/image.hh>

namespace vcsn
{
  template <typename SA, typename ST, typename SRET,
	    typename Auto_t, typename Trans_t, typename Ret_t>
  void
  do_evaluation_rw(const AutomataBase<SA>&,
		   const TransducerBase<ST>&,
		   const AutomataBase<SRET>&,
		   const Auto_t& a,
		   const Trans_t& t,
		   Ret_t& ret)
  {
    image(trim(product(t, extension(a, t))), ret);
  }

  template<typename SA, typename TA, typename ST,
	   typename TT, typename SRET, typename TRET>
  void
  evaluation_rw(const Element<SA, TA>& a, const Element<ST, TT>& t,
	        Element<SRET, TRET>& ret)
  {
    do_evaluation_rw(a.structure(), t.structure(), ret.structure(), a, t, ret);
  }

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_EVALUATION_RW_HXX
