// automaton_view.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCRETE_AUTOMATON_VIEW_HXX
# define VCSN_AUTOMATA_CONCRETE_AUTOMATON_VIEW_HXX

# include <vaucanson/misc/contract.hh>
# include <vaucanson/automata/concrete/automaton_view.hh>

#define AutoType(Type) \
  typename Element<S, IdentityView<T> >::Type

namespace vcsn {

  template <class T>
  IdentityView<T>::IdentityView()
  {}

  template <class T>
  IdentityView<T>::IdentityView(T& d):
    object_(&d),
    const_object_(0)
  {}

  template <class T>
  IdentityView<T>::IdentityView(const T& d):
    object_(0),
    const_object_(&d)
  {}
  
  template <class T>
  IdentityView<T>::IdentityView(const IdentityView& d):
    object_(0)
  {
    assertion(d.object_ != 0 || d.const_object_ != 0);
    const_object_ = d.const_object_ == 0 ? d.object_ : d.const_object_;
  }
    
  template <class T>
  const T& 
  IdentityView<T>::object() const
  {
    assertion(object_ != 0 || const_object_ != 0);
    return const_object_ == 0 ? *object_ : *const_object_;
  }

  template <class T>
  T& 
  IdentityView<T>::object()
  {
    assertion(object_ != 0);
    assertion(const_object_ == 0);
    return *object_;
  }
  
  template <class T>
  IdentityView<T>::operator T&()
  {
    assertion(object_ != 0);
    assertion(const_object_ == 0);
    return *object_;
  }
  
  template <class T>
  IdentityView<T>::operator const T&() const
  {
    assertion(object_ != 0 || const_object_ != 0);
    return const_object_ == 0 ? *object_ : *const_object_;
  }
    
