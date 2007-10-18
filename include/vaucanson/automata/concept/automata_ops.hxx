// automata_ops.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_OPS_HXX
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_OPS_HXX

# include <iterator>
# include <set>
# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/contract.hh>
# include <vaucanson/algebra/concept/series_base.hh>

namespace vcsn {

#define AutoType(Type)				\
  typename Element<S, T>::Type

  template<typename S, typename T, typename U>
  void
  op_assign(const AutomataBase<S>& concept, T& dst, const U& src)
  {
    typedef typename automaton_traits<T>::hstate_t dst_hstate_t;
    typedef typename automaton_traits<U>::hstate_t src_hstate_t;
    typedef typename automaton_traits<U>::transition_iterator transition_iterator;
    typedef typename automaton_traits<U>::final_iterator final_iterator;
    typedef typename automaton_traits<U>::initial_iterator initial_iterator;
    typedef typename automaton_traits<U>::state_iterator state_iterator;

    dst = T(0, op_transitions(concept, src).size());

    std::map<src_hstate_t, dst_hstate_t> states_map;

    //Mapping src's states to dst's states
    for (state_iterator s = op_states(concept, src).begin(),
	  s_end = op_states(concept, src).end(); s != s_end; ++s)
      states_map[*s] = dst.add_state();

    //Adding all transitions
    for (transition_iterator t = op_transitions(concept, src).begin(),
	  t_end = op_transitions(concept, src).end(); t != t_end; ++t)
      op_add_transition(concept,
			dst,
			states_map[src.src_of(*t)],
			states_map[src.dst_of(*t)],
			src.label_of(*t));

    //Adding initial states
    for (initial_iterator i = op_initial(concept, src).begin(),
	  i_end = op_initial(concept, src).end(); i != i_end; ++i)
      op_set_initial(concept,
		     dst,
		     states_map[*i],
		     op_get_initial(concept, src, *i));

    //Adding final states
    for (final_iterator f = op_final(concept, src).begin(),
	  f_end = op_final(concept, src).end(); f != f_end; ++f)
      op_set_final(concept,
		   dst,
		   states_map[*f], op_get_final(concept, src, *f));

    //FIXME: geometry isn't preserved during this conversion.
  }

