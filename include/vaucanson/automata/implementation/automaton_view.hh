// automaton_view.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCRETE_AUTOMATON_VIEW_HH
# define VCSN_AUTOMATA_CONCRETE_AUTOMATON_VIEW_HH

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


#define AutoType(Type) \
  typename Element<S, IdentityView<T> >::Type

  template <class S, class T>
  const typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>&, IdentityView<T>&);

  template <class S, class T>
  bool
  op_exists(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::states_t
  op_states(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::edges_t
  op_edges(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::initial_support_t
  op_initial(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  typename automaton_traits<T>::final_support_t
  op_final(const AutomataBase<S>&, const IdentityView<T>&);

  template <class S, class T>
  void
  op_set_initial(const AutomataBase<S>&, IdentityView<T>&, 
		 hstate_t state,
		 const AutoType(series_set_elt_t)& s);

  template <class S, class T>
  AutoType(series_set_elt_t)
  op_get_initial(const AutomataBase<S>&, 
		 const IdentityView<T>&, 
		 hstate_t state);
  
  template <class S, class T>
  void
  op_set_final(const AutomataBase<S>&, IdentityView<T>&, 
	       hstate_t state,
	       const typename Element<S, T>::series_set_elt_t& s);

  template <class S, class T>
  typename Element<S, T>::series_set_elt_t
  op_get_final(const AutomataBase<S>&, 
	       const IdentityView<T>&, 
	       hstate_t state);
  
  template <class S, class T>
  void
  op_clear_initial(const AutomataBase<S>&, IdentityView<T>&);

  template <class S, class T>
  void
  op_clear_final(const AutomataBase<S>&, IdentityView<T>&);
  
  template <class S, class T>
  hstate_t
  op_add_state(const AutomataBase<S>&, IdentityView<T>&);

  template <class S, class T>
  hstate_t
  op_choose_state(const AutomataBase<S>&, IdentityView<T>&);

  template <class S, class T>
  hedge_t 
  op_add_edge(const AutomataBase<S>&, IdentityView<T>&,
	      hstate_t from, 
	      hstate_t to, 
	      const typename Element<S, T>::label_t& label);

  template <class S, class T>
  hedge_t 
  op_add_series_edge(const AutomataBase<S>&, IdentityView<T>&,
		    hstate_t from, 
		    hstate_t to, 
		    const typename Element<S, T>::series_set_elt_t&);

  template <class S, class T>
  hedge_t 
  op_add_spontaneous(const AutomataBase<S>&, IdentityView<T>&,
		     hstate_t from, 
		     hstate_t to);
  
  template <class S, class T>
  hedge_t 
  op_add_letter_edge(const AutomataBase<S>&, IdentityView<T>&,
		     hstate_t from, 
		     hstate_t to, 
		     const typename Element<S, T>::letter_t&);    
  
  template <class S, class T>
  void
  op_update(const AutomataBase<S>&, IdentityView<T>&,
	    hedge_t, 
	    const AutoType(label_t)& l);
  
  template <class S, class T>
  void
  op_del_state(const AutomataBase<S>&, IdentityView<T>&,
	       hstate_t);

  template <class S, class T>
  void
  op_del_edge(const AutomataBase<S>&, IdentityView<T>&,
	      hedge_t);
	 
  template <class S, class T>
  void
  op_safe_del_state(const AutomataBase<S>&, IdentityView<T>&,
		    hstate_t);

  template <class S, class T>
  bool
  op_has_state(const AutomataBase<S>&, const IdentityView<T>&,
	       hstate_t);

  template <class S, class T>
  bool
  op_has_edge(const AutomataBase<S>&, const IdentityView<T>&,
	      hedge_t);

  template <class S, class T>
  hstate_t
  op_origin_of(const AutomataBase<S>&, const IdentityView<T>&,
	       hedge_t);

  template <class S, class T>
  hstate_t
  op_aim_of(const AutomataBase<S>&, const IdentityView<T>&,
	    hedge_t);
  
  template <class S, class T>
  typename Element<S, T>::label_t
  op_label_of(const AutomataBase<S>&, const IdentityView<T>&,
	      hedge_t);
   
  template <class S, class T>
  const typename Element<S, T>::series_set_elt_t
  op_series_of(const AutomataBase<S>&, const IdentityView<T>&,
	      hedge_t);
   
  template <class S, class T>
  typename Element<S, T>::series_set_elt_value_t
  op_series_value_of(const AutomataBase<S>&, const IdentityView<T>&,
		    hedge_t);
  

  template <class S, class T>
  typename Element<S, T>::monoid_elt_t
  op_word_of(const AutomataBase<S>&, const IdentityView<T>&,
	     hedge_t);

  template <class S, class T>
  typename Element<S, T>::monoid_elt_value_t
  op_word_value_of(const AutomataBase<S>&, const IdentityView<T>&,
		   hedge_t);

  template <class S, class T>
  typename Element<S, T>::letter_t
  op_letter_of(const AutomataBase<S>&, const IdentityView<T>&,
	       hedge_t);
  
  template <class S, class T>
  bool
  op_is_spontaneous(const AutomataBase<S>&, const IdentityView<T>&,
		    hedge_t);

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction		= output

  /** store the output edges of the state 'from' using 'res'. */
  template <class S, class T, 
	    typename OutputIterator>					
  void op_delta(const AutomataBase<S>&, const IdentityView<T>&,
		OutputIterator res, 
		hstate_t from, 
		delta_kind::edges k);

  /** store the output edges of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  void op_delta(const AutomataBase<S>&, const IdentityView<T>&,
		OutputIterator res, 
		hstate_t from, 
		const L& query,
		delta_kind::edges k);
    
  /** store the output edges of the state 'from' where
    the label matches the letter. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  void op_letter_delta(const AutomataBase<S>&, const IdentityView<T>&,
		       OutputIterator res, 
		       hstate_t from, 
		       const L& letter,
		       delta_kind::edges k);

  /** store the output spontaneous transitions. */
  template <class S, class T,
	    typename OutputIterator>
  void op_spontaneous_delta(const AutomataBase<S>&, const IdentityView<T>&,
			    OutputIterator res, 
			    hstate_t from, 
			    delta_kind::edges k);

  // output_return_type = Container
  // output_type        = hedge_t
  // direction		= output

  /** store the output edges of the state 'from' in the container
    'res' */
  template <class S, class T,
	    typename Container>
  void op_deltac(const AutomataBase<S>&, const IdentityView<T>&,
		 Container& res, hstate_t from, delta_kind::edges k);

  /** store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  void op_deltac(const AutomataBase<S>&, const IdentityView<T>&,
		 Container& res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::edges k);

  /** store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  void op_letter_deltac(const AutomataBase<S>&, const IdentityView<T>&,
			Container& res, 
			hstate_t from, 
			const L& letter,
			delta_kind::edges k);

  /** store the output op_spontaneous transitions. */
  template <class S, class T, class Container>
  void op_spontaneous_deltac(const AutomataBase<S>&, const IdentityView<T>&,
			     Container& res, 
			     hstate_t from, 
			     delta_kind::edges k);

  // output_return_type = OutputIterator
  // output_type        = hstate_t
  // direction	  = output

  /** store the output states of the state 'from' using 'res'. */
  template<class S, class T, typename OutputIterator> 
  void op_delta(const AutomataBase<S>&, const IdentityView<T>&,
		OutputIterator res, 
		hstate_t from, 
		delta_kind::states k);

  /** store the output states of the state 'from' where
    query(label(e)) = true using 'res'. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_delta(const AutomataBase<S>&, const IdentityView<T>&,
		OutputIterator res, 
		hstate_t from, 
		const L& query,
		delta_kind::states k);

  /** store the output states of the state 'from' where
    the label matches the letter. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_letter_delta(const AutomataBase<S>&, const IdentityView<T>&,
		       OutputIterator res, 
		       hstate_t from, 
		       const L& letter,
		       delta_kind::states k);

  /** store the output op_spontaneous transitions. */
  template<class S, class T, typename OutputIterator>	
  void op_spontaneous_delta(const AutomataBase<S>&, const IdentityView<T>&,
			    OutputIterator res, 
			    hstate_t from, 
			    delta_kind::states k);

  // output_return_type = Container
  // output_type        = hstate_t
  // direction	  = output

  /** store the output states of the state 'from' in the container
    'res' */
  template<class S, class T, typename Container>
  void op_deltac(const AutomataBase<S>&, const IdentityView<T>&,
		 Container& res, hstate_t from, delta_kind::states k);

  /** store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_deltac(const AutomataBase<S>&, const IdentityView<T>&,
		 Container& res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::states k);

  /** store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_letter_deltac(const AutomataBase<S>&, const IdentityView<T>&,
			Container& res, 
			hstate_t from, 
			const L& letter,
			delta_kind::states k);

  /** store the output op_spontaneous transitions. */
  template<class S, class T, typename Container>
  void op_spontaneous_deltac(const AutomataBase<S>&, const IdentityView<T>&,
			     Container& res, 
			     hstate_t from, 
			     delta_kind::states k);

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = input

  /** store the output edges of the state 'from' using 'res'. */
  template<class S, class T, typename OutputIterator>		
  void op_rdelta(const AutomataBase<S>&, const IdentityView<T>&,
		 OutputIterator res, 
		 hstate_t from, 
		 delta_kind::edges k);

  /** store the output edges of the state 'from' where
    query(label(e)) = true using 'res'. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_rdelta(const AutomataBase<S>&, const IdentityView<T>&,
		 OutputIterator res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::edges k);

  /** store the output edges of the state 'from' where
    the label matches the letter. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_letter_rdelta(const AutomataBase<S>&, const IdentityView<T>&,
			OutputIterator res, 
			hstate_t from, 
			const L& letter,
			delta_kind::edges k);

  /** store the output op_spontaneous transitions. */
  template<class S, class T, typename OutputIterator>
  void op_spontaneous_rdelta(const AutomataBase<S>&, const IdentityView<T>&,
			     OutputIterator res, 
			     hstate_t from, 
			     delta_kind::edges k);

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	  = input

  /** store the output edges of the state 'from' in the container
    'res' */
  template<class S, class T, typename Container>
  void op_rdeltac(const AutomataBase<S>&, const IdentityView<T>&,
		  Container& res, hstate_t from, delta_kind::edges k);

  /** store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_rdeltac(const AutomataBase<S>&, const IdentityView<T>&,
		  Container& res, 
		  hstate_t from, 
		  const L& query,
		  delta_kind::edges k);

  /** store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_letter_rdeltac(const AutomataBase<S>&, const IdentityView<T>&,
			 Container& res, 
			 hstate_t from, 
			 const L& letter,
			 delta_kind::edges k);

  /** store the output op_spontaneous transitions. */
  template<class S, class T, typename Container>
  void op_spontaneous_rdeltac(const AutomataBase<S>&, const IdentityView<T>&,
			      Container& res, 
			      hstate_t from, 
			      delta_kind::edges k);

  // output_return_type = OutputIterator
  // output_type        = hstate_t
  // direction	  = input

  /** store the output states of the state 'from' using 'res'. */
  template<class S, class T, typename OutputIterator>		
  void op_rdelta(const AutomataBase<S>&, const IdentityView<T>&,
		 OutputIterator res, 
		 hstate_t from, 
		 delta_kind::states k);

  /** store the output states of the state 'from' where
    query(label(e)) = true using 'res'. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_rdelta(const AutomataBase<S>&, const IdentityView<T>&,
		 OutputIterator res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::states k);

  /** store the output states of the state 'from' where
    the label matches the letter. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_letter_rdelta(const AutomataBase<S>&, const IdentityView<T>&,
			OutputIterator res, 
			hstate_t from, 
			const L& letter,
			delta_kind::states k);

  /** store the output op_spontaneous transitions. */
  template<class S, class T, typename OutputIterator>
  void op_spontaneous_rdelta(const AutomataBase<S>&, const IdentityView<T>&,
			     OutputIterator res, 
			     hstate_t from, 
			     delta_kind::states k);

  // output_return_type = Container
  // output_type        = hstate_t
  // direction	  = input

  /** store the output states of the state 'from' in the container
    'res' */
  template<class S, class T, typename Container>
  void op_rdeltac(const AutomataBase<S>&, const IdentityView<T>&,
		  Container& res, hstate_t from, delta_kind::states k);

  /** store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_rdeltac(const AutomataBase<S>&, const IdentityView<T>&,
		  Container& res, 
		  hstate_t from, 
		  const L& query,
		  delta_kind::states k);

  /** store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_letter_rdeltac(const AutomataBase<S>&, const IdentityView<T>&,
			 Container& res, 
			 hstate_t from, 
			 const L& letter,
			 delta_kind::states k);

  /** store the output op_spontaneous transitions. */
  template<class S, class T, typename Container>
  void op_spontaneous_rdeltac(const AutomataBase<S>&, const IdentityView<T>&,
			      Container& res, 
			      hstate_t from, 
			      delta_kind::states k);

} // vcsn

# undef AutoType


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/implementation/automaton_view.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_AUTOMATA_CONCRETE_AUTOMATON_VIEW_HH
