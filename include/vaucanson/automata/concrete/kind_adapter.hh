<<<<<<< .working
<<<<<<< .working
// kind_adapter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH
# define VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH

# include <vaucanson/automata/concept/automata_kind.hh>

namespace vcsn {

  //! we define a series of macros to make the data structure for
  //! automaton simpler.

#define ADAPT_ADD_LETTER_EDGE_TO_SERIES_LABEL(T...)			\
  inline \
  hedge_t								\
  op_add_letter_edge(const AutomataBase<S>& s,				\
		     T& v,						\
		     hstate_t from,					\
		     hstate_t to,					\
		     const typename Element<S, T >::letter_t & l)	\
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
  inline \
  typename Element<AutomataBase<S>, T >::letter_t		\
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
  inline \
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

#define ADAPT_ADD_SERIE_EDGE_TO_LETTERS_LABEL(T...)			\
  inline								\
  hedge_t 								\
  op_add_serie_edge(const AutomataBase<S>& a_set,			\
		    T& v,						\
		    hstate_t from, 					\
		    hstate_t to, 					\
		    const typename Element<S,T>::serie_t& s)		\
  {									\
    assertion(s.supp().size() == 1);					\
    return op_add_letter_edge(a_set, v, from, to, *s.supp().begin());	\
  }

#define ADAPT_WORD_OF_TO_LETTERS_LABEL(T...)			\
  inline							\
  typename Element<AutomataBase<S>, T>::monoid_elt_t		\
  op_word_of(const AutomataBase<S>& a_set,			\
	     const T& v,					\
             hedge_t e)						\
  {								\
    typedef T value_t;						\
    typedef typename S::series_t series_t;			\
    typedef typename series_t::monoid_t monoid_t;		\
    typedef typename Element<S, value_t>::monoid_elt_value_t	\
    word_value_t;						\
    Element<monoid_t, word_value_t>				\
         w(a_set.series().monoid());				\
    w += op_letter_of(a_set, v, e);				\
    return w;							\
  }		

#define ADAPT_SERIE_OF_TO_LETTERS_LABEL(T...)			\
  inline							\
  typename Element<AutomataBase<S>, T>::serie_t			\
  op_serie_of(const AutomataBase<S>& a_set,			\
	      const T& v,					\
	      hedge_t e)					\
  {								\
    typedef T value_t;						\
								\
    typedef typename S::series_t series_t;			\
    typedef typename series_t::monoid_t monoid_t;		\
    typedef typename Element<S, value_t>::monoid_elt_value_t	\
    word_value_t;						\
    typedef typename Element<S, value_t>::weight_value_t	\
        weight_value_t;						\
    typedef typename Element<S, value_t>::serie_value_t		\
    serie_value_t;						\
    Element<monoid_t, word_value_t> w(a_set.series().monoid());	\
    w = op_letter_of(a_set, v, e);				\
    Element<series_t, serie_value_t> s(a_set.series());		\
    s.assoc(w, algebra::identity_as<weight_value_t>		\
	    ::of(a_set.series().weights()));			\
    return s;							\
  }		

} // vcsn

# include <vaucanson/automata/concrete/kind_adapter.hxx>

#endif // VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH
=======
// kind_adapter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH
# define VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH

# include <vaucanson/automata/concept/automata_kind.hh>

namespace vcsn {

