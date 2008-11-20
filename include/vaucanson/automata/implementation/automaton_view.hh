// automaton_view.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_AUTOMATON_VIEW_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_AUTOMATON_VIEW_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  template <class T>
  class IdentityView
  {
    public:
      IdentityView();
      IdentityView(T&);
      IdentityView(const T&);
      IdentityView(const IdentityView&);

      const T& object() const;
      T& object();

      operator T&();
      operator const T&() const;

    private:
      T* object_;
      const T* const_object_;
  };

  template <typename T>
  struct automaton_traits< IdentityView<T> >
    : automaton_traits<T>
  {
  };


#define AutoType(Type)				\
  typename Element<S, IdentityView<T> >::Type

  template <class S, class T>
  const typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>&, IdentityView<T>&);

  template <class S, class T>
  const typename automaton_traits<T>::geometry_t&
  op_get_geometry(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::geometry_t&
  op_get_geometry(const AutomataBase<S>&, IdentityView<T>&);

  template <class S, class T>
  bool
  op_exists(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::states_t
  op_states(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::transitions_t
  op_transitions(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::initial_support_t
  op_initial(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::final_support_t
  op_final(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  void
  op_set_initial(const AutomataBase<S>&, IdentityView<T>&,
		 const typename automaton_traits<T>::hstate_t& state,
		 const AutoType(series_set_elt_t)& s);

  template <class S, class T>
  AutoType(series_set_elt_t)
  op_get_initial(const AutomataBase<S>&,
		 const IdentityView<T>&,
		 const typename automaton_traits<T>::hstate_t& state);

  template <class S, class T>
  void
  op_set_final(const AutomataBase<S>&, IdentityView<T>&,
	       const typename automaton_traits<T>::hstate_t& state,
	       const typename Element<S, T>::series_set_elt_t& s);

  template <class S, class T>
  typename Element<S, T>::series_set_elt_t
  op_get_final(const AutomataBase<S>&,
	       const IdentityView<T>&,
	       const typename automaton_traits<T>::hstate_t& state);

  template <class S, class T>
  void
  op_clear_initial(const AutomataBase<S>&, IdentityView<T>&);

  template <class S, class T>
  void
  op_clear_final(const AutomataBase<S>&, IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_add_state(const AutomataBase<S>&, IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_choose_state(const AutomataBase<S>&, IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_transition(const AutomataBase<S>&, IdentityView<T>&,
		    const typename automaton_traits<T>::hstate_t& from,
		    const typename automaton_traits<T>::hstate_t& to,
		    const typename Element<S, T>::label_t& label);

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_series_transition(const AutomataBase<S>&, IdentityView<T>&,
			   const typename automaton_traits<T>::hstate_t& from,
			   const typename automaton_traits<T>::hstate_t& to,
			   const typename Element<S, T>::series_set_elt_t&);

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_spontaneous(const AutomataBase<S>&, IdentityView<T>&,
		     const typename automaton_traits<T>::hstate_t& from,
		     const typename automaton_traits<T>::hstate_t& to);

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_letter_transition(const AutomataBase<S>&, IdentityView<T>&,
			   const typename automaton_traits<T>::hstate_t& from,
			   const typename automaton_traits<T>::hstate_t& to,
			   const typename Element<S, T>::letter_t&);

  template <class S, class T>
  void
  op_update(const AutomataBase<S>&, IdentityView<T>&,
	    const typename automaton_traits<T>::htransition_t&,
	    const AutoType(label_t)& l);

  template <class S, class T>
  void
  op_del_state(const AutomataBase<S>&, IdentityView<T>&,
	       const typename automaton_traits<T>::hstate_t&);

  template <class S, class T>
  void
  op_del_transition(const AutomataBase<S>&, IdentityView<T>&,
		    const typename automaton_traits<T>::htransition_t&);

  template <class S, class T>
  bool
  op_has_state(const AutomataBase<S>&, const IdentityView<T>&,
	       const typename automaton_traits<T>::hstate_t&);

  template <class S, class T>
  bool
  op_has_transition(const AutomataBase<S>&, const IdentityView<T>&,
		    const typename automaton_traits<T>::htransition_t&);

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_src_of(const AutomataBase<S>&, const IdentityView<T>&,
	    const typename automaton_traits<T>::htransition_t&);

  template <class S, class T>
  typename automaton_traits<T>::hstate_t
  op_dst_of(const AutomataBase<S>&, const IdentityView<T>&,
	    const typename automaton_traits<T>::htransition_t&);

  template <class S, class T>
  typename Element<S, T>::label_t
  op_label_of(const AutomataBase<S>&, const IdentityView<T>&,
	      const typename automaton_traits<T>::htransition_t&);

  template <class S, class T>
  const typename Element<S, T>::series_set_elt_t
  op_series_of(const AutomataBase<S>&, const IdentityView<T>&,
	       const typename automaton_traits<T>::htransition_t&);

  template <class S, class T>
  typename Element<S, T>::series_set_elt_value_t
  op_series_value_of(const AutomataBase<S>&, const IdentityView<T>&,
		     const typename automaton_traits<T>::htransition_t&);


  template <class S, class T>
  typename Element<S, T>::monoid_elt_t
  op_word_of(const AutomataBase<S>&, const IdentityView<T>&,
	     const typename automaton_traits<T>::htransition_t&);

  template <class S, class T>
  typename Element<S, T>::monoid_elt_value_t
  op_word_value_of(const AutomataBase<S>&, const IdentityView<T>&,
		   const typename automaton_traits<T>::htransition_t&);

  template <class S, class T>
  typename Element<S, T>::letter_t
  op_letter_of(const AutomataBase<S>&, const IdentityView<T>&,
	       const typename automaton_traits<T>::htransition_t&);

  template <class S, class T>
  bool
  op_is_spontaneous(const AutomataBase<S>&, const IdentityView<T>&,
		    const typename automaton_traits<T>::htransition_t&);

} // vcsn

# undef AutoType


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/automata/implementation/automaton_view.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_AUTOMATON_VIEW_HH
