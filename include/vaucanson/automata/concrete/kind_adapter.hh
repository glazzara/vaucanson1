// kind_adapter.hh
// 
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH
# define VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH

# include <vaucanson/automata/concept/automata_kind.hh>

namespace vcsn {

  //! we define a series of macros to make the data structure for
  //! automaton easier.

#define ADAPT_ADD_LETTER_EDGE_TO_SERIES_LABEL(T...)			\
  hedge_t								\
  op_add_letter_edge(const AutomataBase<S>& s,				\
		     T& v,						\
		     hstate_t from,					\
		     hstate_t to,					\
		     const typename Element<S, T>::letter_t & l)	\
  {									\
    typedef typename S::series_t series_t;				\
    typedef typename series_t::monoid_t monoid_t;			\
    typedef typename Element<S, T>::monoid_elt_value_t			\
    word_value_t;							\
    typedef typename Element<S, T>::serie_value_t			\
    serie_value_t;							\
    Element<monoid_t, word_value_t> w(s.series().monoid());		\
    Element<series_t, serie_value_t> s1(s.series());			\
    w = l;								\
    s1 = w;								\
    return op_add_edge(s, v, from, to, s1.value());			\
  }

#define ADAPT_LETTER_OF_TO_SERIES_LABEL(T...)				\
  typename Element<AutomataBase<S>, T>::letter_t		\
  op_letter_of(const AutomataBase<S>& s,				\
	       const T& v,					\
               hedge_t e)						\
  {									\
    typedef typename S::series_t series_t;				\
    typedef typename series_t::monoid_t monoid_t;			\
    typedef typename Element<S, T>::monoid_elt_value_t 	\
    word_value_t;							\
    typedef typename Element<S, T>::serie_value_t 		\
    serie_value_t;							\
									\
    Element<series_t, serie_value_t> sl = op_serie_of(s, v, e);		\
    precondition(sl.supp().size() == 1);				\
    Element<monoid_t, word_value_t> w = sl.choose_from_supp();		\
    precondition(w.length() == 1);					\
    return *w.begin();							\
  }

#define ADAPT_WORD_OF_TO_SERIES_LABEL(T...)				\
  typename Element<AutomataBase<S>, T>::monoid_elt_t		\
  op_word_of(const AutomataBase<S>& s,					\
	     const T& v,					\
             hedge_t e)							\
  {									\
    typedef typename S::series_t series_t;				\
    typedef typename series_t::monoid_t monoid_t;			\
    typedef typename Element<S, T>::monoid_elt_value_t	\
    word_value_t;							\
    typedef typename Element<S, T>::serie_value_t		\
    serie_value_t;							\
									\
    Element<series_t, serie_value_t> sl = op_serie_of(s, v, e);		\
    precondition(sl.supp().size() == 1);				\
    Element<monoid_t, word_value_t> w = sl.choose_from_supp();		\
    return w;								\
  }

} // vcsn

# include <vaucanson/automata/concrete/kind_adapter.hxx>

#endif // VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH
