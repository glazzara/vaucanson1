// transpose_view.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCRETE_TRANSPOSE_VIEW_HH
# define VCSN_AUTOMATA_CONCRETE_TRANSPOSE_VIEW_HH

# include <vaucanson/automata/concrete/automaton_view.hh>
# include <vaucanson/fundamental/predecls.hh>

namespace vcsn {

  template <class T>
  struct TransposeView : public IdentityView<T>
  {
    TransposeView();
    TransposeView(const T&);
    TransposeView(T&);
    TransposeView(const TransposeView&);
  };
  
  template <class T>
  struct transpose_traits
  {
    typedef undefined_type type;
  };

  template <class S, class T>
  struct transpose_traits<Element<S, T> >
  {
    typedef Element<S, TransposeView<T> > type;
  };

  template <class S, class T>
  Element<S, TransposeView<T> >
  transpose_view(Element<S, T>&);

  template <class S, class T>
  const Element<S, TransposeView<T> >
  transpose_view(const Element<S, T>&);

  template <typename T>
  struct automaton_traits<TransposeView<T> >
  {
    typedef typename automaton_traits<T>::label_t label_t;
    typedef typename automaton_traits<T>::serie_value_t serie_value_t;
    typedef typename automaton_traits<T>::word_value_t word_value_t;
    typedef typename automaton_traits<T>::semiring_elt_value_t semiring_elt_value_t;
    typedef typename automaton_traits<T>::letter_t letter_t;
    typedef typename automaton_traits<T>::tag_t tag_t;
    typedef typename automaton_traits<T>::states_t states_t;
    typedef typename automaton_traits<T>::state_data_t state_data_t;
    typedef typename automaton_traits<T>::state_iterator state_iterator;
    typedef typename automaton_traits<T>::edges_t edges_t;
    typedef typename automaton_traits<T>::edge_data_t edge_data_t;
    typedef typename automaton_traits<T>::edge_iterator edge_iterator;
    typedef typename automaton_traits<T>::initial_t initial_t;
    typedef typename automaton_traits<T>::initial_iterator initial_iterator;
    typedef typename automaton_traits<T>::initial_support_t initial_support_t;
    typedef typename automaton_traits<T>::final_t final_t;
    typedef typename automaton_traits<T>::final_iterator final_iterator;
    typedef typename automaton_traits<T>::final_support_t final_support_t;
  };

#define AutoType(Type) \
  typename Element<S, TransposeView<T> >::Type

  template <class S, class T>
  typename automaton_traits<TransposeView<T> >::initial_support_t
  op_initial(const AutomataBase<S>&, const TransposeView<T>&);

  template <class S, class T>
  typename automaton_traits<TransposeView<T> >::final_support_t
  op_final(const AutomataBase<S>&, const TransposeView<T>&);

  template <class S, class T>
  void
  op_set_initial(const AutomataBase<S>&, TransposeView<T>&, 
		 hstate_t state,
		 const AutoType(series_elt_t)& s);

  template <class S, class T>
  AutoType(series_elt_t)
  op_get_initial(const AutomataBase<S>&, 
		 const TransposeView<T>&, 
		 hstate_t state);
  
  template <class S, class T>
  void
  op_set_final(const AutomataBase<S>&, TransposeView<T>&, 
	       hstate_t state,
	       const typename Element<S, T>::series_elt_t& s);

  template <class S, class T>
  typename Element<S, T>::series_elt_t
  op_get_final(const AutomataBase<S>&, 
	       const TransposeView<T>&, 
	       hstate_t state);
  
  template <class S, class T>
  void
  op_clear_initial(const AutomataBase<S>&, TransposeView<T>&);

  template <class S, class T>
  void
  op_clear_final(const AutomataBase<S>&, TransposeView<T>&);
  
  template <class S, class T>
  hstate_t
  op_origin_of(const AutomataBase<S>&, const TransposeView<T>&,
	       hedge_t);

  template <class S, class T>
  hstate_t
  op_aim_of(const AutomataBase<S>&, const TransposeView<T>&,
	    hedge_t);
  
  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = output

  /*! store the output edges of the state 'from' using 'res'. */
  template <class S, class T, 
	    typename OutputIterator>					
  void op_delta(const AutomataBase<S>&, const TransposeView<T>&,
		OutputIterator res, 
		hstate_t from, 
		delta_kind::edges k);

  /*! store the output edges of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  void op_delta(const AutomataBase<S>&, const TransposeView<T>&,
		OutputIterator res, 
		hstate_t from, 
		const L& query,
		delta_kind::edges k);
    
  /*! store the output edges of the state 'from' where
    the label matches the letter. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  void op_letter_delta(const AutomataBase<S>&, const TransposeView<T>&,
		       OutputIterator res, 
		       hstate_t from, 
		       const L& letter,
		       delta_kind::edges k);

  /*! store the output spontaneous transitions. */
  template <class S, class T,
	    typename OutputIterator>
  void op_spontaneous_delta(const AutomataBase<S>&, const TransposeView<T>&,
			    OutputIterator res, 
			    hstate_t from, 
			    delta_kind::edges k);

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	  = output

  /*! store the output edges of the state 'from' in the container
    'res' */
  template <class S, class T,
	    typename Container>
  void op_deltac(const AutomataBase<S>&, const TransposeView<T>&,
		 Container& res, hstate_t from, delta_kind::edges k);

  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  void op_deltac(const AutomataBase<S>&, const TransposeView<T>&,
		 Container& res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::edges k);

  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  void op_letter_deltac(const AutomataBase<S>&, const TransposeView<T>&,
			Container& res, 
			hstate_t from, 
			const L& letter,
			delta_kind::edges k);

  /*! store the output op_spontaneous transitions. */
  template <class S, class T, class Container>
  void op_spontaneous_deltac(const AutomataBase<S>&, const TransposeView<T>&,
			     Container& res, 
			     hstate_t from, 
			     delta_kind::edges k);

  // output_return_type = OutputIterator
  // output_type        = hstate_t
  // direction	  = output

  /*! store the output states of the state 'from' using 'res'. */
  template<class S, class T, typename OutputIterator> 
  void op_delta(const AutomataBase<S>&, const TransposeView<T>&,
		OutputIterator res, 
		hstate_t from, 
		delta_kind::states k);

  /*! store the output states of the state 'from' where
    query(label(e)) = true using 'res'. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_delta(const AutomataBase<S>&, const TransposeView<T>&,
		OutputIterator res, 
		hstate_t from, 
		const L& query,
		delta_kind::states k);

  /*! store the output states of the state 'from' where
    the label matches the letter. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_letter_delta(const AutomataBase<S>&, const TransposeView<T>&,
		       OutputIterator res, 
		       hstate_t from, 
		       const L& letter,
		       delta_kind::states k);

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename OutputIterator>	
  void op_spontaneous_delta(const AutomataBase<S>&, const TransposeView<T>&,
			    OutputIterator res, 
			    hstate_t from, 
			    delta_kind::states k);

  // output_return_type = Container
  // output_type        = hstate_t
  // direction	  = output

  /*! store the output states of the state 'from' in the container
    'res' */
  template<class S, class T, typename Container>
  void op_deltac(const AutomataBase<S>&, const TransposeView<T>&,
		 Container& res, hstate_t from, delta_kind::states k);

  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_deltac(const AutomataBase<S>&, const TransposeView<T>&,
		 Container& res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::states k);

  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_letter_deltac(const AutomataBase<S>&, const TransposeView<T>&,
			Container& res, 
			hstate_t from, 
			const L& letter,
			delta_kind::states k);

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename Container>
  void op_spontaneous_deltac(const AutomataBase<S>&, const TransposeView<T>&,
			     Container& res, 
			     hstate_t from, 
			     delta_kind::states k);

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = input

  /*! store the output edges of the state 'from' using 'res'. */
  template<class S, class T, typename OutputIterator>		
  void op_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
		 OutputIterator res, 
		 hstate_t from, 
		 delta_kind::edges k);

  /*! store the output edges of the state 'from' where
    query(label(e)) = true using 'res'. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
		 OutputIterator res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::edges k);

  /*! store the output edges of the state 'from' where
    the label matches the letter. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_letter_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
			OutputIterator res, 
			hstate_t from, 
			const L& letter,
			delta_kind::edges k);

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename OutputIterator>
  void op_spontaneous_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
			     OutputIterator res, 
			     hstate_t from, 
			     delta_kind::edges k);

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	  = input

  /*! store the output edges of the state 'from' in the container
    'res' */
  template<class S, class T, typename Container>
  void op_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
		  Container& res, hstate_t from, delta_kind::edges k);

  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
		  Container& res, 
		  hstate_t from, 
		  const L& query,
		  delta_kind::edges k);

  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_letter_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
			 Container& res, 
			 hstate_t from, 
			 const L& letter,
			 delta_kind::edges k);

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename Container>
  void op_spontaneous_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
			      Container& res, 
			      hstate_t from, 
			      delta_kind::edges k);

  // output_return_type = OutputIterator
  // output_type        = hstate_t
  // direction	  = input

  /*! store the output states of the state 'from' using 'res'. */
  template<class S, class T, typename OutputIterator>		
  void op_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
		 OutputIterator res, 
		 hstate_t from, 
		 delta_kind::states k);

  /*! store the output states of the state 'from' where
    query(label(e)) = true using 'res'. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
		 OutputIterator res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::states k);

  /*! store the output states of the state 'from' where
    the label matches the letter. */
  template<class S, class T, typename OutputIterator, typename L>	
  void op_letter_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
			OutputIterator res, 
			hstate_t from, 
			const L& letter,
			delta_kind::states k);

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename OutputIterator>
  void op_spontaneous_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
			     OutputIterator res, 
			     hstate_t from, 
			     delta_kind::states k);

  // output_return_type = Container
  // output_type        = hstate_t
  // direction	  = input

  /*! store the output states of the state 'from' in the container
    'res' */
  template<class S, class T, typename Container>
  void op_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
		  Container& res, hstate_t from, delta_kind::states k);

  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
		  Container& res, 
		  hstate_t from, 
		  const L& query,
		  delta_kind::states k);

  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template<class S, class T, typename Container, typename L>	
  void op_letter_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
			 Container& res, 
			 hstate_t from, 
			 const L& letter,
			 delta_kind::states k);

  /*! store the output op_spontaneous transitions. */
  template<class S, class T, typename Container>
  void op_spontaneous_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
			      Container& res, 
			      hstate_t from, 
			      delta_kind::states k);

} // vcsn

# undef AutoType


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/concrete/transpose_view.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_AUTOMATA_CONCRETE_TRANSPOSE_VIEW_HH
