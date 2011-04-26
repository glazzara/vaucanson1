// standard.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
// 2010, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_STANDARD_HXX
# define VCSN_ALGORITHMS_STANDARD_HXX

# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/algorithms/one_eps_closure.hh>
# include <vaucanson/algorithms/internal/has_neighbour.hh>
# include <vaucanson/algorithms/internal/build_pattern.hh>

# include <vaucanson/algorithms/accessible.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <set>

namespace vcsn {

  /*------------.
  | basic_sptr  |
  `------------*/

  template<typename HSTATE, typename WEIGHT>
  struct basic_sptr
  {
  private:
    const HSTATE& src_;
    const HSTATE& dst_;
    const WEIGHT& weight_;

  public:
    basic_sptr(const HSTATE& src, const HSTATE& dst, const WEIGHT& weight) :
      src_(src), dst_(dst), weight_(weight) {}

    HSTATE src() const {
      return src_;
    }

    HSTATE dst() const {
      return dst_;
    }

    WEIGHT weight() const {
      return weight_;
    }
  };


  /*--------.
  |  union  |
  `--------*/

  template <typename A, typename AI1, typename AI2>
  void
  do_union_here(const AutomataBase<A>&,
		Element<A, AI1>& lhs,
		const Element<A, AI2>& rhs)
  {
    typedef Element<A, AI1> lhs_t;
    AUTOMATON_TYPES(lhs_t);
    typedef Element<A, AI2> rhs_t;
    typedef typename rhs_t::hstate_t r_hstate_t;

    std::map<r_hstate_t, hstate_t> states_map;

    //  union of states
    for_all_states(it, rhs)
      {
	hstate_t    new_state = lhs.add_state();
	states_map[*it] = new_state;

	lhs.set_initial(new_state, rhs.get_initial(*it));
	lhs.set_final(new_state, rhs.get_final(*it));
      }

      //  union of transitions.
    for_all_transitions(it, rhs)
      {
	lhs.add_transition(states_map[rhs.src_of(*it)],
			   states_map[rhs.dst_of(*it)],
			   rhs.label_of(*it));
      }
  }

  //  wrappers for union
  template<typename A, typename AI1, typename AI2>
  void
  union_here(Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    do_union_here(lhs.structure(), lhs, rhs);
  }


  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  union_(const Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    Element<A, AI1> ret(lhs);
    do_union_here(ret.structure(), ret, rhs);
    return ret;
  }

  //   same as union, but keeps track of two states in the union
  //   (will be used for initial states)
  template <typename A, typename AI1, typename AI2>
  void
  marked_union_here(const AutomataBase<A>&,
		    Element<A, AI1>& lhs,
		    const Element<A, AI2>& rhs,
		    const typename Element<A, AI1>::hstate_t& lhs_stt,
		    typename Element<A, AI1>::hstate_t& mrk_stt,
		    const typename Element<A, AI2>::hstate_t& rhs_stt)
  {
    typedef Element<A, AI1> lhs_t;
    AUTOMATON_TYPES(lhs_t);
    typedef Element<A, AI2> rhs_t;
    typedef typename rhs_t::hstate_t   r_hstate_t;
    std::map<r_hstate_t, hstate_t>     states_map;

    //   copy of rhs states into lhs
    for_all_states(it, rhs)
      {
	hstate_t    new_state = lhs.add_state();
	states_map[*it] = new_state;

	lhs.set_initial(new_state, rhs.get_initial(*it));
	lhs.set_final(new_state, rhs.get_final(*it));
      }
    mrk_stt = states_map[rhs_stt];  //  mark copy of rhs_stt

    // copy of rhs transitions into lhs
    for_all_transitions(it, rhs)
      {
	lhs.add_transition(states_map[rhs.src_of(*it)],
			   states_map[rhs.dst_of(*it)],
			   rhs.label_of(*it));
      }
  }

  /*--------------.
  | is_standard.  |
  `--------------*/
  template<typename A, typename AI>
  bool
  do_is_standard(const AutomataBase<A>&, const Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("is_standard");
    typedef Element<A, AI> automaton_t;
    typedef typename automaton_t::series_set_elt_value_t series_set_elt_value_t;

    // Check there is only one initial state.
    if (a.initial().size() != 1)
      return false;

    // Check the multiplicity of the initial state.
    typename automaton_t::hstate_t s = *a.initial().begin();
    if (a.get_initial(s)
	!= a.series().identity(SELECT(series_set_elt_value_t)))
      return false;

    // Check that there is no input transition on the initial state.
    return !has_predecessors(a, s);
  }

