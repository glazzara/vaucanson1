// evaluation_fmp.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_ALGORITHMS_EVALUATION_FMP_HXX
# define VCSN_ALGORITHMS_EVALUATION_FMP_HXX

# include <vaucanson/algorithms/evaluation_fmp.hh>
# include <vaucanson/algorithms/projections_fmp.hh>
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
    trans_t res_composition = normalized_composition(sub_normalize(id_aut),
						     sub_normalize(trans));
    image(res_composition, res);
  }


  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename SARES, typename TARES>
  void
  evaluation_fmp(const Element<ST, TT>& trans,
		 const Element<SA, TA>& aut,
		 Element<SARES, TARES>& res)
  {
    do_evaluation_fmp(trans.structure(), trans.structure().series().monoid(),
		      aut.structure(), aut.structure().series().monoid(),
		      res.structure(), res.structure().series().monoid(),
		      trans, aut, res);

  }

} // End of namespace vcsn.
#endif // !VCSN_ALGORITHMS_EVALUATION_FMP_HXX.