  //! we define a series of macros to make the data structure for
  //! automaton simpler.

#define ADAPT_ADD_LETTER_EDGE_TO_SERIES_LABEL(T...)			\
  inline \
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
  inline \
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
  inline \
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

#define ADAPT_ADD_SERIE_EDGE_TO_LETTERS_LABEL(T...)			\
  inline								\
  hedge_t 								\
  op_add_serie_edge(const AutomataBase<S>& a_set,			\
		    T& v,						\
		    hstate_t from, 					\
		    hstate_t to, 					\
		    const typename Element<S,T>::serie_t& s)		\
  {									\
    assertion(s.supp().size() == 1);					\
    return op_add_letter_edge(a_set, v, from, to, *s.supp().begin());	\
  }

#define ADAPT_WORD_OF_TO_LETTERS_LABEL(T...)			\
  inline							\
  typename Element<AutomataBase<S>, T>::monoid_elt_t		\
  op_word_of(const AutomataBase<S>& a_set,			\
	     const T& v,					\
             hedge_t e)						\
  {								\
    typedef T value_t;						\
    typedef typename S::series_t series_t;			\
    typedef typename series_t::monoid_t monoid_t;		\
    typedef typename Element<S, value_t>::monoid_elt_value_t	\
    word_value_t;						\
    Element<monoid_t, word_value_t>				\
         w(a_set.series().monoid());				\
    w += op_letter_of(a_set, v, e);				\
    return w;							\
  }		

#define ADAPT_SERIE_OF_TO_LETTERS_LABEL(T...)			\
  inline							\
  typename Element<AutomataBase<S>, T>::serie_t			\
  op_serie_of(const AutomataBase<S>& a_set,			\
	      const T& v,					\
	      hedge_t e)					\
  {								\
    typedef T value_t;						\
								\
    typedef typename S::series_t series_t;			\
    typedef typename series_t::monoid_t monoid_t;		\
    typedef typename Element<S, value_t>::monoid_elt_value_t	\
    word_value_t;						\
    typedef typename Element<S, value_t>::weight_value_t	\
        weight_value_t;						\
    typedef typename Element<S, value_t>::serie_value_t		\
    serie_value_t;						\
    Element<monoid_t, word_value_t> w(a_set.series().monoid());	\
    w = op_letter_of(a_set, v, e);				\
    Element<series_t, serie_value_t> s(a_set.series());		\
    s.assoc(w, algebra::identity_as<weight_value_t>		\
	    ::of(a_set.series().weights()));			\
    return s;							\
  }		

} // vcsn

# include <vaucanson/automata/concrete/kind_adapter.hxx>

#endif // VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH
>>>>>>> .merge-right.r335
=======
// kind_adapter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH
# define VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH

# include <vaucanson/automata/concept/automata_kind.hh>

namespace vcsn {

  //! we define a series of macros to make the data structure for
  //! automaton simpler.

#define ADAPT_ADD_LETTER_EDGE_TO_SERIES_LABEL(T...)			\
  inline \
  hedge_t								\
  op_add_letter_edge(const AutomataBase<S>& s,				\
		     T& v,						\
		     hstate_t from,					\
		     hstate_t to,					\
		     const typename Element<S, T >::letter_t & l)	\
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
  inline \
  typename Element<AutomataBase<S>, T >::letter_t		\
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
  inline \
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

#define ADAPT_ADD_SERIE_EDGE_TO_LETTERS_LABEL(T...)			\
  inline								\
  hedge_t 								\
  op_add_serie_edge(const AutomataBase<S>& a_set,			\
		    T& v,						\
		    hstate_t from, 					\
		    hstate_t to, 					\
		    const typename Element<S,T>::serie_t& s)		\
  {									\
    assertion(s.supp().size() == 1);					\
    return op_add_letter_edge(a_set, v, from, to, *s.supp().begin());	\
  }

#define ADAPT_WORD_OF_TO_LETTERS_LABEL(T...)			\
  inline							\
  typename Element<AutomataBase<S>, T>::monoid_elt_t		\
  op_word_of(const AutomataBase<S>& a_set,			\
	     const T& v,					\
             hedge_t e)						\
  {								\
    typedef T value_t;						\
    typedef typename S::series_t series_t;			\
    typedef typename series_t::monoid_t monoid_t;		\
    typedef typename Element<S, value_t>::monoid_elt_value_t	\
    word_value_t;						\
    Element<monoid_t, word_value_t>				\
         w(a_set.series().monoid());				\
    w += op_letter_of(a_set, v, e);				\
    return w;							\
  }		

#define ADAPT_SERIE_OF_TO_LETTERS_LABEL(T...)			\
  inline							\
  typename Element<AutomataBase<S>, T>::serie_t			\
  op_serie_of(const AutomataBase<S>& a_set,			\
	      const T& v,					\
	      hedge_t e)					\
  {								\
    typedef T value_t;						\
								\
    typedef typename S::series_t series_t;			\
    typedef typename series_t::monoid_t monoid_t;		\
    typedef typename Element<S, value_t>::monoid_elt_value_t	\
    word_value_t;						\
    typedef typename Element<S, value_t>::weight_value_t	\
        weight_value_t;						\
    typedef typename Element<S, value_t>::serie_value_t		\
    serie_value_t;						\
    Element<monoid_t, word_value_t> w(a_set.series().monoid());	\
    w = op_letter_of(a_set, v, e);				\
    Element<series_t, serie_value_t> s(a_set.series());		\
    s.assoc(w, algebra::identity_as<weight_value_t>		\
	    ::of(a_set.series().weights()));			\
    return s;							\
  }		

} // vcsn

# include <vaucanson/automata/concrete/kind_adapter.hxx>

#endif // VCSN_AUTOMATA_CONCRETE_KIND_ADAPTER_HH
>>>>>>> .merge-right.r339
