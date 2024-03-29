// projection.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_PROJECTION_HXX
# define VCSN_ALGORITHMS_PROJECTION_HXX

# include <map>

# include <vaucanson/algorithms/projection.hh>

namespace vcsn
{
  template <typename auto_t, typename trans_t>
  void
  set_states(const trans_t& fmp_trans, auto_t& res,
	     std::map<typename trans_t::hstate_t, typename auto_t::hstate_t>&
	      stmap)
  {
    AUTOMATON_TYPES_(trans_t, trans_);
    AUTOMATON_TYPES(auto_t);

    typedef typename trans_series_set_elt_t::support_t	trans_support_t;

    const series_set_t&		series = res.structure().series();
    const monoid_t&		monoid = res.structure().series().monoid();

    for_all_const_states(fmp_s, fmp_trans)
    {
      hstate_t s = res.add_state();
      stmap[*fmp_s] = s;

      if (fmp_trans.is_initial(*fmp_s))
      {
	trans_series_set_elt_t	in = fmp_trans.get_initial(*fmp_s);
	trans_support_t		supp = in.supp();

	semiring_elt_t		in_semi_elt = in.get(*(supp.begin()));
	series_set_elt_t	series_elt(series);

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

	semiring_elt_t		out_semi_elt = out.get(*(supp.begin()));
	series_set_elt_t	series_elt(series);

	series_elt.assoc(monoid_elt_t(monoid,
				      algebra::identity_as<
				      monoid_elt_value_t>::
				      of(monoid).value()),
			 out_semi_elt);
	res.set_final(s, series_elt);
      }
    }
  }

  /*---------.
  | Identity |
  `---------*/

  template <typename S1, typename S2, typename M1, typename M2,
	    typename auto_t, typename trans_t>
  void
  do_identity(const AutomataBase<S1>&,
	      const algebra::FreeMonoidBase<M1>&,
	      const AutomataBase<S2>&,
	      const algebra::FreeMonoidProduct<M1,M2>&,
	      const auto_t& aut, trans_t& res)
  {
    BENCH_TASK_SCOPED("identity");
    AUTOMATON_TYPES_(auto_t, aut_);
    AUTOMATON_TYPES(trans_t);

    std::map<hstate_t, aut_hstate_t>	stmap;
    typedef typename aut_series_set_elt_t::support_t	aut_support_t;

    const series_set_t&		series = res.structure().series();
    const monoid_t&		monoid = res.structure().series().monoid();
    const aut_monoid_t&		aut_monoid = aut.structure().series().monoid();

    set_states(aut, res, stmap);

    for_all_const_transitions_(aut_, aut_e, aut)
    {
      const aut_series_set_elt_t aut_series_elt = aut.series_of(*aut_e);

      // If the transition is labeled by a+bc, we want to output
      // two transitions labeled by (a,a) and (bc,bc).
      aut_support_t aut_supp = aut_series_elt.supp();
      for_all_const_(aut_support_t, label, aut_supp)
	{
	  const aut_monoid_elt_t aut_monoid_elt(aut_monoid, *label);
	  const monoid_elt_value_t word(aut_monoid_elt.value(),
					aut_monoid_elt.value());

	  series_set_elt_t series_elt(series);
	  series_elt.assoc(monoid_elt_t(monoid, word),
			   aut_series_elt.get(aut_monoid_elt));

	  res.add_series_transition(stmap[aut.src_of(*aut_e)],
				    stmap[aut.dst_of(*aut_e)], series_elt);
	}
    }
  }

  template <typename S, typename S2, typename T, typename T2>
  void
  identity(const Element<S,T>& aut, Element<S2, T2>& res)
  {
    do_identity(aut.structure(), aut.structure().series().monoid(),
		res.structure(), res.structure().series().monoid(), aut, res);
  }

  /*--------------.
  | Partial erase |
  `--------------*/

  template <typename S1, typename S2, typename M1, typename M2,
	    typename auto_t, typename trans_t>
  void
  do_partial_erase(const AutomataBase<S1>&,
	      const algebra::FreeMonoidBase<M1>&,
	      const AutomataBase<S2>&,
	      const algebra::FreeMonoidProduct<M1,M2>&,
	      const auto_t& aut, trans_t& res)
  {
    BENCH_TASK_SCOPED("partial erase");
    AUTOMATON_TYPES_(auto_t, aut_);
    AUTOMATON_TYPES(trans_t);

    std::map<hstate_t, aut_hstate_t>	stmap;
    typedef typename aut_series_set_elt_t::support_t	aut_support_t;

    const series_set_t&		series = res.structure().series();
    const monoid_t&		monoid = res.structure().series().monoid();
    const aut_monoid_t&		aut_monoid = aut.structure().series().monoid();
    aut_monoid_elt_value_t empty_word =
    		algebra::identity_as<aut_monoid_elt_value_t>::of(aut_monoid).value();

    set_states(aut, res, stmap);

    for_all_const_transitions_(aut_, aut_e, aut)
    {
      const aut_series_set_elt_t aut_series_elt = aut.series_of(*aut_e);

      // If the transition is labeled by a+bc, we want to output
      // two transitions labeled by (a,a) and (bc,bc).
      aut_support_t aut_supp = aut_series_elt.supp();
      for_all_const_(aut_support_t, label, aut_supp)
	{
	  const aut_monoid_elt_t aut_monoid_elt(aut_monoid, *label);
	  const monoid_elt_value_t word(aut_monoid_elt.value(),
					empty_word);

	  series_set_elt_t series_elt(series);
	  series_elt.assoc(monoid_elt_t(monoid, word),
			   aut_series_elt.get(aut_monoid_elt));

	  res.add_series_transition(stmap[aut.src_of(*aut_e)],
				    stmap[aut.dst_of(*aut_e)], series_elt);
	}
    }
  }

  template <typename S, typename S2, typename T, typename T2>
  void
  partial_erase(const Element<S,T>& aut, Element<S2, T2>& res)
  {
    do_partial_erase(aut.structure(), aut.structure().series().monoid(),
		res.structure(), res.structure().series().monoid(), aut, res);
  }

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_PROJECTION_HXX
