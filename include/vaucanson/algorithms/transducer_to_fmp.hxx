// transducer_to_fmp.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGORITHMS_TRANSDUCER_TO_FMP_HXX
# define VCSN_ALGORITHMS_TRANSDUCER_TO_FMP_HXX

# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <map>

template<typename S, typename T,
	 typename SS, typename TT,
	 typename Self>
void
do_trans_to_fmp(const vcsn::TransducerBase<S>&,
		const vcsn::AutomataBase<SS>&,
		const vcsn::algebra::FreeMonoidProductBase<Self>&,
		const vcsn::Element<S, T>& trans,
		vcsn::Element<SS, TT>& res)
{

  //Map source states with result states
  std::map<vcsn::hstate_t, vcsn::hstate_t> m;

  //Input transducer type
  typedef vcsn::Element<S, T> Trans_t;

  //Output FMP Automaton type
  typedef vcsn::Element<SS, TT> FMP_t;

  typename FMP_t::monoid_t fmp(trans.structure().series().monoid(),
			       trans.structure().series().monoid());
  typename FMP_t::semiring_t sg;
  typename FMP_t::series_set_t ss(sg, fmp);

  typedef vcsn::Element<typename FMP_t::monoid_t::first_monoid_t, typename FMP_t::monoid_elt_value_t::first_type>
    first_monoid_elt_t;
  typedef vcsn::Element<typename FMP_t::monoid_t::second_monoid_t, typename FMP_t::monoid_elt_value_t::second_type>
    second_monoid_elt_t;
  typedef vcsn::Element<typename Trans_t::series_set_t, typename Trans_t::series_set_elt_value_t> mult_elt_t;


    /*----------------------------.
    | Creating the FMP automaton. |
    `----------------------------*/

  // Adding states
  for (typename Trans_t::state_iterator St = trans.states().begin();
       St != trans.states().end();
       ++St)
    m[*St] = res.add_state();


    /*------------------------.
    | Setting initial states. |
    `------------------------*/

  for (typename Trans_t::initial_iterator St = trans.initial().begin();
       St != trans.initial().end();
       ++St)
    {
      typename FMP_t::series_set_elt_t s(ss);
      typename FMP_t::monoid_elt_t mon(res.structure().series().monoid());
      first_monoid_elt_t first(res.structure().series().monoid().first_monoid());
      second_monoid_elt_t second(res.structure().series().monoid().second_monoid());
      typename FMP_t::semiring_elt_t weight(res.structure().series().semiring());

      mult_elt_t mult = trans.get_initial(*St);
      for_each_const_(mult_elt_t::support_t, i, mult.supp())
	{
	  first = *i;

	  typename Trans_t::semiring_elt_t output(trans.structure().series().semiring(), mult.get(*i));
	  for_each_const_(Trans_t::semiring_elt_t::support_t, j, output.supp())
	    {
	      second = *j;
	      weight = output.get(*j);
	      mon = typename FMP_t::monoid_elt_value_t(first.value(), second.value());
	      s.assoc(mon, weight);
	    }
	}
      res.set_initial(m[*St], s);
    }


    /*----------------------.
    | Setting final states. |
    `----------------------*/

  for (typename Trans_t::final_iterator St = trans.final().begin();
       St != trans.final().end();
       ++St)
    {
      typename FMP_t::series_set_elt_t s(ss);
      typename FMP_t::monoid_elt_t mon(res.structure().series().monoid());
      first_monoid_elt_t first(res.structure().series().monoid().first_monoid());
      second_monoid_elt_t second(res.structure().series().monoid().second_monoid());
      typename FMP_t::semiring_elt_t weight(res.structure().series().semiring());

      mult_elt_t mult = trans.get_final(*St);
      for_each_const_(mult_elt_t::support_t, i, mult.supp())
	{
	  first = *i;

	  typename Trans_t::semiring_elt_t output(trans.structure().series().semiring(), mult.get(*i));
	  for_each_const_(Trans_t::semiring_elt_t::support_t, j, output.supp())
	    {
	      second = *j;
	      weight = output.get(*j);
	      mon = typename FMP_t::monoid_elt_value_t(first.value(), second.value());
	      s.assoc(mon, weight);
	    }
	}
      res.set_final(m[*St], s);
    }


    /*----------------.
    | Creating edges. |
    `----------------*/

  for (typename Trans_t::edge_iterator Ed = trans.edges().begin();
       Ed != trans.edges().end();
       ++Ed)
    {
      typename FMP_t::series_set_elt_t s(ss);

      first_monoid_elt_t first(trans.structure().series().monoid());
      second_monoid_elt_t second(trans.structure().series().semiring().monoid());
      typename FMP_t::monoid_elt_t mon(res.structure().series().monoid());

      typename Trans_t::series_set_elt_t series_elt(trans.structure().series());
      series_elt = trans.series_of(*Ed);

      for (typename Trans_t::series_set_elt_t::support_t::const_iterator i = series_elt.supp().begin();
	   i != series_elt.supp().end();
	   ++i)
	{
	  first = *i;

	  typename Trans_t::semiring_elt_t mult(trans.structure().series().semiring());
	  mult = series_elt.get(first);

	  //FIXME
	  //If we don't use a copy of the support we don't get ALL the
	  //element of the series when card(mult) > 1.
	  typename Trans_t::semiring_elt_t::support_t mult_supp = mult.supp();
	  for (typename Trans_t::semiring_elt_t::support_t::const_iterator j = mult_supp.begin();
	       j != mult_supp.end();
	       ++j)
	    {
	      second = *j;

	      mon = typename FMP_t::monoid_elt_value_t(first.value(), second.value());
	      s.assoc(mon, trans.output_of(*Ed).get(second));
	    }
	}
      res.add_series_edge(m[trans.origin_of(*Ed)],
			  m[trans.aim_of(*Ed)],
			  s);
    }
}

template<typename S, typename T,
	 typename SS, typename TT>
vcsn::Element<SS, TT>&
trans_to_fmp(const vcsn::Element<S, T>& trans,
	     vcsn::Element<SS, TT>& res)
{
  do_trans_to_fmp(trans.structure(), res.structure(),
	       res.structure().series().monoid(),
	       trans, res);
  return res;
}

#endif // !VCSN_ALGORITHMS_TRANSDUCER_TO_FMP_HXX
