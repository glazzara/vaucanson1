// projections_fmp.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_PROJECTIONS_FMP_HXX
# define VCSN_ALGORITHMS_PROJECTIONS_FMP_HXX

# include <vaucanson/algorithms/projections_fmp.hh>

namespace vcsn
{

  template <typename S1, typename S2, typename M1, typename M2, typename M3,
	    typename auto_t, typename trans_t>
  void
  do_domain(const AutomataBase<S1>&, const algebra::FreeMonoidProduct<M1, M2>&,
	    const AutomataBase<S2>&, const algebra::FreeMonoid<M3>&,
	    const trans_t& fmp_trans, auto_t& res)
  {
    TIMER_SCOPED("domain");
    AUTOMATON_TYPES_(trans_t, trans_);
    AUTOMATON_TYPES(auto_t);

    typedef typename trans_series_set_elt_t::support_t	trans_support_t;
    std::map<hstate_t, hstate_t>	stmap;

    const series_set_t&		series = res.structure().series();
    const monoid_t&		monoid = res.structure().series().monoid();
    const trans_monoid_t&	trans_monoid =
      fmp_trans.structure().series().monoid();

    set_states(fmp_trans, res, stmap);

    for_all_transitions(fmp_e, fmp_trans)
    {
      const trans_series_set_elt_t	trans_series_elt =
	fmp_trans.series_of(*fmp_e);
      trans_support_t			trans_supp = trans_series_elt.supp();
      const trans_monoid_elt_t	trans_monoid_elt
	(trans_monoid, *(trans_supp.begin()));
      const monoid_elt_value_t	word(trans_monoid_elt.value().first);

      series_set_elt_t		series_elt(series);

      series_elt.assoc(monoid_elt_t(monoid, word),
		       trans_series_elt.get(trans_monoid_elt));

      res.add_series_transition(stmap[fmp_trans.src_of(*fmp_e)],
				stmap[fmp_trans.dst_of(*fmp_e)], series_elt);
    }
  }


  /*-------.
  | Domain |
  `-------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  domain(const Element<S,T>& trans, Element<S2, T2>& res)
  {
    do_domain(trans.structure(), trans.structure().series().monoid(),
	      res.structure(), res.structure().series().monoid(), trans, res);
  }


  template <typename S, typename S2, typename T, typename T2>
  Element<S2, T2>
  domain(const Element<S,T>& trans)
  {
    typedef Element<S, T> trans_t;

    typedef algebra::FreeMonoid<
      typename trans_t::series_set_t::monoid_t::first_monoid_t> monoid_t;

    typedef algebra::Series<typename trans_t::series_set_t::semiring_t,
                            monoid_t>
      series_set_t;

    monoid_t				monoid
      (trans.structure().series().monoid().first_monoid());
    series_set_t			series
      (trans.structure().series().semiring(), monoid);
    Automata<series_set_t>		aut_set(series);
    Element< Automata<series_set_t>, T>	res(aut_set);

    do_domain(trans.structure(), trans.structure().series().monoid(),
	      res.structure(), res.structure().series().monoid(), trans, res);
    return res;
  }




} // End of namespace vcsn.

#endif // ! VCSN_ALGORITHMS_PROJECTIONS_FMP_HXX
