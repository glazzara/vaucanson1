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

#ifndef   	VCSN_ALGORITHMS_IMAGE_HXX
# define   	VCSN_ALGORITHMS_IMAGE_HXX

# include <vaucanson/algorithms/image.hh>
# include <vaucanson/algorithms/projection.hh>

namespace vcsn
{
  template <typename auto_t, typename trans_t>
  static void
  do_fmp_image(const trans_t& fmp_trans, auto_t& res)
  {
    TIMER_SCOPED("image");
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

      const monoid_elt_value_t	word(trans_monoid_elt.value().second);

      series_set_elt_t		series_elt(series);

      series_elt.assoc(monoid_elt_t(monoid, word),
		       trans_series_elt.get(trans_monoid_elt));

      res.add_series_transition(stmap[fmp_trans.src_of(*fmp_e)],
				stmap[fmp_trans.dst_of(*fmp_e)], series_elt);
    }
  }



  template<typename Trans_t, typename Auto_t>
  static void
  do_rw_image(const Trans_t& t,
	      Auto_t& ret)
  {
    TIMER_SCOPED("image (transducer to automaton)");
    AUTOMATON_TYPES(Trans_t);

    std::map<hstate_t, hstate_t> m;

    for_all_states(p, t)
      m[*p] = ret.add_state();

    monoid_elt_t empty =
      algebra::identity_as<monoid_elt_value_t>::of(t.series().monoid());
    typename Trans_t::series_set_elt_t id_series(t.structure().series());
    id_series = vcsn::algebra::
      identity_as<typename Trans_t::series_set_elt_value_t>::
      of(t.structure().series());

    for_all_initial_states(p, t)
    {
      if (t.get_initial(*p) != id_series)
      {
	hstate_t tmp = ret.add_state();
	ret.set_initial(tmp);
	ret.add_series_transition(tmp, m[*p], t.get_initial(*p).get(empty));
      }
      else
	ret.set_initial(m[*p], t.get_initial(*p).get(empty));
    }

    for_all_final_states(p, t)
    {
      if (t.get_final(*p) != id_series)
      {
	hstate_t tmp = ret.add_state();
	ret.set_final(tmp);
	ret.add_series_transition(m[*p], tmp, t.get_final(*p).get(empty));
      }
      else
	ret.set_final(m[*p], t.get_final(*p).get(empty));
    }

    for_all_transitions(e, t)
    {
      ret.add_series_transition(m[t.src_of(*e)],
				m[t.dst_of(*e)],
				t.output_of(*e));
    }
  }


  template <typename S, typename T, typename Auto_t>
  static
  typename output_projection_helper<S, T>::ret
  do_rw_image(const Element<S, T>& t,
	      Auto_t& ret,
	      std::map<hstate_t, hstate_t>& m_)
  {
    TIMER_SCOPED("image (transducer to automaton)");
    typedef Element<S, T>  Trans_t;
    AUTOMATON_TYPES(Trans_t);

    monoid_elt_t empty = t.series().monoid().empty_;
    std::map<hstate_t, hstate_t> m;

    for_all_states(p, t)
    {
      m[*p] = ret.add_state();
      m_[m[*p]] = *p;
    }

    for_all_initial_states(p, t)
      ret.set_initial(m[*p], t.get_initial(*p).get(empty));

    for_all_final_states(p, t)
      ret.set_final(m[*p], t.get_final(*p).get(empty));

    for_all_transitions(e, t)
      ret.add_series_transition(m[t.src_of(*e)], m[t.dst_of(*e)],
				t.output_of(*e));

    return ret;
  }



  /*------------.
  | DISPATCHERS |
  `------------*/

  // Dispatchers for RW transducers
  template <typename S, typename S2,
	    typename T, typename T2,
	    typename ST, typename M1>
  static void
  image_dispatch(const Element<S,T>& src,
		 const TransducerBase<ST>&,
		 const algebra::FreeMonoidBase<M1>&,
		 Element<S2, T2>& dst)
  {
    do_rw_image(src, dst);
  }

  template <typename S, typename S2,
	    typename T, typename T2,
	    typename ST, typename M1>
  static void
  image_dispatch(const Element<S,T>& src,
		 const TransducerBase<ST>&,
		 const algebra::FreeMonoidBase<M1>&,
		 Element<S2, T2>& dst,
		 std::map<hstate_t, hstate_t>& m)
  {
    do_rw_image(src, dst, m);
  }

  // Dispatch and build returned object for RW transducers
  template <typename S, typename T, typename ST>
  static void
  image_dispatch2(const Element<S,T>& src,
		  const TransducerBase<ST>&,
		  std::map<hstate_t, hstate_t>& m)
  {
    typedef Element<S, T>  Trans_t;
    AUTOMATON_TYPES(Trans_t);

    typedef typename output_projection_helper<S, T>::ret    Auto_t;
    typedef typename Auto_t::set_t			    Auto_set_t;
    typedef typename Auto_set_t::series_set_t		 Auto_series_set_t;

    Auto_set_t	 auto_set
      (Auto_series_set_t(src.structure().series().semiring()));
    Auto_t	 dst(auto_set);

    if (m)
      image_dispatch(src, src.structure(),
		     src.structure().series().monoid(), dst, m);
    else
      image_dispatch(src, src.structure(),
		     src.structure().series().monoid(), dst);
    return dst;
  }


  // Dispatcher for transducers
  //  image_dispatch(const Element<S,T>& src, Element<S2, T2>& dst)
  template <typename S, typename S2,
	    typename T, typename T2,
	    typename ST, typename M1>
  static void
  image_dispatch(const Element<S,T>& src,
		 const AutomataBase<ST>&,
		 const algebra::FreeMonoidProductBase<M1>&,
		 Element<S2, T2>& dst)
  {
    do_fmp_image(src, dst);
  }



  /*--------------.
  | IMAGE FACADES |
  `--------------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  image(const Element<S,T>& src, Element<S2, T2>& dst)
  {
    image_dispatch(src, src.structure(),
		   src.structure().series().monoid(),
		   dst);
  }

  template <typename S, typename T>
  typename output_projection_helper<S, T>::ret
  image(const Element<S, T>& src)
  {
    return image_dispatch2(src, src.structure(), 0);
  }

  template <typename S, typename T>
  typename output_projection_helper<S, T>::ret
  image(const Element<S, T>& src,
	std::map<hstate_t, hstate_t>& m)
  {
    return image_dispatch2(src, src.structure(), m);
  }

} // End of namespace vcsn.

#endif	    /* !VCSN_ALGORITHMS_IMAGE_HXX */