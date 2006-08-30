// projection.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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

# include <vaucanson/algorithms/projection.hh>

# include <map>

namespace vcsn {

  template<typename ST, typename SA,
	   typename Trans_t, typename Auto_t>
  void
  do_output_projection(const TransducerBase<ST>&,
		       const AutomataBase<SA>&,
		       const Trans_t& t,
		       Auto_t& ret)
  {
    TIMER_SCOPED("output_projection (transducer/automaton)");
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

  template <class ST, class TT,
	    class SA, class TA>
  void
  output_projection(const Element<ST, TT>& t,
		    Element<SA, TA>& a)
  {
    return do_output_projection(t.structure(), a.structure(), t, a);
  }

  ////////////////////////////////////////////////////////////

  template <typename S, typename T>
  typename output_projection_helper<S, T>::ret
  do_output_projection(const TransducerBase<S>&,
		       const Element<S, T>& t,
		       std::map<hstate_t, hstate_t>& m_)
  {
    TIMER_SCOPED("output_projection (transducer/element)");
    typedef Element<S, T>  Trans_t;
    AUTOMATON_TYPES(Trans_t);

    typedef typename output_projection_helper<S, T>::ret    Auto_t;
    typedef typename Auto_t::set_t			    Auto_set_t;
    typedef typename Auto_set_t::series_set_t		 Auto_series_set_t;

    Auto_set_t	 auto_set(Auto_series_set_t(t.structure().series().semiring()));
    Auto_t	 ret(auto_set);

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

  template <typename S, typename T>
  typename output_projection_helper<S,T>::ret
  output_projection(const Element<S, T>& t,
		    std::map<hstate_t, hstate_t>& m)
  {
    return do_output_projection(t.structure(), t, m);
  }

  template <typename S, typename T>
  typename output_projection_helper<S,T>::ret
  output_projection(const Element<S, T>& t)
  {
    std::map<hstate_t, hstate_t> m;
    return do_output_projection(t.structure(), t, m);
  }

  ///////////////////////////////////////////////////////////

  template <typename S, typename T>
  typename input_projection_helper<S, T>::ret
  do_input_projection(const TransducerBase<S>&,
		      const Element<S, T>& t)
  {
    TIMER_SCOPED("input_projection");
    typedef Element<S, T> Trans_t;
    AUTOMATON_TYPES(Trans_t);

    typedef typename input_projection_helper<S, T>::ret	Auto_t;
    typedef typename Auto_t::set_t			Auto_set_t;
    typedef typename Auto_set_t::series_set_t		Auto_series_set_t;

    Auto_set_t	 auto_set(Auto_series_set_t(t.structure().series().semiring()));
    Auto_t	 ret(auto_set);

    monoid_elt_t empty = t.series().monoid().empty_;
    std::map<hstate_t, hstate_t> m;

    for_all_states(p, t)
    {
      m[*p] = ret.add_state();
    }

    for_all_initial_states(p, t)
      ret.set_initial(m[*p]);

    for_all_final_states(p, t)
      ret.set_final(m[*p]);

    for_all_transitions(e, t)
    {
      ret.add_series_transition(m[t.src_of(*e)],
				m[t.dst_of(*e)],
				t.input_of(*e));
    }

    return ret;
  }

  template <typename S, typename T>
  typename input_projection_helper<S, T>::ret
  input_projection(const Element<S, T>& t)
  {
    return do_input_projection(t.structure(), t);
  }

}

#endif // ! VCSN_ALGORITHMS_PROJECTION_HXX
