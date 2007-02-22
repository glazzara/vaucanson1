// realtime_to_fmp.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_REALTIME_TO_FMP_HXX
# define VCSN_ALGORITHMS_REALTIME_TO_FMP_HXX

# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <map>

namespace vcsn
{
  template<typename S, typename T,
	   typename SS, typename TT,
	   typename Self>
  void
  do_realtime_to_fmp(const vcsn::TransducerBase<S>&,
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

    typedef vcsn::Element<typename FMP_t::monoid_t::first_monoid_t,
      typename FMP_t::monoid_elt_value_t::first_type>
      first_monoid_elt_t;
    typedef vcsn::Element<typename FMP_t::monoid_t::second_monoid_t,
      typename FMP_t::monoid_elt_value_t::second_type>
      second_monoid_elt_t;
    typedef vcsn::Element<typename Trans_t::series_set_t,
      typename Trans_t::series_set_elt_value_t>
      mult_elt_t;


    /*----------------------------.
    | Creating the FMP automaton. |
    `----------------------------*/

    // Adding states
    for (typename Trans_t::state_iterator St = trans.states().begin();
	 St != trans.states().end();
	 ++St)
      m[*St] = res.add_state();

    typename Trans_t::series_set_elt_t id_series(trans.structure().series());
    id_series = vcsn::algebra::
      identity_as<typename Trans_t::series_set_elt_value_t>::
      of(trans.structure().series());


    /*------------------------.
    | Setting initial states. |
    `------------------------*/

    for (typename Trans_t::initial_iterator St, next = trans.initial.begin();
	 next != trans.initial.end();)
    {
      //We need to store the next iterator before using the current one
      //to avoid an invalid iterator after having called set_final.
      //Indeed, set_final can delete the iterator if its second parameter
      //is the zero of the serie.
      St = next;
      next++;

      typename FMP_t::series_set_elt_t s(ss);
      typename FMP_t::monoid_elt_t mon(res.structure().series().monoid());
      first_monoid_elt_t
	first(res.structure().series().monoid().first_monoid());
      second_monoid_elt_t
	second(res.structure().series().monoid().second_monoid());
      typename FMP_t::semiring_elt_t
	weight(res.structure().series().semiring());

      mult_elt_t mult = trans.get_initial(*St);
      if (mult != id_series)
      {
	hstate_t tmp = res.add_state();
	typename mult_elt_t::support_t mult_supp = mult.supp();
	for_all_const_(mult_elt_t::support_t, i, mult_supp)
	{
	  first = *i;

	  typename Trans_t::semiring_elt_t
	    output(trans.structure().series().semiring(), mult.get(*i));
	  typename Trans_t::semiring_elt_t::support_t
	    output_supp = output.supp();
	  for_all_const_(Trans_t::semiring_elt_t::support_t,
			 j,
			 output_supp)
	  {
	    second = *j;
	    weight = output.get(*j);
	    mon = typename FMP_t::monoid_elt_value_t(first.value(),
						     second.value());
	    s.assoc(mon, weight);
	  }
	}
	res.add_series_transition(tmp, m[*St], s);
	res.set_initial(tmp);
      }
      else
	res.set_initial(m[*St]);
    }


    /*----------------------.
    | Setting final states. |
    `----------------------*/

    for (typename Trans_t::final_iterator St, next = trans.final.begin();
	 next != trans.final.end();)
    {
      //We need to store the next iterator before using the current one
      //to avoid an invalid iterator after having called set_final.
      //Indeed, set_final can delete the iterator if its second parameter
      //is the zero of the serie.
      St = next;
      next++;

      typename FMP_t::series_set_elt_t s(ss);
      typename FMP_t::monoid_elt_t mon(res.structure().series().monoid());
      first_monoid_elt_t
	first(res.structure().series().monoid().first_monoid());
      second_monoid_elt_t
	second(res.structure().series().monoid().second_monoid());
      typename FMP_t::semiring_elt_t
	weight(res.structure().series().semiring());

      mult_elt_t mult = trans.get_final(*St);
      if (mult != id_series)
      {
	hstate_t tmp = res.add_state();

	typename mult_elt_t::support_t mult_supp = mult.supp();
	for_all_const_(mult_elt_t::support_t, i, mult_supp)
	{
	  first = *i;

	  typename Trans_t::semiring_elt_t
	    output(trans.structure().series().semiring(), mult.get(*i));
	  typename Trans_t::semiring_elt_t::support_t
	    output_supp = output.supp();
	  for_all_const_(Trans_t::semiring_elt_t::support_t,
			 j,
			 output_supp)
	  {
	    second = *j;
	    weight = output.get(*j);
	    mon = typename FMP_t::monoid_elt_value_t(first.value(),
						     second.value());
	    s.assoc(mon, weight);
	  }
	}
	res.add_series_transition(m[*St], tmp, s);
	res.set_final(tmp);
      }
      else
	res.set_final(m[*St]);
    }


    /*-----------------------.
    | Creating transitions.  |
    `-----------------------*/

    for (typename Trans_t::transition_iterator Ed = trans.transitions().begin();
	 Ed != trans.transitions().end();
	 ++Ed)
    {
      typename FMP_t::series_set_elt_t s(ss);

      first_monoid_elt_t first(trans.structure().series().monoid());
      second_monoid_elt_t
	second(trans.structure().series().semiring().monoid());
      typename FMP_t::monoid_elt_t
	mon(res.structure().series().monoid());

      typename Trans_t::series_set_elt_t
	series_elt(trans.structure().series());
      series_elt = trans.series_of(*Ed);

      for (typename Trans_t::series_set_elt_t::support_t::const_iterator
	     i = series_elt.supp().begin();
	   i != series_elt.supp().end();
	   ++i)
      {
	first = *i;

	typename Trans_t::semiring_elt_t
	  mult(trans.structure().series().semiring());
	mult = series_elt.get(first);

	//FIXME
	//If we don't use a copy of the support we don't get ALL the
	//element of the series when card(mult) > 1.
	typename Trans_t::semiring_elt_t::support_t
	  mult_supp = mult.supp();
	for (typename Trans_t::semiring_elt_t::support_t::const_iterator
	       j = mult_supp.begin();
	     j != mult_supp.end();
	     ++j)
	{
	  second = *j;

	  mon = typename FMP_t::monoid_elt_value_t(first.value(),
						   second.value());
	  s.assoc(mon, trans.output_of(*Ed).get(second));
	}
      }
      res.add_series_transition(m[trans.src_of(*Ed)],
				m[trans.dst_of(*Ed)],
				s);
    }
  }

  template<typename S, typename T,
	   typename SS, typename TT>
  vcsn::Element<SS, TT>&
  realtime_to_fmp(const vcsn::Element<S, T>& trans,
		  vcsn::Element<SS, TT>& res)
  {
    do_realtime_to_fmp(trans.structure(), res.structure(),
		       res.structure().series().monoid(),
		       trans, res);
    return res;
  }
}

#endif // ! VCSN_ALGORITHMS_REALTIME_TO_FMP_HXX
