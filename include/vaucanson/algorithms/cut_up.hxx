// cut_up.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_CUT_UP_HXX
# define VCSN_ALGORITHMS_CUT_UP_HXX

/**
   * @file cut_up.hxx
   *
   * Cut-up algorithm.
   *
   * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
   */


namespace vcsn {


  /*----------------------------------.
  | Check if an automaton is cut up.  |
  `----------------------------------*/

  template <typename A, typename AI>
  bool is_cut_up(const Element<A, AI>& a)
  {
    TIMER_SCOPED("is_cut_up");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    for_all_const_transitions(e, a)
      if (! a.series_of(*e).is_finite_app() ||
	  a.series_of(*e).supp().size() > 1)
	return false;

    return true;
  }


  /*------------------------------------------------.
  | Specialization for label with rational series.  |
  `------------------------------------------------*/

  template <typename S, typename T, typename TT, typename Auto, typename Ret>
  void do_cut_up(const AutomataBase<S>&,
		 const rat::exp<T, TT>&,
		 const Auto& a,
		 Ret& res)
  {
    AUTOMATON_TYPES_(Ret, ret_);
    typedef typename generalized_traits<Ret>::automaton_t gen_automaton_t;
    AUTOMATON_TYPES(gen_automaton_t);

    auto_copy(res, a);

    std::map<hstate_t, ret_hstate_t> statemap;

    ret_transitions_t		transitions = res.transitions();

    for_all_(ret_transitions_t, e, transitions)
    {
      if (! res.series_of(*e).is_finite_app() ||
	  res.series_of(*e).supp().size() > 1)
      {
	gen_automaton_t tmp(res.structure());
	standard_of(tmp, res.series_of(*e).value());

	for_all_states(s, tmp)
	  statemap[*s] = res.add_state();

	for_all_initial_states(i, tmp)
	  res.add_series_transition(res.src_of(*e),
				    statemap[*i],
				    tmp.get_initial(*i));

	for_all_transitions(ed, tmp)
	  res.add_transition(statemap[tmp.src_of(*ed)],
			     statemap[tmp.dst_of(*ed)],
			     tmp.label_of(*ed));

	for_all_final_states(f, tmp)
	  res.add_series_transition(statemap[*f], res.dst_of(*e),
				    tmp.get_final(*f));

	res.del_transition(*e);
      }
    }
  }


  /*--------------------------------------------------.
  | Specialization for label with polynomial series.  |
  `--------------------------------------------------*/

  template <typename S, typename T, typename TT, typename Auto, typename Ret>
  void do_cut_up(const S&,
		 const algebra::polynom<T, TT>&,
		 const Auto& a,
		 Ret& res)
  {
    AUTOMATON_TYPES(Ret);
    typedef typename Ret::series_set_elt_t::support_t support_t;
    int	size;

    auto_copy(res, a);

    transitions_t transitions = res.transitions();

    for_all_(transitions_t, e, transitions)
    {
      series_set_elt_t label(res.structure().series());
      label = res.series_of(*e);

      if ((size = label.supp().size()) > 1)
      {
	typename support_t::const_iterator m = label.supp().begin();
	for (int i = 0; i < size; ++i, ++m)
	{
	  series_set_elt_t series(res.structure().series());
	  series.assoc(*m, label.get(*m));
	  res.add_series_transition(res.src_of(*e),
				    res.dst_of(*e),
				    series);
	}

	res.del_transition(*e);
      }
    }
  }


  /*---------.
  | Wrappers |
  `---------*/

  template <typename A, typename AI>
  void
  cut_up(const Element<A, AI>& a, Element<A, AI>& res)
  {
    TIMER_SCOPED("cut_up");
    typedef typename Element<A, AI>::series_set_elt_t::value_t series_impl_t;
    do_cut_up(a.structure(), SELECT(series_impl_t), a, res);
  }


  template <typename A, typename AI>
  Element<A, AI>
  cut_up(const Element<A, AI>& a)
  {
    Element<A, AI> res(a.structure());
    cut_up(a, res);
    return res;
  }


  template <typename A, typename AI>
  void
  cut_up_here(Element<A, AI>& a)
  {
    a = cut_up(a);
  }


} // ! vcsn


#endif // ! VCSN_ALGORITHMS_CUT_UP_HXX
