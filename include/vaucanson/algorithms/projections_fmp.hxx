// projections_fmp.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.
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
  template <typename auto_t, typename trans_t>
  static void
  set_states(const trans_t& fmp_trans, auto_t& res,
	     std::map<hstate_t, hstate_t>& stmap)
  {
    AUTOMATON_TYPES_(trans_t, trans_);
    AUTOMATON_TYPES(auto_t);

    typedef typename trans_series_set_elt_t::support_t	trans_support_t;

    const series_set_t&		series = res.structure().series();
    const monoid_t&		monoid = res.structure().series().monoid();

    for_each_state(fmp_s, fmp_trans)
      {
	hstate_t s = res.add_state();
	stmap[*fmp_s] = s;

	if (fmp_trans.is_initial(*fmp_s))
	  {
	    trans_series_set_elt_t	in = fmp_trans.get_initial(*fmp_s);
	    trans_support_t		supp = in.supp();

	    semiring_elt_t		in_semi_elt = in.get(*(supp.begin()));
	    series_set_elt_t		series_elt(series);

	    series_elt.assoc(monoid_elt_t(monoid,
					  algebra::identity_as<
					  monoid_elt_value_t>::
					  of(monoid).value()),
			     in_semi_elt);
	    res.set_initial(s, series_elt);
	  }

	if (fmp_trans.is_final(*fmp_s))
	  {
	    trans_series_set_elt_t	out = fmp_trans.get_final(*fmp_s);
	    trans_support_t		supp = out.supp();

	    semiring_elt_t		out_semi_elt =
	      out.get(*(supp.begin()));
	    series_set_elt_t		series_elt(series);

	    series_elt.assoc(monoid_elt_t(monoid,
					  algebra::identity_as<
					  monoid_elt_value_t>::
					  of(monoid).value()),
			     out_semi_elt);
	    res.set_final(s, series_elt);
	  }
      }
  }

  template <typename S1, typename S2, typename M1, typename M2, typename M3,
	    typename auto_t, typename trans_t>
  void
  do_domain(const AutomataBase<S1>&, const algebra::FreeMonoidProduct<M1, M2>&,
	    const AutomataBase<S2>&, const algebra::FreeMonoid<M3>&,
	    const trans_t& fmp_trans, auto_t& res)
  {
    AUTOMATON_TYPES_(trans_t, trans_);
    AUTOMATON_TYPES(auto_t);

    typedef typename trans_series_set_elt_t::support_t	trans_support_t;
    std::map<hstate_t, hstate_t>	stmap;

    const series_set_t&		series = res.structure().series();
    const monoid_t&		monoid = res.structure().series().monoid();
    const trans_monoid_t&	trans_monoid =
      fmp_trans.structure().series().monoid();

    set_states(fmp_trans, res, stmap);

    for_each_edge(fmp_e, fmp_trans)
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

	res.add_series_edge(stmap[fmp_trans.origin_of(*fmp_e)],
			    stmap[fmp_trans.aim_of(*fmp_e)], series_elt);
      }
  }

  template <typename S1, typename S2, typename M1, typename M2,
	    typename auto_t, typename trans_t>
  void
  do_image(const AutomataBase<S1>&, const algebra::FreeMonoidProduct<M1, M2>&,
	   const AutomataBase<S2>&, const algebra::FreeMonoidBase<M2>&,
	   const trans_t& fmp_trans, auto_t& res)
  {
    AUTOMATON_TYPES_(trans_t, trans_);
    AUTOMATON_TYPES(auto_t);

    typedef typename trans_series_set_elt_t::support_t	trans_support_t;
    std::map<hstate_t, hstate_t>	stmap;

    const series_set_t&		series = res.structure().series();
    const monoid_t&		monoid = res.structure().series().monoid();
    const trans_monoid_t&	trans_monoid =
      fmp_trans.structure().series().monoid();

    set_states(fmp_trans, res, stmap);

    for_each_edge(fmp_e, fmp_trans)
      {
	const trans_series_set_elt_t	trans_series_elt =
	  fmp_trans.series_of(*fmp_e);
	trans_support_t			trans_supp = trans_series_elt.supp();
	const trans_monoid_elt_t	trans_monoid_elt
	  (trans_monoid, *(trans_supp.begin()));

	const monoid_elt_value_t	word(trans_monoid_elt.value().second);

	series_set_elt_t		series_elt(series);

	series_elt.assoc(monoid_elt_t(monoid, word),
			 trans_series_elt.get(trans_monoid_elt));

	res.add_series_edge(stmap[fmp_trans.origin_of(*fmp_e)],
			    stmap[fmp_trans.aim_of(*fmp_e)], series_elt);
      }
  }

  template <typename S1, typename S2, typename M1, typename M2,
	    typename auto_t, typename trans_t>
  void
  do_identity(const AutomataBase<S1>&,
	      const algebra::FreeMonoidBase<M1>&,
	      const AutomataBase<S2>&,
	      const algebra::FreeMonoidProduct<M1,M2>&,
	      const auto_t& aut, trans_t& res)
  {
    AUTOMATON_TYPES_(auto_t, aut_);
    AUTOMATON_TYPES(trans_t);

    std::map<hstate_t, hstate_t>	stmap;
    typedef typename aut_series_set_elt_t::support_t	aut_support_t;

    const series_set_t&		series = res.structure().series();
    const monoid_t&		monoid = res.structure().series().monoid();
    const aut_monoid_t&		aut_monoid = aut.structure().series().monoid();

    set_states(aut, res, stmap);

    for_each_edge(aut_e, aut)
      {
	const aut_series_set_elt_t	aut_series_elt =
	  aut.series_of(*aut_e);
	aut_support_t			aut_supp = aut_series_elt.supp();
	const aut_monoid_elt_t	aut_monoid_elt
	  (aut_monoid, *(aut_supp.begin()));
	const monoid_elt_value_t	word(aut_monoid_elt.value(),
					     aut_monoid_elt.value());

	series_set_elt_t		series_elt(series);

	series_elt.assoc(monoid_elt_t(monoid, word),
			 aut_series_elt.get(aut_monoid_elt));

	res.add_series_edge(stmap[aut.origin_of(*aut_e)],
			    stmap[aut.aim_of(*aut_e)], series_elt);
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


  /*------.
  | Image |
  `------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  image(const Element<S,T>& trans, Element<S2, T2>& res)
  {
    do_image(trans.structure(), trans.structure().series().monoid(),
	     res.structure(), res.structure().series().monoid(), trans, res);
  }


  template <typename S, typename S2, typename T, typename T2>
  Element<S2, T2>
  image(const Element<S,T>& trans)
  {
    typedef Element<S, T> trans_t;

    typedef algebra::FreeMonoid<
      typename trans_t::series_set_t::monoid_t::second_monoid_t> monoid_t;

    typedef algebra::Series<typename trans_t::series_set_t::semiring_t,
			    monoid_t>
      series_set_t;

    monoid_t				monoid
      (trans.structure().series().monoid().second_monoid());
    series_set_t			series
      (trans.structure().series().semiring(), monoid);
    Automata<series_set_t>		aut_set(series);
    Element< Automata<series_set_t>, T>	res(aut_set);

    do_image(trans.structure(), trans.structure().series().monoid(),
	     res.structure(), res.structure().series().monoid(), trans, res);
    return res;
  }


  /*---------.
  | Identity |
  `---------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  identity(const Element<S,T>& aut, Element<S2, T2>& res)
  {
    do_identity(aut.structure(), aut.structure().series().monoid(),
		res.structure(), res.structure().series().monoid(), aut, res);
  }

  template <typename S, typename S2, typename T, typename T2>
  Element<S2, T2>
  identity(const Element<S,T>& aut)
  {
    typedef Element<S, T> auto_t;

    typedef algebra::FreeMonoidProduct<
      typename auto_t::series_set_t::monoid_t,
      typename auto_t::series_set_t::monoid_t> monoid_t;

    typedef algebra::Series<typename auto_t::series_set_t::semiring_t,
			    monoid_t>
      series_set_t;

    monoid_t		monoid (aut.structure().series().monoid(),
				aut.structure().series().monoid());

    series_set_t			series
      (aut.structure().series().semiring(), monoid);
    Automata<series_set_t>		aut_set(series);
    Element< Automata<series_set_t>, T>	res(aut_set);

    do_identity(aut.structure(), aut.structure().series().monoid(),
		res.structure(), res.structure().series().monoid(), aut, res);
    return res;
  }


} // End of namespace vcsn.

#endif // ! VCSN_ALGORITHMS_PROJECTIONS_FMP_HXX