  template <class S, class T>
  const typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>&, const T& v)
  {
    return v.tag();
  }

  template <class S, class T>
  typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>&, T& v)
  {
    return v.tag();
  }

  template <class S, class T>
  const typename automaton_traits<T>::geometry_t&
  op_get_geometry(const AutomataBase<S>&, const T& v)
  {
    return v.geometry();
  }

  template <class S, class T>
  typename automaton_traits<T>::geometry_t&
  op_get_geometry(const AutomataBase<S>&, T& v)
  {
    return v.geometry();
  }

  template <class S, class T>
  bool
  op_exists(const AutomataBase<S>& s, const T& v)
  {
    return v.exists(s);
  }

  template <class S, class T>
  typename automaton_traits<T>::states_t
  op_states(const AutomataBase<S>&, const T& v)
  {
    return v.states();
  }

  template <class S, class T>
  typename automaton_traits<T>::transitions_t
  op_transitions(const AutomataBase<S>&, const T& v)
  {
    return v.edges();
  }

  template <class S, class T>
  typename automaton_traits<T>::initial_support_t
  op_initial(const AutomataBase<S>&, const T& v)
  {
    return v.initial();
  }

  template <class S, class T>
  typename automaton_traits<T>::final_support_t
  op_final(const AutomataBase<S>&, const T& v)
  {
    return v.final();
  }

  template <class S, class T>
  void
  op_set_initial(const AutomataBase<S>& ss, T& v,
		 typename automaton_traits<T>::hstate_t state,
		 const AutoType(series_set_elt_t)& s)
  {
    typedef
      typename Element<S, T>::series_set_elt_value_t series_set_elt_value_t;
    v.set_initial(state,
		  s.value(),
		  zero_value(ss.series(),
			     SELECT(series_set_elt_value_t)));
  }

  template <class S, class T>
  typename Element<S, T>::series_set_elt_t
  op_get_initial(const AutomataBase<S>& s,
		 const T& v,
		 typename automaton_traits<T>::hstate_t state)
  {
    return typename Element<S, T>::series_set_elt_t
      (s.series(),
       v.get_initial(state,
		     zero_value(s.series(),
				SELECT(AutoType(series_set_elt_value_t)))));
  }

  template <class S, class T>
  bool
  op_is_initial(const AutomataBase<S>& s,
		 const T& v,
		 typename automaton_traits<T>::hstate_t state)
  {
    return v.is_initial(state, zero_value(s.series(),
				SELECT(AutoType(series_set_elt_value_t))));
  }

  template <class S, class T>
  void
  op_set_final(const AutomataBase<S>& ss, T& v,
	       typename automaton_traits<T>::hstate_t state,
	       const typename Element<S, T>::series_set_elt_t& s)
  {
    v.set_final(state,
		s.value(),
		zero_value(ss.series(),
			   SELECT(AutoType(series_set_elt_value_t))));
  }

  template <class S, class T>
  typename Element<S, T>::series_set_elt_t
  op_get_final(const AutomataBase<S>& s,
	       const T& v,
	       typename automaton_traits<T>::hstate_t state)
  {
    return typename Element<S, T>::series_set_elt_t
      (s.series(),
       v.get_final(state,
		   zero_value(s.series(),
			      SELECT(AutoType(series_set_elt_value_t)))));
  }

  template <class S, class T>
  bool
  op_is_final(const AutomataBase<S>& s,
	      const T& v,
	      typename automaton_traits<T>::hstate_t state)
  {
    return v.is_final(state, zero_value(s.series(),
			      SELECT(AutoType(series_set_elt_value_t))));
  }

  template <class S, class T>
  void
  op_clear_initial(const AutomataBase<S>&, T& v)
  {
    return v.clear_initial();
  }

  template <class S, class T>
  void
  op_clear_final(const AutomataBase<S>&, T& v)
  {
    return v.clear_final();
  }

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_add_state(const AutomataBase<S>&, T& v)
  {
    return v.add_state();
  }

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_choose_state(const AutomataBase<S>& s, const T& v)
  {
    typedef typename automaton_traits<T>::states_t states_t;
    typedef typename states_t::const_iterator state_iterator;
    const states_t& st = op_states(s, v);
    assertion(st.size() > 0);
    int n = misc::random::generate(0, int(st.size() - 1));
    state_iterator ss = st.begin();
    for (; n > 0; --n)
      ++ss;
    return *ss;
  }

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_transition(const AutomataBase<S>&, T& v,
		    typename automaton_traits<T>::hstate_t from,
		    typename automaton_traits<T>::hstate_t to,
		    const typename Element<S, T>::label_t& label)
  {
    return v.add_edge(from, to, label);
  }

  template<class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_weighted_transition(const AutomataBase<S>& s, T& v,
			     typename automaton_traits<T>::hstate_t from,
			     typename automaton_traits<T>::hstate_t to,
			     const typename Element<S, T>::semiring_elt_t& w,
			     const typename Element<S, T>::monoid_elt_value_t& m)
  {
    typename Element<S, T>::series_set_elt_t series (s.series());
    series.assoc(m, w.value());
    return op_add_series_transition(s, v, from, to, series);
  }

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_series_transition(const AutomataBase<S>& s, T& v,
			   typename automaton_traits<T>::hstate_t from,
			   typename automaton_traits<T>::hstate_t to,
			   const typename Element<S, T>::series_set_elt_t& l)
  {
    return op_add_transition(s, v, from, to, l.value());
  }

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_spontaneous(const AutomataBase<S>& s, T& v,
		     typename automaton_traits<T>::hstate_t from,
		     typename automaton_traits<T>::hstate_t to,
		     const typename Element<S, T>::semiring_elt_t& w)
  {
    AutoType(series_set_elt_t) ss(s.series());
    ss.assoc(algebra::identity_as<AutoType(monoid_elt_value_t)>::
	     of(s.series().monoid()), w);
    return op_add_series_transition(s, v, from, to, ss);
  }

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_letter_transition(const AutomataBase<S>& s, T& v,
			   typename automaton_traits<T>::hstate_t from,
			   typename automaton_traits<T>::hstate_t to,
			   const typename Element<S, T>::letter_t& l)
  {
    return op_add_transition(s, v, from, to, l);
  }

  template <class S, class T>
  void
  op_update(const AutomataBase<S>&, T& v,
	    typename automaton_traits<T>::htransition_t  e,
	    const AutoType(label_t)& l)
  {
    // FIXME: test that l != 0.
    v.update(e, l);
  }

  template <class S, class T>
  void
  op_del_state(const AutomataBase<S>&, T& v,
	       typename automaton_traits<T>::hstate_t s)
  {
    v.del_state(s);
  }

  template <class S, class T>
  void
  op_del_transition(const AutomataBase<S>&, T& v,
		    typename automaton_traits<T>::htransition_t e)
  {
    v.del_edge(e);
  }

  template <class S, class T>
  bool
  op_has_state(const AutomataBase<S>&, const T& v,
	       typename automaton_traits<T>::hstate_t s)
  {
    return v.has_state(s);
  }

  template <class S, class T>
  bool
  op_has_transition(const AutomataBase<S>&, const T& v,
		    typename automaton_traits<T>::htransition_t e)
  {
    return v.has_edge(e);
  }

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_src_of(const AutomataBase<S>&, const T& v,
	    typename automaton_traits<T>::htransition_t e)
  {
    return v.src_of(e);
  }

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_dst_of(const AutomataBase<S>&, const T& v,
	    typename automaton_traits<T>::htransition_t e)
  {
    return v.dst_of(e);
  }

  template <class S, class T>
  typename Element<S, T>::label_t
  op_label_of(const AutomataBase<S>&, const T& v,
	      typename automaton_traits<T>::htransition_t e)
  {
    return v.label_of(e);
  }

  template <class S, class T>
  const typename Element<S, T>::series_set_elt_t
  op_series_of(const AutomataBase<S>& s, const T& v,
	       typename automaton_traits<T>::htransition_t e)
  {
    return typename Element<S, T>::series_set_elt_t
      (s.series(),
       v.label_of(e));
  }

  template <class S, class T>
  typename Element<S, T>::series_set_elt_value_t
  op_series_value_of(const AutomataBase<S>& s, const T& v,
		     typename automaton_traits<T>::htransition_t e)
  {
    return op_series_of(s, v, e).value();
  }

  template <class S, class T>
  typename Element<S, T>::monoid_elt_t
  op_word_of(const AutomataBase<S>& s, const T& v,
	     typename automaton_traits<T>::htransition_t e)
  {
    return typename Element<S, T>::monoid_elt_t
      (s.series().monoid(),
       v.label_of(e));
  }

  template <class S, class T>
  typename Element<S, T>::semiring_elt_t
  op_weight_of(const AutomataBase<S>& s, const T& v,
	       typename automaton_traits<T>::htransition_t e)
  {
    return op_series_of(s, v, e).get(op_word_of(s, v, e));
  }

  template <class S, class T>
  typename Element<S, T>::monoid_elt_value_t
  op_word_value_of(const AutomataBase<S>& s, const T& v,
		   typename automaton_traits<T>::htransition_t e)
  {
    return op_word_of(s, v, e).value();
  }

  template <class S, class T>
  typename Element<S, T>::letter_t
  op_letter_of(const AutomataBase<S>&, const T& v,
	       typename automaton_traits<T>::htransition_t e)
  {
    return v.label_of(e);
  }

  template <class S, class T>
  bool
  op_is_spontaneous(const AutomataBase<S>& s, const T& v,
		    typename automaton_traits<T>::htransition_t e)
  {
    return (op_series_of(s, v, e) ==
	    algebra::identity_as<AutoType(series_set_elt_value_t)>::of(s.series()));
  }

  template<typename T>
  struct always_true
  {
      bool operator()(typename automaton_traits<T>::htransition_t) const
      {
	return true;
      }
  };

  template <class S, class T, class Letter>
  class letter_query
  {
    public:
      letter_query(const S* s, const T* v, const Letter& l) :
	s_ (s),
	v_ (v),
	w_ (s->series().monoid(), l)
      {
      }

      bool operator()(typename automaton_traits<T>::htransition_t e) const
      {
	return (op_series_get(s_->series(),
			      op_series_of(*s_, *v_, e).value(),
			      w_.value())
		!= algebra::zero_as<AutoType(semiring_elt_value_t)>
		::of(s_->series().semiring()));
      }

    private:
      const S*			s_;
      const T*			v_;
      AutoType(monoid_elt_t)	w_;
  };

  template <class S, class T, class Letter>
  letter_query<S, T, Letter>
  make_letter_query(const S& s, const T& t, const Letter& l)
  {
    return letter_query<S, T, Letter> (&s, &t, l);
  }

  template <class S, class T>
  class spontaneous_query
  {
    public:
      spontaneous_query(const S& s, const T& v):
	s_(s),
	v_(v)
      {}

      bool operator()(typename automaton_traits<T>::htransition_t e) const
      {
	return (op_series_of(s_, v_, e)
		.get(algebra::identity_as<AutoType(monoid_elt_value_t)>::of
		     (s_.series().monoid()))
		!= algebra::zero_as<AutoType(semiring_elt_value_t)>
		::of(s_.series().semiring()));
      }

    private:
      const S& s_;
      const T& v_;
  };

  template <class S, class T>
  spontaneous_query<S, T> make_spontaneous_query(const S& s,
						 const T& t)
  {
    return spontaneous_query<S, T>(s.self(), t);
  }

    /*---------.
    | Deltas.  |
    `---------*/

  template <class S, class T,
	    typename OutputIterator, typename Kind>
  void op_delta(const AutomataBase<S>&, const T& v,
		OutputIterator res,
		typename automaton_traits<T>::hstate_t from,
		delta_kind::kind<Kind> k)
  {
    v.delta(res, from, always_true<T>(), k);
  }

  template <class S, class T,
	    typename OutputIterator, typename L, typename Kind>
  void op_delta(const AutomataBase<S>&, const T& v,
		OutputIterator res,
		typename automaton_traits<T>::hstate_t from,
		const L& query,
		delta_kind::kind<Kind> k)
  {
    v.delta(res, from, query, k);
  }

  template <class S, class T,
	    typename OutputIterator, typename L, typename Kind>
  void op_letter_delta(const AutomataBase<S>& s, const T& v,
		       OutputIterator res,
		       typename automaton_traits<T>::hstate_t from,
		       const L& letter,
		       delta_kind::kind<Kind> k)
  {
    v.delta(res, from, make_letter_query(s.self(), v, letter), k);
  }

  template <class S, class T,
	    typename OutputIterator, typename Kind>
  void op_spontaneous_delta(const AutomataBase<S>& s,
			    const T& v,
			    OutputIterator res,
			    typename automaton_traits<T>::hstate_t from,
			    delta_kind::kind<Kind> k)
  {
    v.delta (res, from, make_spontaneous_query(s.self(), v), k);
  }

    /*----------.
    | Deltacs.  |
    `----------*/

  template <class S, class T,
	    typename Container, typename Kind>
  void op_deltac(const AutomataBase<S>&, const T& v,
		 Container& res, typename automaton_traits<T>::hstate_t from, delta_kind::kind<Kind> k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    v.delta(i, from, always_true<T>(), k);
  }

  template <class S, class T,
	    typename Container, typename L, typename Kind>
  void op_deltac(const AutomataBase<S>&,
		 const T& v,
		 Container& res,
		 typename automaton_traits<T>::hstate_t from,
		 const L& query,
		 delta_kind::kind<Kind> k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    v.delta(i, from, query, k);
  }


  template <class S, class T,
	    typename Container, typename L, typename Kind>
  void op_letter_deltac(const AutomataBase<S>& s,
			const T& v,
			Container& res,
			typename automaton_traits<T>::hstate_t from,
			const L& letter,
			delta_kind::kind<Kind> k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    v.delta(i, from, make_letter_query(s.self(), v, letter), k);
  }

  template <class S, class T, class Container, typename Kind>
  void op_spontaneous_deltac(const AutomataBase<S>& s,
			     const T& v,
			     Container& res,
			     typename automaton_traits<T>::hstate_t from,
			     delta_kind::kind<Kind> k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    v.delta (i, from, make_spontaneous_query(s.self(), v), k);
  }

    /*----------.
    | Deltafs.  |
    `----------*/

  template <class S, class T,
	    typename Functor, typename Kind>
  void op_deltaf(const AutomataBase<S>&, const T& v,
		 Functor& fun, typename automaton_traits<T>::hstate_t from, delta_kind::kind<Kind> k)
  {
    v.deltaf(fun, from, always_true<T>(), k);
  }

  template <class S, class T,
	    typename Functor, typename L, typename Kind>
  void op_deltaf(const AutomataBase<S>&,
		 const T& v,
		 Functor& fun,
		 typename automaton_traits<T>::hstate_t from,
		 const L& query,
		 delta_kind::kind<Kind> k)
  {
    v.deltaf(fun, from, query, k);
  }


  template <class S, class T,
	    typename Functor, typename L, typename Kind>
  void op_letter_deltaf(const AutomataBase<S>& s,
			const T& v,
			Functor& fun,
			typename automaton_traits<T>::hstate_t from,
			const L& letter,
			delta_kind::kind<Kind> k)
  {
    v.deltaf(fun, from, make_letter_query(s.self(), v, letter), k);
  }

  template <class S, class T, class Functor, typename Kind>
  void op_spontaneous_deltaf(const AutomataBase<S>& s,
			     const T& v,
			     Functor& fun,
			     typename automaton_traits<T>::hstate_t from,
			     delta_kind::kind<Kind> k)
  {
    v.deltaf(fun, from, make_spontaneous_query(s.self(), v), k);
  }


    /*-----------------.
    | Reverse deltas.  |
    `-----------------*/

  template <class S, class T,
	    typename OutputIterator, typename Kind>
  void op_rdelta(const AutomataBase<S>&, const T& v,
		 OutputIterator res,
		 typename automaton_traits<T>::hstate_t from,
		 delta_kind::kind<Kind> k)
  {
    v.rdelta (res, from, always_true<T>(), k);
  }

  template <class S, class T,
	    typename OutputIterator, typename L, typename Kind>
  void op_rdelta(const AutomataBase<S>&, const T& v,
		 OutputIterator res,
		 typename automaton_traits<T>::hstate_t from,
		 const L& query,
		 delta_kind::kind<Kind> k)
  {
    v.rdelta(res, from, query, k);
  }

  template <class S, class T,
	    typename OutputIterator, typename L, typename Kind>
  void op_letter_rdelta(const AutomataBase<S>& s, const T& v,
			OutputIterator res,
			typename automaton_traits<T>::hstate_t from,
			const L& letter,
			delta_kind::kind<Kind> k)
  {
    v.rdelta(res, from, make_letter_query(s.self(), v, letter), k);
  }

  template <class S, class T,
	    typename OutputIterator, typename Kind>
  void op_spontaneous_rdelta(const AutomataBase<S>& s, const T& v,
			     OutputIterator res,
			     typename automaton_traits<T>::hstate_t from,
			     delta_kind::kind<Kind> k)
  {
    v.rdelta(res, from, make_spontaneous_query(s.self(), v), k);
  }

    /*------------------.
    | Reverse deltacs.  |
    `------------------*/

  template <class S, class T,
	    typename Container, typename Kind>
  void op_rdeltac(const AutomataBase<S>&, const T& v,
		  Container& res, typename automaton_traits<T>::hstate_t from, delta_kind::kind<Kind> k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    v.rdelta(i, from, always_true<T>(), k);
  }

  template <class S, class T,
	    typename Container, typename L, typename Kind>
  void op_rdeltac(const AutomataBase<S>&,
		  const T& v,
		  Container& res,
		  typename automaton_traits<T>::hstate_t from,
		  const L& query,
		  delta_kind::kind<Kind> k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    v.rdelta(i, from, query, k);
  }


  template <class S, class T,
	    typename Container, typename L, typename Kind>
  void op_letter_rdeltac(const AutomataBase<S>& s,
			 const T& v,
			 Container& res,
			 typename automaton_traits<T>::hstate_t from,
			 const L& letter,
			 delta_kind::kind<Kind> k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    v.rdelta (i, from, make_letter_query(s.self(), v, letter), k);
  }

  template <class S, class T, class  Container, typename Kind>
  void op_spontaneous_rdeltac(const AutomataBase<S>& s,
			      const T& v,
			      Container& res,
			      typename automaton_traits<T>::hstate_t from,
			      delta_kind::kind<Kind> k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    v.rdelta (i, from, make_spontaneous_query(s.self(), v), k);
  }

    /*------------------.
    | Reverse Deltafs.  |
    `------------------*/

  template <class S, class T,
	    typename Functor, typename Kind>
  void op_rdeltaf(const AutomataBase<S>&, const T& v,
		  Functor& fun, typename automaton_traits<T>::hstate_t from, delta_kind::kind<Kind> k)
  {
    v.rdeltaf(fun, from, always_true<T>(), k);
  }

  template <class S, class T,
	    typename Functor, typename L, typename Kind>
  void op_rdeltaf(const AutomataBase<S>&,
		  const T& v,
		  Functor& fun,
		  typename automaton_traits<T>::hstate_t from,
		  const L& query,
		  delta_kind::kind<Kind> k)
  {
    v.rdeltaf(fun, from, query, k);
  }


  template <class S, class T,
	    typename Functor, typename L, typename Kind>
  void op_letter_rdeltaf(const AutomataBase<S>& s,
			 const T& v,
			 Functor& fun,
			 typename automaton_traits<T>::hstate_t from,
			 const L& letter,
			 delta_kind::kind<Kind> k)
  {
    v.rdeltaf(fun, from, make_letter_query(s.self(), v, letter), k);
  }

  template <class S, class T, class Functor, typename Kind>
  void op_spontaneous_rdeltaf(const AutomataBase<S>& s,
			      const T& v,
			      Functor& fun,
			      typename automaton_traits<T>::hstate_t from,
			      delta_kind::kind<Kind> k)
  {
    v.rdeltaf(fun, from, make_spontaneous_query(s.self(), v), k);
  }


} // vcsn

# undef AutoType

#endif // ! VCSN_AUTOMATA_CONCEPT_AUTOMATA_OPS_HXX
