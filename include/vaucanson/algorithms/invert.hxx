// product.hh: this file is part of the Vaucanson project.
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

#ifndef   	INVERT_HXX_
# define   	INVERT_HXX_

# include <map>

# include <vaucanson/misc/usual_macros.hh>

# include <vaucanson/algorithms/standard_of.hh>
# include <vaucanson/algorithms/realtime.hh>

namespace vcsn {


  /*----------------------------------.
  | Specialization for RW transducers |
  `----------------------------------*/

  template<typename S, typename T>
  Element<S, T>& do_invert_rw(Element<S, T>& t,
			      Element<S, T>& u)
  {
    typedef Element<S, T> Trans_t;
    typedef typename output_projection_helper<S, T>::ret Auto_t;
    AUTOMATON_TYPES(Trans_t);

    normalize_here(t);

    std::map<hstate_t, hstate_t> map_t_u;
    for_all_states (p, t)
      map_t_u[*p] = u.add_state ();

    for_all_initial_states (p, t)
      u.set_initial (map_t_u[*p]);

    for_all_final_states (p, t)
      u.set_final (map_t_u[*p]);

    for_all_transitions (e, t)
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

	for_all_states (p, auto_tmp)
	  if (auto_tmp.is_initial (*p))
	    map_auto_u[*p] = map_t_u[t.src_of(*e)];
	  else
	    map_auto_u[*p] = u.add_state();

	typename semiring_elt_t::semiring_elt_t
	  o_sm_zero (u.structure().series().semiring().semiring());
	monoid_elt_t monoid_identity = u.series().monoid().empty_;

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



  /*---------------------------.
  | Dispatch for RW tranducers |
  `---------------------------*/

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
  |  Facades  |
  `----------*/

  template<typename S, typename T>
  Element<S, T>&
  invert(const Element<S, T>& t)
  {
    return do_invert(t.structure(), t);
  }

  template<typename S, typename T>
  void
  invert(const Element<S, T>& t,
	 Element<S, T>& res)
  {
    Element<S, T> src(t);

    do_invert(t.structure(), src, res);
  }
}

#endif /* !INVERT_HXX_ */