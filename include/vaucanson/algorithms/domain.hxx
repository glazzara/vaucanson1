// domain.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_DOMAIN_HXX
# define VCSN_ALGORITHMS_DOMAIN_HXX

# include <vaucanson/algorithms/domain.hh>
# include <vaucanson/algorithms/cut_up.hh>

namespace vcsn
{

  /*-----------.
  | FMP_Domain |
  `-----------*/

  template <typename src_t, typename dst_t>
  void
  do_fmp_domain(const src_t& input, dst_t& dst, bool weighted)
  {
    BENCH_TASK_SCOPED("fmp_domain");
    AUTOMATON_TYPES_(src_t, trans_);
    AUTOMATON_TYPES(dst_t);

    src_t src = cut_up(input);

    typedef typename trans_series_set_elt_t::support_t	trans_support_t;
    std::map<trans_hstate_t, hstate_t>	stmap;

    const series_set_t& series = dst.structure().series();
    const monoid_t& monoid = dst.structure().series().monoid();
    const trans_monoid_t& trans_monoid = src.structure().series().monoid();
    const semiring_elt_t& unit = src.structure().series().semiring().wone_;

    for_all_const_states(fmp_s, src)
    {
      hstate_t s = dst.add_state();
      stmap[*fmp_s] = s;

      if (src.is_initial(*fmp_s))
	{
	  const trans_series_set_elt_t trans_series_elt =
	    src.get_initial(*fmp_s);
	  trans_support_t trans_supp = trans_series_elt.supp();
	  const trans_monoid_elt_t trans_monoid_elt(trans_monoid,
						    *(trans_supp.begin()));

	  const monoid_elt_value_t word(trans_monoid_elt.value().first);

	  series_set_elt_t series_elt(series);

	  series_elt.assoc(monoid_elt_t(monoid, word),
			   weighted ?
			   trans_series_elt.get(trans_monoid_elt) : unit);
	  dst.set_initial(s, series_elt);
	}
      if (src.is_final(*fmp_s))
	{
	  const trans_series_set_elt_t trans_series_elt =
	    src.get_final(*fmp_s);
	  trans_support_t trans_supp = trans_series_elt.supp();
	  const trans_monoid_elt_t trans_monoid_elt(trans_monoid,
						    *(trans_supp.begin()));

	  const monoid_elt_value_t word(trans_monoid_elt.value().first);

	  series_set_elt_t series_elt(series);

	  series_elt.assoc(monoid_elt_t(monoid, word),
			   weighted ?
			   trans_series_elt.get(trans_monoid_elt) : unit);

	  dst.set_final(s, series_elt);
	}
    }

    for_all_const_transitions_(trans_, fmp_e, src)
    {
      const trans_series_set_elt_t trans_series_elt = src.series_of(*fmp_e);
      trans_support_t trans_supp = trans_series_elt.supp();
	for_all_const_(trans_support_t, trans_value, trans_supp)
	{
      const trans_monoid_elt_t trans_monoid_elt(trans_monoid,
						*trans_value);
      const monoid_elt_value_t word(trans_monoid_elt.value().first);

      series_set_elt_t series_elt(series);

      series_elt.assoc(monoid_elt_t(monoid, word),
		       weighted ? trans_series_elt.get(trans_monoid_elt)
		       : unit);

      dst.add_series_transition(stmap[src.src_of(*fmp_e)],
				stmap[src.dst_of(*fmp_e)], series_elt);
	}
    }
  }


  /*----------.
  | RW_Domain |
  `----------*/

  template <typename src_t, typename dst_t>
  void
  do_rw_domain(const src_t& src, dst_t& dst)
  {
    BENCH_TASK_SCOPED("rw_domain");
    std::map<typename src_t::hstate_t, typename dst_t::hstate_t> m;
    AUTOMATON_TYPES(src_t);

    for_all_const_states(p, src)
    {
      m[*p] = dst.add_state();
    }

    for_all_const_initial_states(p, src)
      dst.set_initial(m[*p]);

    for_all_const_final_states(p, src)
      dst.set_final(m[*p]);

    for_all_const_transitions(e, src)
    {
      dst.add_series_transition(m[src.src_of(*e)],
				m[src.dst_of(*e)],
				src.input_of(*e));
    }
  }

// FIXME: non void version


  /*-----------------.
  | Dispatch methods |
  `-----------------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  domain_dispatch(const AutomataBase<S>&, const Element<S,T>& src, Element<S2, T2>& dst, bool weighted)
  {
    do_fmp_domain(src, dst, weighted);
  }

  template <typename S, typename S2, typename T, typename T2>
  void
  domain_dispatch(const TransducerBase<S>&, const Element<S,T>& src, Element<S2, T2>& dst, bool)
  {
    do_rw_domain(src, dst);
  }

  template <typename S, typename S2, typename T, typename T2>
  void
  domain(const Element<S,T>& src, Element<S2, T2>& dst, bool weighted)
  {
    domain_dispatch(src.structure(), src, dst, weighted);
  }

} // End of namespace vcsn.

#endif // ! VCSN_ALGORITHMS_DOMAIN_HXX