  template <class S, class T>
  const typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>& s, const IdentityView<T>& v)
  {
    return op_get_tag(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>& s, IdentityView<T>& v)
  {
    return op_get_tag(s, v.object());
  }

  template <class S, class T>
  bool
  op_exists(const AutomataBase<S>& s, const IdentityView<T>& v)
  {
    return op_exists(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::states_t
  op_states(const AutomataBase<S>& s, const IdentityView<T>& v)
  {
    return op_states(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::edges_t
  op_edges(const AutomataBase<S>& s, const IdentityView<T>& v)
  {
    return op_edges(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::initial_support_t
  op_initial(const AutomataBase<S>& s, const IdentityView<T>& v)
  {
    return op_initial(s, v.object());
  }

  template <class S, class T>
  typename automaton_traits<T>::final_support_t
  op_final(const AutomataBase<S>& s, const IdentityView<T>& v)
  {
    return op_final(s, v.object());
  }

  template <class S, class T>
  void
  op_set_initial(const AutomataBase<S>& ss, IdentityView<T>& v, 
		 hstate_t state,
		 const AutoType(series_elt_t)& s)
  {
    return op_set_initial(ss, v.object(), state, s);
  }

  template <class S, class T>
  AutoType(series_elt_t)
  op_get_initial(const AutomataBase<S>& s, 
		 const IdentityView<T>& v, 
		 hstate_t state)
  {
    return op_get_initial(s, v.object(), state);
  }
  
  template <class S, class T>
  void
  op_set_final(const AutomataBase<S>& ss, IdentityView<T>& v, 
	       hstate_t state,
	       const typename Element<S, T>::series_elt_t& s)
  {
    op_set_final(ss, v.object, state, s);
  }

  template <class S, class T>
  typename Element<S, T>::series_elt_t
  op_get_final(const AutomataBase<S>& s, 
	       const IdentityView<T>& v,  
	       hstate_t state)
  {
    return op_get_final(s, v.object, state);
  }
  
  template <class S, class T>
  void
  op_clear_initial(const AutomataBase<S>& s, IdentityView<T>& v)
  {
    op_clear_initial(s, v.object);
  }

  template <class S, class T>
  void
  op_clear_final(const AutomataBase<S>& s, IdentityView<T>& v)
  {
    op_clear_final(s, v.object());
  }
  
  template <class S, class T>
  hstate_t
  op_add_state(const AutomataBase<S>& s, IdentityView<T>& v)
  {
    return op_add_state(s, v.object());
  }

  template <class S, class T>
  hstate_t
  op_choose_state(const AutomataBase<S>& s, IdentityView<T>& v)
  {
    return op_choose_state(s, v.object());
  }

  template <class S, class T>
  hedge_t 
  op_add_edge(const AutomataBase<S>& s, IdentityView<T>& v,
	      hstate_t from, 
	      hstate_t to, 
	      const typename Element<S, T>::label_t& label)
  {
    return op_add_edge(s, v.object(), from, to, label);
  }

  template <class S, class T>
  hedge_t 
  op_add_serie_edge(const AutomataBase<S>& s, 
		    IdentityView<T>& v,
		    hstate_t from, 
		    hstate_t to, 
		    const typename Element<S, T>::series_elt_t& se)
  {
    return op_add_serie_edge(s, v.object(), from, to, se);
  }

  template <class S, class T>
  hedge_t 
  op_add_spontaneous(const AutomataBase<S>& s, IdentityView<T>& v,
		     hstate_t from, 
		     hstate_t to)
  {
    return op_add_spontaneous(s, v.object(), from, to);
  }
  
  template <class S, class T>
  hedge_t 
  op_add_letter_edge(const AutomataBase<S>& s, IdentityView<T>& v,
		     hstate_t from, 
		     hstate_t to, 
		     const typename Element<S, T>::letter_t& e)
  {
    return op_add_letter_edge(s, v.object(), from, to, e);
  }
  
  template <class S, class T>
  void
  op_update(const AutomataBase<S>& s, IdentityView<T>& v,
	    hedge_t e, 
	    const AutoType(label_t)& l)
  {
    op_update(s, v.object(), e, l);
  }
  
  template <class S, class T>
  void
  op_del_state(const AutomataBase<S>& s, IdentityView<T>& v,
	       hstate_t st)
  {
    op_del_state(s, v.object(), st);
  }

  template <class S, class T>
  void
  op_del_edge(const AutomataBase<S>& s, IdentityView<T>& v,
	      hedge_t e)
  {
    op_del_edge(s, v.object(), e);
  }
	 
  template <class S, class T>
  void
  op_safe_del_state(const AutomataBase<S>& s, IdentityView<T>& v,
		    hstate_t st)
  {
    op_safe_del_state(s, v.object(), st);
  }

  template <class S, class T>
  bool
  op_has_state(const AutomataBase<S>& s, 
	       const IdentityView<T>& v,
	       hstate_t st)
  {
    return op_has_state(s, v.object(), st);
  }

  template <class S, class T>
  bool
  op_has_edge(const AutomataBase<S>& s, 
	      const IdentityView<T>& v,
	      hedge_t e)
  {
    return op_has_edge(s, v.object(), e);
  }

  template <class S, class T>
  hstate_t
  op_origin_of(const AutomataBase<S>& s, 
	       const IdentityView<T>& v,
	       hedge_t e)
  {
    return op_origin_of(s, v.object(), e);
  }

  template <class S, class T>
  hstate_t
  op_aim_of(const AutomataBase<S>& s, 
	    const IdentityView<T>& v,
	    hedge_t e)
  {
    return op_aim_of(s, v.object(), e);
  }
  
  template <class S, class T>
  typename Element<S, T>::label_t
  op_label_of(const AutomataBase<S>& s, 
	      const IdentityView<T>& v,
	      hedge_t e)
  {
    return op_label_of(s, v.object(), e);
  }
   
  template <class S, class T>
  const typename Element<S, T>::series_elt_t
  op_serie_of(const AutomataBase<S>& s,  
	      const IdentityView<T>& v,
	      hedge_t e)
  {
    return op_serie_of(s, v.object(), e);
  }
   
  template <class S, class T>
  typename Element<S, T>::serie_value_t
  op_serie_value_of(const AutomataBase<S>& s, 
		    const IdentityView<T>& v,
		    hedge_t e)
  {
    return op_serie_value_of(s, v.object(), e);
  }
  
  template <class S, class T>
  typename Element<S, T>::monoid_elt_t
  op_word_of(const AutomataBase<S>& s, 
	     const IdentityView<T>& v,
	     hedge_t e)
  {
    return op_word_of(s, v.object(), e);
  }

  template <class S, class T>
  typename Element<S, T>::monoid_elt_value_t
  op_word_value_of(const AutomataBase<S>& s, 
		   const IdentityView<T>& v,
		   hedge_t e)
  {
    return op_word_value_of(s, v.object(), e);
  }

  template <class S, class T>
  typename Element<S, T>::letter_t
  op_letter_of(const AutomataBase<S>& s, 
	       const IdentityView<T>& v,
	       hedge_t e)
  {
    return op_letter_of(s, v.object(), e);
  }
  
  template <class S, class T>
  bool
  op_is_spontaneous(const AutomataBase<S>& s, 
		    const IdentityView<T>& v,
		    hedge_t e)
  {
    return op_is_spontaneous(s, v.object(), e);
  }

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = output

  /*! store the output edges of the state 'from' using 'res'. */
  template <class S, class T, 
	    typename OutputIterator>					
  void op_delta(const AutomataBase<S>& s, 
		const IdentityView<T>& v,
		OutputIterator res, 
		hstate_t from, 
		delta_kind::edges k)
  {
    op_delta(s, v.object(), res, from, k);
  }

  /*! store the output edges of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  void op_delta(const AutomataBase<S>& s, 
		const IdentityView<T>& v,
		OutputIterator res, 
		hstate_t from, 
		const L& query,
		delta_kind::edges k)
  {
    op_delta(s, v.object(), res, from, query, k);
  }
    
  /*! store the output edges of the state 'from' where
    the label matches the letter. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  void op_letter_delta(const AutomataBase<S>& s, 
		       const IdentityView<T>& v,
		       OutputIterator res, 
		       hstate_t from, 
		       const L& letter,
		       delta_kind::edges k)
  {
    op_letter_delta(s, v.object(), res, from, letter, k);
  }

  /*! store the output spontaneous transitions. */
  template <class S, class T,
	    typename OutputIterator>
  void op_spontaneous_delta(const AutomataBase<S>& s, 
			    const IdentityView<T>& v,
			    OutputIterator res, 
			    hstate_t from, 
			    delta_kind::edges k)
  {
    op_spontaneous_delta(s, v.object(), res, from, k);
  }

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	  = output

  /*! store the output edges of the state 'from' in the container
    'res' */
  template <class S, class T,
	    typename Container>
  void op_deltac(const AutomataBase<S>& s, 
		 const IdentityView<T>& v,
		 Container& res, hstate_t from, delta_kind::edges k)
  {
    op_deltac(s, v.object(), res, from, k);
  }

  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  void op_deltac(const AutomataBase<S>& s, 
		 const IdentityView<T>& v,
		 Container& res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::edges k)
  {
    op_deltac(s, v.object(), res, from, query, k);
  }

  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  void op_letter_deltac(const AutomataBase<S>& s, 
			const IdentityView<T>& v,
			Container& res, 
			hstate_t from, 
			const L& letter,
			delta_kind::edges k)
  {
    op_letter_deltac(s, v.object(), res, from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template <class S, class T, class Container>
  void op_spontaneous_deltac(const AutomataBase<S>& s, 
			     const IdentityView<T>& v,
			     Container& res, 
			     hstate_t from, 
			     delta_kind::edges k)
  {
    op_spontaneous_deltac(s, v.object(), res, from, k);
  }

  // output_return_type = OutputIterator
  // output_type        = hstate_t
  // direction	  = output

  /*! store the output states of the state 'from' using 'res'. */
  template<class S, class T, typename OutputIterator> 
  void op_delta(const AutomataBase<S>& s, 
		const IdentityView<T>& v,
		OutputIterator res,  
		hstate_t from, 
		delta_kind::states k)
  {
    op_delta(s, v.object(), res, from, k);
  }

  /*! store the output states of the state 'from' where
    query(label(e)) = true using 'res'. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_delta(const AutomataBase<S>& s, 
		const IdentityView<T>& v,
		OutputIterator res, 
		hstate_t from, 
		const L& query,
		delta_kind::states k)
  {
    op_delta(s, v.object(), res, from, query, k);
  }

  /*! store the output states of the state 'from' where
    the label matches the letter. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_letter_delta(const AutomataBase<S>& s, 
		       const IdentityView<T>& v,
		       OutputIterator res, 
		       hstate_t from, 
		       const L& letter,
		       delta_kind::states k)
  {
    op_letter_delta(s, v.object(), res, from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename OutputIterator>	
  void op_spontaneous_delta(const AutomataBase<S>& s, 
			    const IdentityView<T>& v,
			    OutputIterator res, 
			    hstate_t from, 
			    delta_kind::states k)
  {
    op_spontaneous_delta(s, v.object(), res, from, k);
  }

  // output_return_type = Container
  // output_type        = hstate_t
  // direction	  = output

  /*! store the output states of the state 'from' in the container
    'res' */
  template<class S, class T, typename Container>
  void op_deltac(const AutomataBase<S>& s, 
		 const IdentityView<T>& v,
		 Container& res, hstate_t from, delta_kind::states k)
  {
    op_delta(s, v.object(), res, from, k);
  }

  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_deltac(const AutomataBase<S>& s, 
		 const IdentityView<T>& v,
		 Container& res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::states k)
  {
    op_deltac(s, v.object(), res, from, k);
  }

  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_letter_deltac(const AutomataBase<S>& s, 
			const IdentityView<T>& v,
			Container& res, 
			hstate_t from, 
			const L& letter,
			delta_kind::states k)
  {
    op_letter_deltac(s, v.object(), res, from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename Container>
  void op_spontaneous_deltac(const AutomataBase<S>& s, 
			     const IdentityView<T>& v, 
			     Container& res, 
			     hstate_t from, 
			     delta_kind::states k)
  {
    op_spontaneous_deltac(s, v.object(), res, from, k);
  }

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = input

  /*! store the output edges of the state 'from' using 'res'. */
  template<class S, class T, typename OutputIterator>		
  void op_rdelta(const AutomataBase<S>& s, const IdentityView<T>& v, 
		 OutputIterator res, 
		 hstate_t from, 
		 delta_kind::edges k)
  {
    op_rdelta(s, v.object(), res, from, k);
  }

  /*! store the output edges of the state 'from' where
    query(label(e)) = true using 'res'. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_rdelta(const AutomataBase<S>& s, const IdentityView<T>& v, 
		 OutputIterator res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::edges k)
  {
    op_rdelta(s, v.object(), res, from, query, k);
  }

  /*! store the output edges of the state 'from' where
    the label matches the letter. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_letter_rdelta(const AutomataBase<S>& s, const IdentityView<T>& v, 
			OutputIterator res, 
			hstate_t from, 
			const L& letter,
			delta_kind::edges k)
  {
    op_letter_rdelta(s, v.object(), res, from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename OutputIterator>
  void op_spontaneous_rdelta(const AutomataBase<S>& s, 
			     const IdentityView<T>& v, 
			     OutputIterator res, 
			     hstate_t from, 
			     delta_kind::edges k)
  {
    op_spontaneous_rdelta(s, v.object(), res, from, k);
  }

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	  = input

  /*! store the output edges of the state 'from' in the container
    'res' */
  template<class S, class T, typename Container>
  void op_rdeltac(const AutomataBase<S>& s, const IdentityView<T>& v, 
		  Container& res, hstate_t from, delta_kind::edges k)
  {
    op_rdeltac(s, v.object(), res, from, k);
  }

  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_rdeltac(const AutomataBase<S>& s, const IdentityView<T>& v, 
		  Container& res, 
		  hstate_t from, 
		  const L& query,
		  delta_kind::edges k)
  {
    op_rdeltac(s, v.object(), res, from, query, k);
  }

  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_letter_rdeltac(const AutomataBase<S>& s, const IdentityView<T>& v, 
			 Container& res, 
			 hstate_t from, 
			 const L& letter,
			 delta_kind::edges k)
  {
    op_letter_rdeltac(s, v.object(), res, from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename Container>
  void op_spontaneous_rdeltac(const AutomataBase<S>& s, 
			      const IdentityView<T>& v, 
			      Container& res, 
			      hstate_t from, 
			      delta_kind::edges k)
  {
    op_spontaneous_rdeltac(s, v.object(), res, from, k);
  }

  // output_return_type = OutputIterator
  // output_type        = hstate_t
  // direction	  = input

  /*! store the output states of the state 'from' using 'res'. */
  template<class S, class T, typename OutputIterator>		
  void op_rdelta(const AutomataBase<S>& s, const IdentityView<T>& v, 
		 OutputIterator res, 
		 hstate_t from, 
		 delta_kind::states k)
  {
    op_rdelta(s, v.object(), res, from, k);
  }

  /*! store the output states of the state 'from' where
    query(label(e)) = true using 'res'. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_rdelta(const AutomataBase<S>& s, const IdentityView<T>& v, 
		 OutputIterator res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::states k)
  {
    op_rdelta(s, v.object(), res, from, query, k);
  }

  /*! store the output states of the state 'from' where
    the label matches the letter. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_letter_rdelta(const AutomataBase<S>& s, const IdentityView<T>& v, 
			OutputIterator res, 
			hstate_t from, 
			const L& letter,
			delta_kind::states k)
  {
    op_letter_rdelta(s, v.object(), res, from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename OutputIterator>
  void op_spontaneous_rdelta(const AutomataBase<S>& s, 
			     const IdentityView<T>& v, 
			     OutputIterator res, 
			     hstate_t from, 
			     delta_kind::states k)
  {
    op_spontaneous_rdelta(s, v.object(), res, from, k);
  }

  // output_return_type = Container
  // output_type        = hstate_t
  // direction	  = input

  /*! store the output states of the state 'from' in the container
    'res' */
  template<class S, class T, typename Container>
  void op_rdeltac(const AutomataBase<S>& s, const IdentityView<T>& v, 
		  Container& res, hstate_t from, delta_kind::states k)
  {
    op_rdeltac(s, v.object(), res, from, k);
  }

  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_rdeltac(const AutomataBase<S>& s, const IdentityView<T>& v, 
		  Container& res, 
		  hstate_t from, 
		  const L& query,
		  delta_kind::states k)
  {
    op_rdeltac(s, v.object(), res, from, query, k);
  }

  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_letter_rdeltac(const AutomataBase<S>& s, const IdentityView<T>& v, 
			 Container& res, 
			 hstate_t from, 
			 const L& letter,
			 delta_kind::states k)
  {
    op_letter_rdeltac(s, v.object(), res, from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename Container>
  void op_spontaneous_rdeltac(const AutomataBase<S>& s, 
			      const IdentityView<T>& v, 
			      Container& res, 
			      hstate_t from, 
			      delta_kind::states k)
  {
    op_spontaneous_rldeltac(s, v.object(), res, from, k);
  }

} // vcsn

# undef AutoType

#endif // VCSN_AUTOMATA_CONCRETE_AUTOMATON_VIEW_HXX