  template<typename A, typename AI>
  bool
  is_standard(const Element<A, AI>& a)
  {
    return do_is_standard(a.structure(), a);
  }

  /*------------.
  | standardize |
  `------------*/

  template<typename S, typename AI>
  void
  do_standardize(const AutomataBase<S>&, Element<S, AI>& a)
  {
    BENCH_TASK_SCOPED("standardize");
    typedef Element<S, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef basic_sptr<hstate_t, series_set_elt_t> sptr_t;
    typedef typename std::list<hstate_t> stt_lst_t;

    stt_lst_t  stt_list;
    series_set_elt_t fin_wgt =
      algebra::zero_as<series_set_elt_value_t>::of(a.series());

    if (is_standard(a)) return;

    hstate_t i = a.add_state();  // add a new state that will be the
				 // initial state
    //  put all initial states of a in a list
    for_all_initial_states(it, a)   stt_list.push_back(*it);

    for_all(typename stt_lst_t, it, stt_list)
      {
	hstate_t ini_stt = *it;
	series_set_elt_t ini_wgt = a.get_initial(ini_stt);

	//  emulates closure with respect of a spt transition between i and ini_stt
	sptr_t t(i, ini_stt, ini_wgt);
	one_eps_closure(a, t, misc::backward);
	//  computes the final weight of the new initial state
	a.unset_initial(ini_stt);
	//  delete state if there is zero incoming transitions
	if (!has_predecessors(a, ini_stt))
	  a.del_state(ini_stt);
      }

    a.set_initial(i);

    return;
  }

  // standardize is always 'here'
  template<typename A, typename AI>
  void
  standardize(Element<A, AI>& a)
  {
    do_standardize(a.structure(), a);
  }

  /*-----------------.
  | sum_of_standard  |
  `-----------------*/

  template <typename A, typename AI>
  void
  sum_of_standard_inside(const AutomataBase<A>&,   Element<A, AI>& aut,
                         const typename Element<A, AI>::hstate_t& aut_stt,
                               typename Element<A, AI>::hstate_t& mrk_stt)
  {
    typedef Element<A, AI> automaton_t;    AUTOMATON_TYPES(automaton_t);
    typedef series_set_elt_t                    weight_t;
    typedef basic_sptr<hstate_t, weight_t>   sptr_t;

    weight_t unit = aut.series().identity(SELECT(series_set_elt_value_t));

    sptr_t t(aut_stt, mrk_stt, unit);
    one_eps_closure(aut, t, misc::backward);
    aut.del_state(mrk_stt);
  }


  template <typename A, typename AI1, typename AI2>
  void
  do_sum_of_standard_here(const AutomataBase<A>&,
                                Element<A, AI1>& lhs,
                          const Element<A, AI2>& rhs)
  {
    BENCH_TASK_SCOPED("sum_of_standard");

    typedef Element<A, AI1> lhs_t;
    AUTOMATON_TYPES(lhs_t);
    typedef Element<A, AI2> rhs_t;
    typedef typename rhs_t::hstate_t     r_hstate_t;

    hstate_t mrk_stt;

    // Mark the initial states
    hstate_t    lhs_stt = *lhs.initial().begin();
    r_hstate_t  rhs_stt = *rhs.initial().begin();

    marked_union_here(lhs.structure(), lhs, rhs, lhs_stt, mrk_stt, rhs_stt);

    sum_of_standard_inside(lhs.structure(), lhs, lhs_stt, mrk_stt);
  }


