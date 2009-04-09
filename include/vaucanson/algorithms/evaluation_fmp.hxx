// evaluation_fmp.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EVALUATION_FMP_HXX
# define VCSN_ALGORITHMS_EVALUATION_FMP_HXX

# include <vaucanson/algorithms/evaluation_fmp.hh>
# include <vaucanson/algorithms/image.hh>
# include <vaucanson/algorithms/normalized_composition.hh>
# include <vaucanson/algorithms/sub_normalize.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>

namespace vcsn
{
  template <typename S1, typename S2, typename S3,
	    typename M1, typename M2, typename M3, typename M4,
	    typename trans_t, typename auto_t, typename res_t>
  void
  do_evaluation_fmp(const AutomataBase<S1>&,
		    const algebra::FreeMonoidProduct<M1, M2>&,
		    const AutomataBase<S2>&, const algebra::FreeMonoid<M3>&,
		    const AutomataBase<S3>&, const algebra::FreeMonoid<M4>&,
		    const trans_t& trans, const auto_t& aut, res_t& res)
  {
    trans_t id_aut(trans.structure());
    identity(aut, id_aut);
    trans_t res_composition = compose(sub_normalize(id_aut),
				      sub_normalize(trans));
    image(res_composition, res);
  }

  // FIXME: we should empty res.
  template <typename ST, typename TT>
  void
  evaluation_fmp(const Element<ST, TT>& trans,
		 const typename input_projection_helper<ST, TT>::ret& aut,
		 typename output_projection_helper<ST, TT>::ret& res)
  {
    BENCH_TASK_SCOPED("evaluation_fmp");
    do_evaluation_fmp(trans.structure(), trans.structure().series().monoid(),
		      aut.structure(), aut.structure().series().monoid(),
		      res.structure(), res.structure().series().monoid(),
		      trans, aut, res);
  }

} // End of namespace vcsn.
#endif // ! VCSN_ALGORITHMS_EVALUATION_FMP_HXX
