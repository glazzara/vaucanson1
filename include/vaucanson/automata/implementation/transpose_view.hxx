// transpose_view.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_TRANSPOSE_VIEW_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_TRANSPOSE_VIEW_HXX

# include <vaucanson/automata/implementation/transpose_view.hh>

namespace vcsn {

#define AutoType(Type)				\
  typename Element<S, TransposeView<T> >::Type

  template <class T>
  TransposeView<T>::TransposeView()
  {}

  template <class T>
  TransposeView<T>::TransposeView(const T& object):
    IdentityView<T>(object)
  {}

  template <class T>
  TransposeView<T>::TransposeView(T& object):
    IdentityView<T>(object)
  {}

  template <class T>
  TransposeView<T>::TransposeView(const TransposeView& t):
    IdentityView<T>(t)
  {}

  template <class S, class T>
  Element<S, TransposeView<T> >
  transpose_view(Element<S, T>& a)
  {
    return Element<S, TransposeView<T> >
      (a.structure(), TransposeView<T>(a.value()));
  }

  template <class S, class T>
  const Element<S, TransposeView<T> >
  transpose_view(const Element<S, T>& a)
  {
    return Element<S, TransposeView<T> >
      (a.structure(), TransposeView<T>(a.value()));
  }

  template <class S, class T>
  const typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>& s, const TransposeView<T>& v)
  {
    return op_get_tag(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>& s, TransposeView<T>& v)
  {
    return op_get_tag(s, v.object());
  }

  template <class S, class T>
  const typename automaton_traits<T>::geometry_t&
  op_geometry(const AutomataBase<S>& s, const TransposeView<T>& v)
  {
    return op_geometry(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::geometry_t&
  op_geometry(const AutomataBase<S>& s, TransposeView<T>& v)
  {
    return op_geometry(s, v.object());
  }

  template <class S, class T>
  bool
  op_exists(const AutomataBase<S>& s, const TransposeView<T>& v)
  {
    return op_exists(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::states_t
  op_states(const AutomataBase<S>& s, const TransposeView<T>& v)
  {
    return op_states(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::transitions_t
  op_transitions(const AutomataBase<S>& s, const TransposeView<T>& v)
  {
    return op_transitions(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_add_state(const AutomataBase<S>& s, TransposeView<T>& v)
  {
    return op_add_state(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_choose_state(const AutomataBase<S>& s, TransposeView<T>& v)
  {
    return op_choose_state(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_transition(const AutomataBase<S>& s, TransposeView<T>& v,
		    const typename automaton_traits<T>::hstate_t& from,
		    const typename automaton_traits<T>::hstate_t& to,
		    const typename Element<S, T>::label_t& label)
  {
    return op_add_transition(s, v.object(), from, to, label);
  }

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_series_transition(const AutomataBase<S>& s,
			   TransposeView<T>& v,
			   const typename automaton_traits<T>::hstate_t& from,
			   const typename automaton_traits<T>::hstate_t& to,
			   const typename Element<S, T>::series_set_elt_t& se)
  {
    return op_add_series_transition(s, v.object(), from, to, se);
  }

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_spontaneous(const AutomataBase<S>& s, TransposeView<T>& v,
		     const typename automaton_traits<T>::hstate_t& from,
		     const typename automaton_traits<T>::hstate_t& to)
  {
    return op_add_spontaneous(s, v.object(), from, to);
  }

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_letter_transition(const AutomataBase<S>& s, TransposeView<T>& v,
			   const typename automaton_traits<T>::hstate_t& from,
			   const typename automaton_traits<T>::hstate_t& to,
			   const typename Element<S, T>::letter_t& e)
  {
    return op_add_letter_transition(s, v.object(), from, to, e);
  }

  template <class S, class T>
  void
  op_update(const AutomataBase<S>& s, TransposeView<T>& v,
	    const typename automaton_traits<T>::htransition_t& e,
	    const AutoType(label_t)& l)
  {
    op_update(s, v.object(), e, l);
  }

  template <class S, class T>
  void
  op_del_state(const AutomataBase<S>& s, TransposeView<T>& v,
	       const typename automaton_traits<T>::hstate_t& st)
  {
    op_del_state(s, v.object(), st);
  }

  template <class S, class T>
  void
  op_del_transition(const AutomataBase<S>& s, TransposeView<T>& v,
		    const typename automaton_traits<T>::htransition_t& e)
  {
    op_del_transition(s, v.object(), e);
  }

  template <class S, class T>
  bool
  op_has_state(const AutomataBase<S>& s,
	       const TransposeView<T>& v,
	       const typename automaton_traits<T>::hstate_t& st)
  {
    return op_has_state(s, v.object(), st);
  }

  template <class S, class T>
  bool
  op_has_transition(const AutomataBase<S>& s,
		    const TransposeView<T>& v,
		    const typename automaton_traits<T>::htransition_t& e)
  {
    return op_has_transition(s, v.object(), e);
  }

  template <class S, class T>
  typename Element<S, T>::label_t
  op_label_of(const AutomataBase<S>& s,
	      const TransposeView<T>& v,
	      const typename automaton_traits<T>::htransition_t& e)
  {
    return op_label_of(s, v.object(), e);
  }

  template <class S, class T>
  const typename Element<S, T>::series_set_elt_t
  op_series_of(const AutomataBase<S>& s,
	       const TransposeView<T>& v,
	       const typename automaton_traits<T>::htransition_t& e)
  {
    typename Element<S, T>::series_set_elt_t r =
      op_series_of(s, v.object(), e);
    r.transpose();
    return r;
  }

  template <class S, class T>
  typename Element<S, T>::series_set_elt_value_t
  op_series_value_of(const AutomataBase<S>& s,
		     const TransposeView<T>& v,
		     const typename automaton_traits<T>::htransition_t& e)
  {
    return op_series_value_of(s, v.object(), e);
  }

  template <class S, class T>
  typename Element<S, T>::monoid_elt_t
  op_word_of(const AutomataBase<S>& s,
	     const TransposeView<T>& v,
	     const typename automaton_traits<T>::htransition_t& e)
  {
    return op_word_of(s, v.object(), e);
  }

  template <class S, class T>
  typename Element<S, T>::monoid_elt_value_t
  op_word_value_of(const AutomataBase<S>& s,
		   const TransposeView<T>& v,
		   const typename automaton_traits<T>::htransition_t& e)
  {
    return op_word_value_of(s, v.object(), e);
  }

  template <class S, class T>
  typename Element<S, T>::letter_t
  op_letter_of(const AutomataBase<S>& s,
	       const TransposeView<T>& v,
	       const typename automaton_traits<T>::htransition_t& e)
  {
    return op_letter_of(s, v.object(), e);
  }

  template <class S, class T>
  bool
  op_is_spontaneous(const AutomataBase<S>& s,
		    const TransposeView<T>& v,
		    const typename automaton_traits<T>::htransition_t& e)
  {
    return op_is_spontaneous(s, v.object(), e);
  }

  template <class S, class T>
  typename automaton_traits<TransposeView<T> >::initial_support_t
  op_initial(const AutomataBase<S>& s, const TransposeView<T>& v)
  {
    return op_final(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<TransposeView<T> >::final_support_t
  op_final(const AutomataBase<S>& s, const TransposeView<T>& v)
  {
    return op_initial(s, v.object());
  }

  template <class S, class T>
  void
  op_set_initial(const AutomataBase<S>& ss, TransposeView<T>& v,
		 const typename automaton_traits<T>::hstate_t& state,
		 const AutoType(series_set_elt_t)& s)
  {
    return op_set_final(ss, v.object(), state, s);
  }

  template <class S, class T>
  AutoType(series_set_elt_t)
  op_get_initial(const AutomataBase<S>& s,
		 const TransposeView<T>& v,
		 const typename automaton_traits<T>::hstate_t& state)
  {
    AutoType(series_set_elt_t) r = op_get_final(s, v.object(), state);
    r.transpose();
    return r;
  }

  template <class S, class T>
  void
  op_set_final(const AutomataBase<S>& ss, TransposeView<T>& v,
	       const typename automaton_traits<T>::hstate_t& state,
	       const typename Element<S, T>::series_set_elt_t& s)
  {
    op_set_initial(ss, v.object(), state, s);
  }

  template <class S, class T>
  typename Element<S, T>::series_set_elt_t
  op_get_final(const AutomataBase<S>& s,
	       const TransposeView<T>& v,
	       const typename automaton_traits<T>::hstate_t& state)
  {
    typename Element<S, T>::series_set_elt_t r = op_get_initial(s, v.object(),
								state);
    r.transpose();
    return r;
  }

  template <class S, class T>
  void
  op_clear_initial(const AutomataBase<S>& s, TransposeView<T>& v)
  {
    op_clear_final(s, v.object());
  }

  template <class S, class T>
  void
  op_clear_final(const AutomataBase<S>& s, TransposeView<T>& v)
  {
    op_clear_initial(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_src_of(const AutomataBase<S>& s,
	    const TransposeView<T>& v,
	    const typename automaton_traits<T>::htransition_t& e)
  {
    return op_dst_of(s, v.object(), e);
  }

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_dst_of(const AutomataBase<S>& s,
	    const TransposeView<T>& v,
	    const typename automaton_traits<T>::htransition_t& e)
  {
    return op_src_of(s, v.object(), e);
  }

  // output_return_type = Container
  // output_type	= const typename automaton_traits<T>::htransition_t&
  // direction		= output

  template <class S, class T,
	    typename Container>
  void op_deltac(const AutomataBase<S>& s,
		 const TransposeView<T>& v,
		 Container& res, const typename automaton_traits<T>::hstate_t& from, delta_kind::transitions k)
  {
    op_rdeltac(s, v.object(), res, from, k);
  }

  template <class S, class T,
	    typename Container, typename L>
  void op_deltac(const AutomataBase<S>& s,
		 const TransposeView<T>& v,
		 Container& res,
		 const typename automaton_traits<T>::hstate_t& from,
		 const L& query,
		 delta_kind::transitions k)
  {
    op_rdeltac(s, v.object(), res, from, query, k);
  }

  template <class S, class T,
	    typename Container, typename L>
  void op_letter_deltac(const AutomataBase<S>& s,
			const TransposeView<T>& v,
			Container& res,
			const typename automaton_traits<T>::hstate_t& from,
			const L& letter,
			delta_kind::transitions k)
  {
    op_letter_rdeltac(s, v.object(), res, from, letter, k);
  }

  template <class S, class T, class Container>
  void op_spontaneous_deltac(const AutomataBase<S>& s,
			     const TransposeView<T>& v,
			     Container& res,
			     const typename automaton_traits<T>::hstate_t& from,
			     delta_kind::transitions k)
  {
    op_spontaneous_rdeltac(s, v.object(), res, from, k);
  }

  // output_return_type = Container
  // output_type	= const typename automaton_traits<T>::hstate_t&
  // direction		= output

  template<class S, class T, typename Container>
  void op_deltac(const AutomataBase<S>& s,
		 const TransposeView<T>& v,
		 Container& res, const typename automaton_traits<T>::hstate_t& from, delta_kind::states k)
  {
    op_rdeltac(s, v.object(), res, from, k);
  }

  template<class S, class T, typename Container, typename L>
  void op_deltac(const AutomataBase<S>& s,
		 const TransposeView<T>& v,
		 Container& res,
		 const typename automaton_traits<T>::hstate_t& from,
		 const L& query,
		 delta_kind::states k)
  {
    op_rdeltac(s, v.object(), res, from, k);
  }

  template<class S, class T, typename Container, typename L>
  void op_letter_deltac(const AutomataBase<S>& s,
			const TransposeView<T>& v,
			Container& res,
			const typename automaton_traits<T>::hstate_t& from,
			const L& letter,
			delta_kind::states k)
  {
    op_letter_rdeltac(s, v.object(), res, from, letter, k);
  }

  template<class S, class T, typename Container>
  void op_spontaneous_deltac(const AutomataBase<S>& s,
			     const TransposeView<T>& v,
			     Container& res,
			     const typename automaton_traits<T>::hstate_t& from,
			     delta_kind::states k)
  {
    op_spontaneous_rdeltac(s, v.object(), res, from, k);
  }

  // output_return_type = Container
  // output_type	= const typename automaton_traits<T>::htransition_t&
  // direction		= input

  template<class S, class T, typename Container>
  void op_rdeltac(const AutomataBase<S>& s, const TransposeView<T>& v,
		  Container& res, const typename automaton_traits<T>::hstate_t& from, delta_kind::transitions k)
  {
    op_deltac(s, v.object(), res, from, k);
  }

  template<class S, class T, typename Container, typename L>
  void op_rdeltac(const AutomataBase<S>& s, const TransposeView<T>& v,
		  Container& res,
		  const typename automaton_traits<T>::hstate_t& from,
		  const L& query,
		  delta_kind::transitions k)
  {
    op_deltac(s, v.object(), res, from, query, k);
  }

  template<class S, class T, typename Container, typename L>
  void op_letter_rdeltac(const AutomataBase<S>& s, const TransposeView<T>& v,
			 Container& res,
			 const typename automaton_traits<T>::hstate_t& from,
			 const L& letter,
			 delta_kind::transitions k)
  {
    op_letter_deltac(s, v.object(), res, from, letter, k);
  }

  template<class S, class T, typename Container>
  void op_spontaneous_rdeltac(const AutomataBase<S>& s,
			      const TransposeView<T>& v,
			      Container& res,
			      const typename automaton_traits<T>::hstate_t& from,
			      delta_kind::transitions k)
  {
    op_spontaneous_deltac(s, v.object(), res, from, k);
  }

  // output_return_type = Container
  // output_type	= const typename automaton_traits<T>::hstate_t&
  // direction		= input

  template<class S, class T, typename Container>
  void op_rdeltac(const AutomataBase<S>& s, const TransposeView<T>& v,
		  Container& res, const typename automaton_traits<T>::hstate_t& from, delta_kind::states k)
  {
    op_deltac(s, v.object(), res, from, k);
  }

  template<class S, class T, typename Container, typename L>
  void op_rdeltac(const AutomataBase<S>& s, const TransposeView<T>& v,
		  Container& res,
		  const typename automaton_traits<T>::hstate_t& from,
		  const L& query,
		  delta_kind::states k)
  {
    op_deltac(s, v.object(), res, from, query, k);
  }

  template<class S, class T, typename Container, typename L>
  void op_letter_rdeltac(const AutomataBase<S>& s, const TransposeView<T>& v,
			 Container& res,
			 const typename automaton_traits<T>::hstate_t& from,
			 const L& letter,
			 delta_kind::states k)
  {
    op_letter_deltac(s, v.object(), res, from, letter, k);
  }

  template<class S, class T, typename Container>
  void op_spontaneous_rdeltac(const AutomataBase<S>& s,
			      const TransposeView<T>& v,
			      Container& res,
			      const typename automaton_traits<T>::hstate_t& from,
			      delta_kind::states k)
  {
    op_spontaneous_deltac(s, v.object(), res, from, k);
  }

} // vcsn

# undef AutoType

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_TRANSPOSE_VIEW_HXX