  template<typename A, typename AI1, typename AI2>
  void
  sum_of_standard_here(Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    precondition(is_standard(lhs));
    precondition(is_standard(rhs));
    do_sum_of_standard_here(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  sum_of_standard(const Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    precondition(is_standard(lhs));
    precondition(is_standard(rhs));
    Element<A, AI1> ret(lhs);
    sum_of_standard_here(ret, rhs);
    return ret;
  }

  /*---------------------.
  | concat_of_standard.  |
  `---------------------*/


  template <typename A, typename AI>
  void
  concat_of_standard_inside(const AutomataBase<A>&,   Element<A, AI>& aut,
			    typename std::list<typename Element<A, AI>::hstate_t>& stt_list,
			    typename Element<A, AI>::hstate_t& mrk_stt)
  {
    typedef Element<A, AI> aut_t;
    AUTOMATON_TYPES(aut_t);
    typedef series_set_elt_t                    weight_t;
    typedef typename std::list<hstate_t>        stt_lst_t;
    typedef basic_sptr<hstate_t, weight_t>      sptr_t;

    weight_t	mrk_wgt = aut.get_final(mrk_stt);

    for_all(typename stt_lst_t, it, stt_list)
      {
        hstate_t   fin_stt = *it;
        weight_t   fin_wgt = aut.get_final(fin_stt);
	aut.unset_final(fin_stt);
        sptr_t t(fin_stt, mrk_stt, fin_wgt);
        one_eps_closure(aut, t, misc::backward);
      }
    aut.del_state(mrk_stt);
  }


  template <typename A, typename AI1, typename AI2>
  void
  do_concat_of_standard_here(const AutomataBase<A>&,
			     Element<A, AI1>& lhs,
			     const Element<A, AI2>& rhs)
  {
    BENCH_TASK_SCOPED("concat_of_standard");

    typedef Element<A, AI1> lhs_t;
    AUTOMATON_TYPES(lhs_t);
    typedef std::list<hstate_t>              stt_lst_t;
    typedef Element<A, AI2> rhs_t;
    typedef typename rhs_t::hstate_t r_hstate_t;

    // Remember list of final states in lhs
    stt_lst_t    stt_list;
    for_all_final_states(it, lhs)  stt_list.push_back(*it);

    // Mark the initial states and perform marked union of states
    hstate_t    mrk_stt;
    hstate_t    lhs_stt = *lhs.initial().begin();
    r_hstate_t  rhs_stt = *rhs.initial().begin();
    marked_union_here(lhs.structure(), lhs, rhs, lhs_stt, mrk_stt, rhs_stt);

    concat_of_standard_inside(lhs.structure(), lhs, stt_list, mrk_stt);
  }


  template<typename A, typename AI1, typename AI2>
  void
  concat_of_standard_here(Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    precondition(is_standard(lhs));
    precondition(is_standard(rhs));
    do_concat_of_standard_here(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  concat_of_standard(const Element<A, AI1>& lhs,
		     const Element<A, AI2>& rhs)
  {
    precondition(is_standard(lhs));
    precondition(is_standard(rhs));
    Element<A, AI1> ret(lhs);
    do_concat_of_standard_here(ret.structure(), ret, rhs);
    return ret;
  }


   /*----------------------------------.
   | left_ext_mult_of_standard_inside  |
   `----------------------------------*/

  template <typename A, typename AI>
  void
  left_ext_mult_of_standard_inside(const AutomataBase<A>&,
				   Element<A, AI>& aut,
                                   const typename Element<A, AI>::hstate_t& ini_stt,
                                   const typename Element<A, AI>::series_set_elt_t& k)
  {
    typedef Element<A, AI> automaton_t;  AUTOMATON_TYPES(automaton_t);
    typedef series_set_elt_t                      weight_t;
    typedef typename std::list<htransition_t>   trn_lst_t;

    weight_t     zero(aut.series().zero_);
    trn_lst_t    ini_out_list;

    // Build the list of outgoing transitions from ini_stt
    for (delta_iterator it(aut.value(), ini_stt); !it.done(); it.next())
      ini_out_list.push_back(*it);

    // In case of multiplication by zero (this cannot happen if we are
    // working from a rational expression, but we check it nonetheless
    // in case one day this function is used with a used-supplied
    // weight).
    if (k == zero)
      {
        // erase all outgoing transitions from ini_stt
        for_all(typename trn_lst_t, it, ini_out_list)
           aut.del_transition(*it);
        // make ini_stt non final
        aut.unset_final(ini_stt);
      }
    // In all other cases
    else
      {
	for_all(typename trn_lst_t, it, ini_out_list)
	  { // multiply by k the series of all outgoing transitions from ini_stt
	    hstate_t dest = aut.dst_of(*it);
	    weight_t wgt = k * aut.series_of(*it);
	    aut.del_transition(*it);
	    aut.add_series_transition(ini_stt, dest, wgt);
	  }
	// multiply by k the final weight of ini_stt
	aut.set_final(ini_stt, k * aut.get_final(ini_stt));
      }
  }

  template <typename A, typename AI>
  void
  left_mult_of_standard_here(Element<A, AI>& aut,
			     const typename Element<A, AI>::series_set_elt_t& k)
  {
    precondition(is_standard(aut));
    left_ext_mult_of_standard_inside(aut.structure(), aut,
				     *aut.initial().begin(), k);
  }

  /*----------------------------------.
  | right_ext_mult_of_standard_inside  |
  `----------------------------------*/

  template <typename A, typename AI>
  void
  right_ext_mult_of_standard_inside
  (const AutomataBase<A>&, Element<A, AI>& aut,
   typename std::list<typename Element<A, AI>::hstate_t>& stt_list,
   const typename Element<A, AI>::series_set_elt_t& k)
  {
    typedef Element<A, AI> automaton_t;  AUTOMATON_TYPES(automaton_t);
    typedef typename std::list<hstate_t> stt_lst_t;

    // multiply by k (on the right) the final weight of of every state
    // in stt_list
    for_all(typename stt_lst_t, it, stt_list)
      aut.set_final(*it, aut.get_final(*it) * k);
  }

  template <typename A, typename AI>
  void
  right_mult_of_standard_here(Element<A, AI>& aut,
			      const typename Element<A, AI>::series_set_elt_t& k)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    precondition(is_standard(aut));
    std::list<hstate_t> finals;
    for_all_final_states(it, aut)  finals.push_back(*it);

    right_ext_mult_of_standard_inside(aut.structure(), aut,
				      finals, k);
  }

  /*------------------.
  | star_of_standard  |
  `------------------*/

  template <typename A, typename AI>
  void
  star_of_standard_inside(const AutomataBase<A>&, Element<A, AI>& aut,
                          const typename Element<A, AI>::hstate_t& ini_stt,
			  typename std::list<typename Element<A, AI>::hstate_t>& stt_list)
  {
    typedef Element<A, AI> automaton_t;   AUTOMATON_TYPES(automaton_t);
    typedef series_set_elt_t                    weight_t;
    typedef typename std::list<hstate_t>        stt_lst_t;
    typedef basic_sptr<hstate_t, weight_t>      sptr_t;
    weight_t unit = aut.series().identity(SELECT(series_set_elt_value_t));

    // compute the star of the final weight of ini_stt (starable has
    // already been called)
    weight_t	fin_wgt = aut.get_final(ini_stt);  fin_wgt.star();

    // multiply on the left by that coefficient
    aut.set_final(ini_stt, unit);
    left_ext_mult_of_standard_inside(aut.structure(), aut, ini_stt, fin_wgt);

    // emulates closure of spt transition from every
    // state in stt_list to ini_stt
    for_all(typename stt_lst_t, it, stt_list)
      {
        hstate_t   crn_stt = *it;
        weight_t   crn_fin_wgt = aut.get_final(crn_stt);
	aut.unset_final(crn_stt);

        sptr_t t(crn_stt, ini_stt, crn_fin_wgt);
        one_eps_closure(aut, t, misc::backward);
      }
  }


  template <typename A, typename AI>
  void
  do_star_of_standard_here(const AutomataBase<A>&, Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("star_of_standard");
    typedef Element<A, AI> automaton_t;   AUTOMATON_TYPES(automaton_t);
    typedef series_set_elt_t              weight_t;
    typedef std::list<hstate_t>           stt_lst_t;

    hstate_t    ini_stt = *a.initial().begin();
    weight_t	fin_wgt = a.get_final(ini_stt);

    precondition(fin_wgt.starable());

    stt_lst_t  stt_list;
    for_all_final_states(it, a)
      if (*it != ini_stt)
	stt_list.push_back(*it);

    star_of_standard_inside(a.structure(), a, ini_stt, stt_list);
  }

  template<typename A, typename AI>
  void
  star_of_standard_here(Element<A, AI>& a)
  {
    precondition(is_standard(a));
    do_star_of_standard_here(a.structure(), a);
  }

  template<typename A, typename AI>
  Element<A, AI>
  star_of_standard(const Element<A, AI>& a)
  {
    precondition(is_standard(a));
    Element<A, AI> ret(a);
    do_star_of_standard_here(ret.structure(), ret);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_STANDARD_HXX
