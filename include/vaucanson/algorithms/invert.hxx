// invert.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008 The Vaucanson Group.
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

#ifndef	VCSN_ALGORITHMS_INVERT_HXX
# define VCSN_ALGORITHMS_INVERT_HXX

# include <map>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/series/series.hh>

# include <vaucanson/misc/usual_macros.hh>

# include <vaucanson/algorithms/standard_of.hh>
# include <vaucanson/algorithms/realtime.hh>

namespace vcsn
{

  /*------------------------------------.
  | Specialization for RW transducers.  |
  `------------------------------------*/

  template<typename S, typename T>
  Element<S, T>&
  do_invert_rw(Element<S, T>& t,
	       Element<S, T>& u)
  {
    typedef Element<S, T> Trans_t;
    typedef typename output_projection_helper<S, T>::ret Auto_t;
    AUTOMATON_TYPES(Trans_t);

    normalize_here(t);

    std::map<hstate_t, hstate_t> map_t_u;
    for_all_const_states (p, t)
      map_t_u[*p] = u.add_state ();

    initial_iterator i_it;
    for (initial_iterator next = t.initial().begin(), next_end = t.initial().end();
	 next != next_end;)
    {
      //We need to store the next iterator before using the current one
      //to avoid an invalid iterator after having called set_final.
      //Indeed, set_final can delete the iterator if its second parameter
      //is the zero of the serie.
      i_it = next;
      next++;
      u.set_initial (map_t_u[*i_it]);
    }

    final_iterator f_it;
    for (final_iterator next = t.final().begin(), next_end = t.final().end();
	 next != next_end;)
    {
      //We need to store the next iterator before using the current one
      //to avoid an invalid iterator after having called set_final.
      //Indeed, set_final can delete the iterator if its second parameter
      //is the zero of the serie.
      f_it = next;
      next++;
      u.set_final (map_t_u[*f_it]);
    }

    for_all_const_transitions (e, t)
    {
      semiring_elt_t exp = t.output_of(*e);

      typename Auto_t::set_t auto_structure
	(typename Auto_t::set_t::series_set_t
	 (t.structure().series().semiring()));
      Auto_t auto_tmp(auto_structure);

      // As the output of each transition is not supposed to be
      // realtime we build the standard automaton corresponding to
      // this expression
      standard_of(auto_tmp, exp.value());

      std::map<hstate_t, hstate_t> map_auto_u;

      for_all_const_states (p, auto_tmp)
	if (auto_tmp.is_initial (*p))
	  map_auto_u[*p] = map_t_u[t.src_of(*e)];
	else
	  map_auto_u[*p] = u.add_state();

      typename semiring_elt_t::semiring_elt_t
	o_sm_zero (u.structure().series().semiring().semiring());
      monoid_elt_t monoid_identity = u.series().monoid().VCSN_EMPTY_;

      monoid_elt_t a (u.structure().series().monoid());
      semiring_elt_t sm (u.structure().series().semiring());
      series_set_elt_t s (u.structure().series());

      for (typename Auto_t::transition_iterator f =
	     auto_tmp.transitions().begin();
	   f != auto_tmp.transitions().end();
	   ++f)
      {
	a = auto_tmp.word_of (*f);

	s.assoc (a, algebra::identity_as<semiring_elt_value_t>
		 ::of(u.series().semiring()));

	u.add_series_transition (map_auto_u[auto_tmp.src_of(*f)],
				 map_auto_u[auto_tmp.dst_of(*f)],
				 s);
      }

      a = t.input_of (*e);
      for (typename Auto_t::final_iterator q = auto_tmp.final().begin();
	   q != auto_tmp.final().end();
	   ++q)
      {
	typedef typename semiring_elt_t::semiring_elt_t output_sm_t;
	typedef typename output_sm_t::value_t output_sm_value_t;

	sm.assoc (a, algebra::identity_as<output_sm_value_t>
		  ::of(u.series().semiring().semiring()));
	s.assoc(monoid_identity, sm);
	u.add_series_transition(map_auto_u[*q],
				map_t_u[t.dst_of(*e)],
				s);
      }
    }

    realtime_here(u);

    return u;
  }


  /*-------------------------------------.
  | Specialization for FMP transducers.  |
  `-------------------------------------*/


  // Invert `label' and store the result in `res'.
  template<typename S, typename T,
	   typename SS, typename TT>
  static void invert_label(const Element<S, T>& label,
			   Element<SS, TT>& res)
  {
    typedef Element<S, T> series_set_elt_t;
    typedef typename series_set_elt_t::monoid_elt_t::value_t
      res_monoid_elt_value_t;

    // Invert each pair
    for_all_const_(series_set_elt_t::support_t, w, label.supp())
      // (u,v) -> (v,u)
      res.assoc(res_monoid_elt_value_t((*w).second, (*w).first),
		label.get(*w));
  }


