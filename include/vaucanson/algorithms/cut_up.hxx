// cut_up.hxx: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
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


  /*--------------------------------.
  | Check if an automaton is cut up |
  `--------------------------------*/

  template <class S, class T>
  bool is_cut_up(const Element<S, T>& a)
  {
    typedef Element<S, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    for_each_edge(e, a)
      if (! a.series_of(*e).is_finite_app() ||
	  a.series_of(*e).supp().size() > 1)
	return false;

    return true;
  }


  /*----------------------------------------------.
  | Specialization for label with rational series |
  `----------------------------------------------*/

  template <class S, class T, class TT, class Auto, class Ret>
  void do_cut_up(const AutomataBase<S>&,
		 const rat::exp<T, TT>&,
		 const Auto& a,
		 Ret& res)
  {
    AUTOMATON_TYPES(Ret);
    typedef typename generalized_traits<Ret>::automaton_t gen_automaton_t;

    auto_copy(res, a);

    std::map<hstate_t, hstate_t> statemap;

    edges_t		edges = res.value().edges();

    for_each_(edges_t, e, edges)
      {
	if (! res.series_of(*e).is_finite_app() ||
	    res.series_of(*e).supp().size() > 1)
	  {
	    gen_automaton_t tmp(res.structure());
	    standard_of(tmp, res.series_of(*e).value());

	    for_each_state(s, tmp)
	      statemap[*s] = res.add_state();

	    for_each_initial_state(i, tmp)
	      res.add_series_edge(res.origin_of(*e),
				  statemap[*i],
				  tmp.get_initial(*i));

	    for_each_edge(ed, tmp)
	      res.add_edge(statemap[tmp.origin_of(*ed)],
			   statemap[tmp.aim_of(*ed)],
			   tmp.label_of(*ed));

	    for_each_final_state(f, tmp)
	      res.add_series_edge(statemap[*f], res.aim_of(*e),
				  tmp.get_final(*f));

	    res.del_edge(*e);
	  }
      }
  }


  /*------------------------------------------------.
  | Specialization for label with polynomial series |
  `------------------------------------------------*/

  template <class S, class T, class TT, class Auto, class Ret>
  void do_cut_up(const S&,
		 const algebra::polynom<T, TT>&,
		 const Auto& a,
		 Ret& res)
  {
    int				size;
    typedef typename Ret::series_set_elt_t series_set_elt_t;
    typedef typename series_set_elt_t::support_t support_t;
    typedef typename Ret::value_t::edges_t edges_t;

    auto_copy(res, a);

    edges_t		edges = res.value().edges();

    for_each_(edges_t, e, edges)
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
		res.add_series_edge(res.origin_of(*e),
				    res.aim_of(*e),
				    series);
	      }

	    res.del_edge(*e);
	  }
      }
  }


  /*---------.
  | Wrappers |
  `---------*/

  template <class S, class T>
  Element<S, T>
  cut_up(const Element<S, T>& a)
  {
    typedef typename Element<S, T>::series_set_elt_t::value_t series_impl_t;

    Element<S, T> res(a.structure());
    do_cut_up(a.structure(),SELECT(series_impl_t), a, res);

    return res;
  }


  template <class S, class T>
  void
  cut_up(const Element<S, T>& a, Element<S, T>& res)
  {
    typedef typename Element<S, T>::series_set_elt_t::value_t series_impl_t;

    do_cut_up(a.structure(), SELECT(series_impl_t), a, res);
  }


  template <class S, class T>
  void
  cut_up_here(Element<S, T>& a)
  {
    typedef typename Element<S, T>::series_set_elt_t::value_t series_impl_t;

    Element<S, T> res(a.structure());
    do_cut_up(a.structure(),SELECT(series_impl_t), a, res);

    a = res;
  }

  
} // ! vcsn


#endif // ! VCSN_ALGORITHMS_CUT_UP_HXX
