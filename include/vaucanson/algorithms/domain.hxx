// domain.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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

namespace vcsn
{

  /*-----------.
  | FMP_Domain |
  `-----------*/

  template <typename src_t, typename dst_t>
  void
  do_fmp_domain(const src_t& src, dst_t& dst)
  {
    TIMER_SCOPED("fmp_domain");
    AUTOMATON_TYPES_(src_t, trans_);
    AUTOMATON_TYPES(dst_t);

    typedef typename trans_series_set_elt_t::support_t	trans_support_t;
    std::map<trans_hstate_t, hstate_t>	stmap;

    const series_set_t&		series = dst.structure().series();
    const monoid_t&		monoid = dst.structure().series().monoid();
    const trans_monoid_t&	trans_monoid =
      src.structure().series().monoid();

    set_states(src, dst, stmap);

    for_all_transitions_(trans_, fmp_e, src)
    {
      const trans_series_set_elt_t	trans_series_elt =
	src.series_of(*fmp_e);
      trans_support_t			trans_supp = trans_series_elt.supp();
      const trans_monoid_elt_t	trans_monoid_elt
	(trans_monoid, *(trans_supp.begin()));
      const monoid_elt_value_t	word(trans_monoid_elt.value().first);

      series_set_elt_t		series_elt(series);

      series_elt.assoc(monoid_elt_t(monoid, word),
		       trans_series_elt.get(trans_monoid_elt));

      dst.add_series_transition(stmap[src.src_of(*fmp_e)],
				stmap[src.dst_of(*fmp_e)], series_elt);
    }
  }

// FIXME: non void version


  /*----------.
  | RW_Domain |
  `----------*/

  template <typename src_t, typename dst_t>
  void
  do_rw_domain(const src_t& src, dst_t& dst)
  {
    TIMER_SCOPED("rw_domain");
    std::map<typename src_t::hstate_t, typename dst_t::hstate_t> m;
    AUTOMATON_TYPES(src_t);

    for_all_states(p, src)
    {
      m[*p] = dst.add_state();
    }

    for_all_initial_states(p, src)
      dst.set_initial(m[*p]);

    for_all_final_states(p, src)
      dst.set_final(m[*p]);

    for_all_transitions(e, src)
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
  domain_dispatch(const S&, const Element<S,T>& src, Element<S2, T2>& dst)
  {
    do_fmp_domain(src, dst);
  }

  template <typename S, typename S2, typename T, typename T2>
  void
  domain_dispatch(const TransducerBase<S>&, const Element<S,T>& src, Element<S2, T2>& dst)
  {
    do_rw_domain(src, dst);
  }

  template <typename S, typename S2, typename T, typename T2>
  void
  domain(const Element<S,T>& src, Element<S2, T2>& dst)
  {
    domain_dispatch(src.structure(), src, dst);
  }

} // End of namespace vcsn.

#endif // ! VCSN_ALGORITHMS_DOMAIN_HXX