  template<typename S, typename T,
	   typename SS, typename TT>
  Element<SS, TT>&
  do_invert_tdc(const Element<S, T>& t,
		Element<SS, TT>& u)
  {
    typedef Element<S, T> Trans_t;
    typedef Element<SS, TT> res_t;
    AUTOMATON_TYPES(Trans_t);
    AUTOMATON_TYPES_(res_t, res_);

    std::map<hstate_t, hstate_t> map_t_u;
    for_all_const_states (p, t)
      map_t_u[*p] = u.add_state ();

    // Proceed initial and final states
    for_all_const_initial_states (p, t)
      {
	res_series_set_elt_t s (u.structure().series());
	invert_label(t.get_initial(*p), s);
	u.set_initial (map_t_u[*p], s);
      }

    for_all_const_final_states (p, t)
      {
	res_series_set_elt_t s (u.structure().series());
	invert_label(t.get_final(*p), s);
	u.set_final (map_t_u[*p], s);
      }


    for_all_const_transitions (e, t)
      {
	res_series_set_elt_t s (u.structure().series());
	res_monoid_elt_t a (u.structure().series().monoid());

	// Get the label of the current transition
	series_set_elt_t label(t.structure().series());
	label = t.series_of(*e);

	invert_label(label, s);

	u.add_series_transition(map_t_u[t.src_of(*e)],
				map_t_u[t.dst_of(*e)],
				s);
      }

    return u;
  }



  /*------------------------------.
  | Dispatch for FMP tranducers.  |
  `------------------------------*/

  template<typename S, typename T,
	   typename M1, typename M2>
  Element<S, T>&
  do_invert_fmp(const algebra::FreeMonoidProduct<M1, M2>&,
		const Element<S, T>& t)
  {
    // Declaration of the inverted transducer
    typedef Element<S, T> trans_t;
    AUTOMATON_TYPES(trans_t);

    typedef algebra::FreeMonoidProduct<
      typename trans_t::series_set_t::monoid_t::second_monoid_t,
      typename trans_t::series_set_t::monoid_t::first_monoid_t>
      res_monoid_t;

    typedef algebra::Series<typename trans_t::series_set_t::semiring_t,
      res_monoid_t>
      res_series_set_t;

    res_monoid_t monoid(t.structure().series().monoid().second_monoid(),
			t.structure().series().monoid().first_monoid());


    res_series_set_t series(t.structure().series().semiring(), monoid);

    Automata<series_set_t, kind_t> trans_set(series);

    typedef Element< Automata<series_set_t, kind_t>, T> res_trans_t;
    res_trans_t* res = new res_trans_t(trans_set);

    return do_invert_tdc(t, *res);
  }


  template<typename S, typename T,
	   typename SS, typename TT,
	   typename M1, typename M2>
  Element<SS, TT>&
  do_invert_fmp(const algebra::FreeMonoidProduct<M1, M2>&,
		const Element<S, T>& t,
		Element<SS, TT>& res)
  {
    return do_invert_tdc(t, res);
  }


  template<typename S, typename T>
  Element<S, T>&
  do_invert(const AutomataBase<S>&,
	    const Element<S, T>& t)
  {
    return do_invert_fmp(t.structure().series().monoid(), t);
  }

  template<typename S, typename T>
  Element<S, T>&
  do_invert(const AutomataBase<S>&,
	    const Element<S, T>& t,
	    Element<S, T>& res)
  {
    return do_invert_fmp(t.structure().series().monoid(), t, res);

  }

  /*-----------------------------.
  | Dispatch for RW tranducers.  |
  `-----------------------------*/

  template<typename S, typename T>
  Element<S, T>&
  do_invert(const TransducerBase<S>&,
	    const Element<S, T>& t)
  {
    // Building the structure of the inverted transducer
    typedef Element<S, T> Trans_t;
    AUTOMATON_TYPES(Trans_t);

    monoid_t o_mon_structure
      (t.structure().series().monoid());
    typename semiring_t::semiring_t sm_sm_structure
      (t.structure().series().semiring().semiring());
    typename semiring_t::monoid_t i_mon_structure
      (t.structure().series().semiring().monoid());

    semiring_t sm_structure (sm_sm_structure, o_mon_structure);
    series_set_t ss_structure(sm_structure, i_mon_structure);

    automata_set_t auto_structure(ss_structure);

    Trans_t* res = new Trans_t(auto_structure);
    Trans_t src(t);

    do_invert_rw(src, *res);
    return *res;
  }


  template<typename S, typename T>
  Element<S, T>&
  do_invert(const TransducerBase<S>&,
	    const Element<S, T>& t,
	    Element<S, T>& res)
  {
    Element<S, T> src(t);
    return do_invert_rw(src, res);
  }




  /*----------.
  | Facades.  |
  `----------*/

  template<typename S, typename T>
  Element<S, T>&
  invert(const Element<S, T>& t)
  {
    TIMER_SCOPED("invert");
    return do_invert(t.structure(), t);
  }

  template<typename S, typename T>
  void
  invert(const Element<S, T>& t,
	 Element<S, T>& res)
  {
    TIMER_SCOPED("invert");
    do_invert(t.structure(), t, res);
  }
}

#endif // !VCSN_ALGORITHMS_INVERT_HXX
