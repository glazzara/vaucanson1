// kind_adapter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_KIND_ADAPTER_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_KIND_ADAPTER_HH

# include <vaucanson/automata/concept/automata_kind.hh>

namespace vcsn {

  /// we define a series of macros to make the data structure for
  /// automaton simpler.

#define ADAPT_ADD_LETTER_TRANSITION_TO_SERIES_LABEL(T...)		\
  htransition_t								\
  op_add_letter_transition(const AutomataBase<S>& s,			\
			   T& v,					\
			   hstate_t from,				\
			   hstate_t to,					\
			   const typename Element<S, T >::letter_t & l)	\
  {									\
    typedef typename S::series_set_t		series_set_t;		\
    typedef typename series_set_t::monoid_t	monoid_t;		\
    typedef typename series_set_t::semiring_t	semiring_t;		\
    typedef typename Element<S, T >::monoid_elt_value_t			\
      monoid_elt_value_t;						\
    typedef typename Element<S, T >::semiring_elt_value_t		\
      semiring_elt_value_t;						\
    typedef typename Element<S, T >::series_set_elt_value_t		\
      series_set_elt_value_t;						\
									\
    Element<series_set_t, series_set_elt_value_t> label (s.series());	\
									\
    Element<monoid_t, monoid_elt_value_t> word (s.series().monoid(), l); \
    label.assoc(word,							\
		s.series().semiring().identity(SELECT(semiring_elt_value_t))); \
									\
    return op_add_transition(s, v, from, to, label.value());		\
  }

#define ADAPT_LETTER_OF_TO_SERIES_LABEL(T...)				\
  typename Element<AutomataBase<S>, T >::letter_t			\
  op_letter_of(const AutomataBase<S>& s,				\
	       const T& v,						\
	       htransition_t e)						\
  {									\
    typedef typename S::series_set_t series_set_t;			\
    typedef typename series_set_t::monoid_t monoid_t;			\
    typedef typename Element<S, T >::monoid_elt_value_t			\
      word_value_t;							\
    typedef typename Element<S, T >::series_set_elt_value_t		\
      series_set_elt_value_t;						\
									\
    Element<series_set_t, series_set_elt_value_t> sl = op_series_of(s, v, e); \
    precondition(sl.supp().size() == 1);				\
    Element<monoid_t, word_value_t> w = sl.choose_from_supp();		\
    precondition(w.length() == 1);					\
    return *w.begin();							\
  }

#define ADAPT_WORD_OF_TO_SERIES_LABEL(T...)				\
  typename Element<AutomataBase<S>, T >::monoid_elt_t			\
  op_word_of(const AutomataBase<S>& s,					\
	     const T& v,						\
	     htransition_t e)						\
  {									\
    typedef typename S::series_set_t series_set_t;			\
    typedef typename series_set_t::monoid_t monoid_t;			\
    typedef typename Element<S, T >::monoid_elt_value_t			\
      word_value_t;							\
    typedef typename Element<S, T >::series_set_elt_value_t		\
      series_set_elt_value_t;						\
									\
    Element<series_set_t, series_set_elt_value_t> sl = op_series_of(s, v, e); \
    precondition(sl.supp().size() == 1);				\
    Element<monoid_t, word_value_t> w = sl.choose_from_supp();		\
    return w;								\
  }

#define ADAPT_ADD_SERIE_TRANSITION_TO_LETTERS_LABEL(T...)		\
  htransition_t								\
  op_add_series_transition(const AutomataBase<S>& a_set,		\
			   T& v,					\
			   hstate_t from,				\
			   hstate_t to,					\
			   const typename Element<S,T >::series_set_elt_t& s) \
  {									\
    assertion(s.supp().size() == 1);					\
    return op_add_letter_transition(a_set, v, from, to, *s.supp().begin()); \
  }

#define ADAPT_WORD_OF_TO_LETTERS_LABEL(T...)			\
  typename Element<AutomataBase<S>, T >::monoid_elt_t		\
  op_word_of(const AutomataBase<S>& a_set,			\
	     const T& v,					\
	     htransition_t e)					\
  {								\
    typedef T value_t;						\
    typedef typename S::series_set_t series_set_t;		\
    typedef typename series_set_t::monoid_t monoid_t;		\
    typedef typename Element<S, value_t>::monoid_elt_value_t	\
      word_value_t;						\
    Element<monoid_t, word_value_t>				\
      w(a_set.series().monoid());				\
    w += op_letter_of(a_set, v, e);				\
    return w;							\
  }

#define ADAPT_SERIE_OF_TO_LETTERS_LABEL(T...)				\
  typename Element<AutomataBase<S>, T >::series_set_elt_t		\
  op_series_of(const AutomataBase<S>& a_set,				\
	       const T& v,						\
	       htransition_t e)						\
  {									\
    typedef T value_t;							\
									\
    typedef typename S::series_set_t series_set_t;			\
    typedef typename series_set_t::monoid_t monoid_t;			\
    typedef typename Element<S, value_t>::monoid_elt_value_t		\
      word_value_t;							\
    typedef typename Element<S, value_t>::semiring_elt_value_t		\
      semiring_elt_value_t;						\
    typedef typename Element<S, value_t>::series_set_elt_value_t	\
      series_set_elt_value_t;						\
    Element<monoid_t, word_value_t> w(a_set.series().monoid());		\
    w = op_letter_of(a_set, v, e);					\
    Element<series_set_t, series_set_elt_value_t> s(a_set.series());	\
    s.assoc(w, algebra::identity_as<semiring_elt_value_t>		\
	    ::of(a_set.series().semiring()));				\
    return s;								\
  }

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/automata/implementation/kind_adapter.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_KIND_ADAPTER_HH
