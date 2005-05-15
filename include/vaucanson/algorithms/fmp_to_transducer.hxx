// fmp_to_transducer.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGORITHMS_FMP_TO_TRANSDUCER_HXX
# define VCSN_ALGORITHMS_FMP_TO_TRANSDUCER_HXX

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>

# include <map>

template<typename S, typename T,
	 typename SS, typename TT,
	 typename Self>
void
do_fmp_to_trans(const vcsn::AutomataBase<S>&,
		const vcsn::TransducerBase<SS>&,
		const vcsn::algebra::FreeMonoidProductBase<Self>&,
		const vcsn::Element<S, T>& fmp,
		vcsn::Element<SS, TT>& res)
{
  // Map source automaton's states with result's states
  std::map<vcsn::hstate_t, vcsn::hstate_t> m;

  // Input FMP type
  typedef vcsn::Element<S, T> FMP_t;

  // Output transducer type
  typedef vcsn::Element<SS, TT> Trans_t;

  /*-------------------------.
  | Creating the transducer. |
  `-------------------------*/

  // Adding states
  for (typename FMP_t::state_iterator St = fmp.states().begin();
       St != fmp.states().end();
       ++St)
    m[*St] = res.add_state();


  /*-------------------------.
  | Setting initial states.  |
  `-------------------------*/

  for (typename FMP_t::initial_iterator St = fmp.initial().begin();
       St != fmp.initial().end();
       ++St)
    {
      //Series to be created
      typename Trans_t::series_set_elt_t s(res.structure().series());

      typename FMP_t::series_set_elt_t s_elt = fmp.get_initial(*St);
      for_each_const_(FMP_t::series_set_elt_t::support_t, i, s_elt.supp())
	{
	  typename Trans_t::semiring_elt_value_t::monoid_elt_value_t output_monoid_value;
	  typename Trans_t::semiring_elt_t::semiring_elt_t weight;

	  typename Trans_t::monoid_elt_value_t input_monoid_value = (*i).first;
	  typename Trans_t::monoid_elt_t input_monoid(res.structure().series().monoid(),
						      input_monoid_value);

	  typename Trans_t::semiring_elt_t::monoid_elt_t output_monoid(res.structure().series().semiring().monoid(), (*i).second);
	  weight = s_elt.get(*i);

	  //Creating the element multiplicity
	  typename Trans_t::semiring_elt_t out_mult(res.structure().series().semiring());
	  out_mult.assoc(output_monoid, weight);

	  //Associating it to the input monoid
	  s.assoc(input_monoid, out_mult);
	}
      res.set_initial(m[*St], s);
    }


  /*------------------------.
  | Setting final states.   |
  `------------------------*/

  for (typename FMP_t::final_iterator St = fmp.final().begin();
       St != fmp.final().end();
       ++St)
    {
      //Series to be created
      typename Trans_t::series_set_elt_t s(res.structure().series());

      typename FMP_t::series_set_elt_t s_elt = fmp.get_final(*St);
      for_each_const_(FMP_t::series_set_elt_t::support_t, i, s_elt.supp())
	{
	  typename Trans_t::semiring_elt_value_t::monoid_elt_value_t output_monoid_value;
	  typename Trans_t::semiring_elt_t::semiring_elt_t weight;

	  typename Trans_t::monoid_elt_value_t input_monoid_value = (*i).first;
	  typename Trans_t::monoid_elt_t input_monoid(res.structure().series().monoid(),
						      input_monoid_value);

	  typename Trans_t::semiring_elt_t::monoid_elt_t output_monoid(res.structure().series().semiring().monoid(), (*i).second);
	  weight = s_elt.get(*i);

	  //Creating the element multiplicity
	  typename Trans_t::semiring_elt_t out_mult(res.structure().series().semiring());
	  out_mult.assoc(output_monoid, weight);

	  //Associating it to the input monoid
	  s.assoc(input_monoid, out_mult);
	}
      res.set_final(m[*St], s);
    }


  /*-----------------.
  | Creating edges.  |
  `-----------------*/

  for (typename FMP_t::edge_iterator Ed = fmp.edges().begin();
       Ed != fmp.edges().end();
       ++Ed)
    {
      // FIXME
      // No Special Treatment is done for 0 weighted
      typename Trans_t::series_set_elt_t edge_value(res.structure().series());

      typename Trans_t::monoid_elt_value_t input_monoid_value;
      typename Trans_t::semiring_elt_value_t::monoid_elt_value_t output_monoid_value;

      typename FMP_t::series_set_elt_t series_fmp(fmp.structure().series());
      typename Trans_t::semiring_elt_t out_mult(res.structure().series().semiring());
      series_fmp = fmp.series_of(*Ed);

      for_each_const_(FMP_t::series_set_elt_t::support_t, i, series_fmp.supp())
	{
	  input_monoid_value = (*i).first;
 	  output_monoid_value = (*i).second;

	  //Creating the edge's semiring value
 	  typename Trans_t::semiring_elt_t::semiring_elt_t
 	    edge_weight(res.structure().series().semiring().semiring(),
			series_fmp.get(*i));
	  typename Trans_t::semiring_elt_t out_mult(res.structure().series().semiring());
 	  out_mult.assoc(typename Trans_t::semiring_elt_t::monoid_elt_t(res.structure().series().semiring().monoid(), output_monoid_value), edge_weight);

	  //Creating the edge's monoid value
	  typename Trans_t::monoid_elt_t input(res.structure().series().monoid(),
					       input_monoid_value);
	  edge_value.assoc(input, out_mult);
	  res.add_series_edge(m[fmp.origin_of(*Ed)],
			      m[fmp.aim_of(*Ed)],
			      edge_value);
	}
    }
}

template<typename S, typename T,
	 typename SS, typename TT>
vcsn::Element<SS, TT>&
fmp_to_trans(const vcsn::Element<S, T>& fmp,
	  vcsn::Element<SS, TT>& res)
{
  do_fmp_to_trans(fmp.structure(), res.structure(),
	       fmp.structure().series().monoid(),
	       fmp, res);
  return res;
}

#endif // !VCSN_ALGORITHMS_FMP_TO_TRANSDUCER_HXX
