// aut_projection.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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

#ifndef VCSN_ALGORITHMS_AUT_PROJECTION_HXX
# define VCSN_ALGORITHMS_AUT_PROJECTION_HXX

# include <vaucanson/algorithms/aut_projection.hh>

namespace vcsn
{
  template <typename S, typename T>
  void
  do_first_projection(const Element<S, T>& src,
		      typename projection_traits<S, T>::
		      first_projection_t& dst)
  {
    BENCH_TASK_SCOPED("first_projection");

    // Type helpers.
    typedef Element<S, T> automaton_t;
    typedef projection_traits<S, T> projection_traits_t;
    typedef typename projection_traits_t::first_projection_t res_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_TYPES_(res_t, res_);

    // Helper map.
    std::map<hstate_t, res_hstate_t> m;

    // Create destination states.
    for_all_const_states(p, src)
      m[*p] = dst.add_state();

    // Setup initial weights.
    for_all_const_initial_states(i, src)
    {
      dst.set_initial(m[*i],
		      projection_traits_t::
		      series_first_projection(dst.series(),
					      src.get_initial(*i)));
    }

    // Setup normal transitions.
    for_all_const_transitions(e, src)
    {
      dst.add_series_transition(m[src.src_of(*e)],
				m[src.dst_of(*e)],
				projection_traits_t::
				series_first_projection(dst.series(),
							src.series_of(*e)));
    }

    // Setup final weights.
    for_all_const_final_states(f, src)
    {
      dst.set_final(m[*f],
		    projection_traits_t::
		    series_first_projection(dst.series(),
					    src.get_final(*f)));
    }
  }

  template <typename S, typename T>
  void
  do_second_projection(const Element<S, T>& src,
		       typename projection_traits<S, T>::
		       second_projection_t& dst)
  {
    BENCH_TASK_SCOPED("second_projection");

    // Type helpers.
    typedef Element<S, T> automaton_t;
    typedef projection_traits<S, T> projection_traits_t;
    typedef typename projection_traits_t::second_projection_t res_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_TYPES_(res_t, res_);

    // Helper map.
    std::map<hstate_t, res_hstate_t> m;

    // Create destination states.
    for_all_const_states(p, src)
      m[*p] = dst.add_state();

    // Setup initial weights.
    for_all_const_initial_states(i, src)
    {
      dst.set_initial(m[*i],
		      projection_traits_t::
		      series_second_projection(dst.series(),
					       src.get_initial(*i)));
    }

    // Setup normal transitions.
    for_all_const_transitions(e, src)
    {
      dst.add_series_transition(m[src.src_of(*e)],
				m[src.dst_of(*e)],
				projection_traits_t::
				series_second_projection(dst.series(),
							 src.series_of(*e)));
    }

    // Setup final weights.
    for_all_const_final_states(f, src)
    {
      dst.set_final(m[*f],
		    projection_traits_t::
		    series_second_projection(dst.series(),
					     src.get_final(*f)));
    }
  }

  /*------------------.
  | Function Facades. |
  `------------------*/

  //
  // First projection
  //

  template <typename S, typename T>
  void
  first_projection(const Element<S, T>& src,
		   typename projection_traits<S, T>::first_projection_t& dst)
  {
    do_first_projection(src, dst);
  }

  template <typename S, typename T>
  typename projection_traits<S, T>::first_projection_t
  first_projection(const Element<S, T>& src)
  {
    typename projection_traits<S, T>::first_projection_t
	dst = projection_traits<S, T>::first_projection(src);

    do_first_projection(src, dst);

    return dst;
  }

  //
  // Second projection
  //

  template <typename S, typename T>
  void
  second_projection(const Element<S, T>& src,
		    typename projection_traits<S, T>::
		    second_projection_t& dst)
  {
    do_second_projection(src, dst);
  }

  template <typename S, typename T>
  typename projection_traits<S, T>::second_projection_t
  second_projection(const Element<S, T>& src)
  {
    typename projection_traits<S, T>::second_projection_t
	dst = projection_traits<S, T>::second_projection(src);

    do_second_projection(src, dst);

    return dst;
  }

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_AUT_PROJECTION_HXX
