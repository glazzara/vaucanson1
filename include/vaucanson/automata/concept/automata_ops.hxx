// automata_ops.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_OPS_HXX
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_OPS_HXX

# include <iterator>
# include <set>
# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/contract.hh>
# include <vaucanson/algebra/concept/series_base.hh>

namespace vcsn {

#define AutoType(Type) \
  typename Element<S, T>::Type

  template <class S, class T>
  inline
  const typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>&, const T& v)
  {
    return v.tag();
  }

  template <class S, class T>
  inline
  typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>&, T& v)
  {
    return v.tag();
  }

  template <class S, class T>
  inline
  bool
  op_exists(const AutomataBase<S>&, const T& v)
  {
    return v.exists();
  }

  template <class S, class T>
  inline
  typename automaton_traits<T>::states_t
  op_states(const AutomataBase<S>&, const T& v)
  {
    return v.states();
  }

  template <class S, class T>
  inline
  typename automaton_traits<T>::edges_t
  op_edges(const AutomataBase<S>&, const T& v)
  {
    return v.edges();
  }

  template <class S, class T>
  inline
  typename automaton_traits<T>::initial_support_t
  op_initial(const AutomataBase<S>&, const T& v)
  {
    return v.initial();
  }

  template <class S, class T>
  inline
  typename automaton_traits<T>::final_support_t
  op_final(const AutomataBase<S>&, const T& v)
  {
    return v.final();
  }

  template <class S, class T>
  inline
  void
  op_set_initial(const AutomataBase<S>& ss, T& v, 
		 hstate_t state,
		 const AutoType(series_elt_t)& s)
  {
    typedef typename Element<S, T>::serie_value_t serie_value_t;
    v.set_initial(state,
		  s.value(),
		  zero_value(ss.series(),
			     SELECT(serie_value_t)));
  }

  template <class S, class T>
  inline
  typename Element<S, T>::series_elt_t
  op_get_initial(const AutomataBase<S>& s, 
		 const T& v, 
		 hstate_t state)
  {
    return typename Element<S, T>::series_elt_t
      (s.series(),
       v.get_initial(state,
		     zero_value(s.series(),
				SELECT(AutoType(serie_value_t)))));
       }
  
  template <class S, class T>
  inline
  void
  op_set_final(const AutomataBase<S>& ss, T& v, 
	       hstate_t state,
	       const typename Element<S, T>::series_elt_t& s)
  {
    v.set_final(state,
		s.value(),
		zero_value(ss.series(),
			   SELECT(AutoType(serie_value_t))));
  }

  template <class S, class T>
  inline
  typename Element<S, T>::series_elt_t
  op_get_final(const AutomataBase<S>& s, 
	       const T& v, 
	       hstate_t state)
  {
    return typename Element<S, T>::series_elt_t
      (s.series(),
       v.get_final(state,
		   zero_value(s.series(),
			      SELECT(AutoType(serie_value_t)))));
  }
  
  template <class S, class T>
  inline
  void
  op_clear_initial(const AutomataBase<S>&, T& v)
  {
    return v.clear_initial();
  }

  template <class S, class T>
  inline
  void
  op_clear_final(const AutomataBase<S>&, T& v)
  {
    return v.clear_final();
  }
  
  template <class S, class T>
  inline
  hstate_t
  op_add_state(const AutomataBase<S>&, T& v)
  {
    return v.add_state();
  }

  template <class S, class T>
  inline
  hstate_t
  op_choose_state(const AutomataBase<S>& s, const T& v)
  {
    typedef typename automaton_traits<T>::states_t states_t;
    typedef typename states_t::iterator state_iterator;
    const states_t& st = op_states(s, v);
    assertion(st.size() > 0);
    int n = utility::random::generate(0, int(st.size() - 1));
    state_iterator ss = st.begin();
    for (; n > 0; --n)
      ++ss;
    return *ss;
  }

  template <class S, class T>
  inline
  hedge_t 
  op_add_edge(const AutomataBase<S>&, T& v,
	      hstate_t from, 
	      hstate_t to, 
	      const typename Element<S, T>::label_t& label)
  {
    return v.add_edge(from, to, label);
  }

  template <class S, class T>
  inline
  hedge_t 
  op_add_serie_edge(const AutomataBase<S>& s, T& v,
		    hstate_t from, 
		    hstate_t to, 
		    const typename Element<S, T>::series_elt_t& l)
  {
    return op_add_edge(s, v, from, to, l.value());
  }

  template <class S, class T>
  inline
  hedge_t 
  op_add_spontaneous(const AutomataBase<S>& s, T& v,
		     hstate_t from, 
		     hstate_t to,
		     const typename Element<S, T>::semiring_elt_t& w)
  {    
    AutoType(series_elt_t) ss;
    ss.assoc(algebra::identity_as<AutoType(monoid_elt_value_t)>::
	    of(s.series().monoid()), w);
    return op_add_serie_edge(s, v, from, to, ss);
  }

  template <class S, class T>
  inline
  hedge_t 
  op_add_letter_edge(const AutomataBase<S>& s, T& v,
		     hstate_t from, 
		     hstate_t to, 
		     const typename Element<S, T>::letter_t& l)
  {
    return op_add_edge(s, v, from, to, l);
  }
  
  template <class S, class T>
  inline
  void
  op_update(const AutomataBase<S>&, T& v,
	    hedge_t  e, 
	    const AutoType(label_t)& l)
  {
    // FIXME: test that l != 0.
    v.update(e, l);
  }
  
  template <class S, class T>
  inline
  void
  op_del_state(const AutomataBase<S>&, T& v,
	       hstate_t s)
  {
    v.del_state(s);
  }

  template <class S, class T>
  inline
  void
  op_del_edge(const AutomataBase<S>&, T& v,
	      hedge_t e)
  {
    v.del_edge(e);
  }
	 
  template <class S, class T>
  inline
  void
  op_safe_del_state(const AutomataBase<S>&, T& v,
		    hstate_t s)
  {
    v.safe_del_state(s);
  }

  template <class S, class T>
  inline
  bool
  op_has_state(const AutomataBase<S>&, const T& v,
	       hstate_t s)
  {
    return v.has_state(s);
  }

  template <class S, class T>
  inline
  bool
  op_has_edge(const AutomataBase<S>&, const T& v,
	      hedge_t e)
  {
    return v.has_edge(e);
  }

  template <class S, class T>
  inline
  hstate_t
  op_origin_of(const AutomataBase<S>&, const T& v,
	       hedge_t e)
  {
    return v.origin_of(e);
  }

  template <class S, class T>
  inline
  hstate_t
  op_aim_of(const AutomataBase<S>&, const T& v,
	    hedge_t e)
  {
    return v.aim_of(e);
  }
  
  template <class S, class T>
  inline
  typename Element<S, T>::label_t
  op_label_of(const AutomataBase<S>&, const T& v,
	      hedge_t e)
  {
    return v.label_of(e);
  }
   
  template <class S, class T>
  inline
  const typename Element<S, T>::series_elt_t
  op_serie_of(const AutomataBase<S>& s, const T& v,
	      hedge_t e)
  {
    return typename Element<S, T>::series_elt_t
      (s.series(),
       v.label_of(e));
  }
   
  template <class S, class T>
  inline
  typename Element<S, T>::serie_value_t
  op_serie_value_of(const AutomataBase<S>& s, const T& v,
		    hedge_t e)
  {
    return op_serie_of(s, v, e).value();
  }
  
  template <class S, class T>
  inline
  typename Element<S, T>::monoid_elt_t
  op_word_of(const AutomataBase<S>& s, const T& v,
	     hedge_t e)
  {
    return typename Element<S, T>::monoid_elt_t
      (s.series().monoid(),
       v.label_of(e));
  }

  template <class S, class T>
  inline
  typename Element<S, T>::monoid_elt_value_t
  op_word_value_of(const AutomataBase<S>& s, const T& v,
		   hedge_t e)
  {
    return op_word_of(s, v, e).value();
  }

  template <class S, class T>
  inline
  typename Element<S, T>::letter_t
  op_letter_of(const AutomataBase<S>&, const T& v,
	       hedge_t e)
  {
    return v.label_of(e);
  }
  
  template <class S, class T>
  inline
  bool
  op_is_spontaneous(const AutomataBase<S>& s, const T& v,
		    hedge_t e)
  {
    return (op_serie_of(s, v, e) == 
	    algebra::identity_as<AutoType(serie_value_t)>::of(s.series()));
  }

  struct always_true
  {
    bool operator()(hedge_t) const
    {
      return true;
    }
  };

  template <class S, class T, class Letter>
  class letter_query
  {
  public:
    letter_query()
    {
      w_ *= Letter();
    }

    bool operator()(hedge_t e) const
    {
      return (op_series_get(s_->series(), 
 			    op_serie_of(*s_, *v_, e).value(),
 			    w_.value())
 	      != algebra::zero_as<AutoType(semiring_elt_value_t)>
 	      ::of(s_->series().semiring()));
    }

    //  private:
    const S* s_;
    const T* v_;
    AutoType(monoid_elt_t) w_;
  };

  template <class S, class T, class Letter>
  inline
  const letter_query<S, T, Letter>& make_letter_query(const S& s,
						      const T& t,
						      const Letter& l)
  {
    static letter_query<S, T, Letter> lq;
    lq.s_ = &s;
    lq.v_ = &t;
    *lq.w_.begin() = l;
    return lq;
  }

  template <class S, class T>
  class spontaneous_query
  {
  public:
    spontaneous_query(const S& s, const T& v):
      s_(s),
      v_(v)
    {}

    bool operator()(hedge_t e) const
    {
      return (op_serie_of(s_, v_, e)
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
  inline
  spontaneous_query<S, T> make_spontaneous_query(const S& s,
					    const T& t)
  {
    return spontaneous_query<S, T>(s.self(), t);
  }

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = output

  /*! store the output edges of the state 'from' using 'res'. */
  template <class S, class T, 
	    typename OutputIterator>					
  inline
  void op_delta(const AutomataBase<S>& s, const T& v,
		OutputIterator res, 
		hstate_t from, 
		delta_kind::edges k)
  {
    op_delta(s, v, res, from, always_true(), k);
  }

  /*! store the output edges of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  inline
  void op_delta(const AutomataBase<S>&, const T& v,
		OutputIterator res, 
		hstate_t from, 
		const L& query,
		delta_kind::edges k)
  {
    v.delta(res, from, query, k);
  }
    
  /*! store the output edges of the state 'from' where
    the label matches the letter. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  inline
  void op_letter_delta(const AutomataBase<S>& s, const T& v,
		       OutputIterator res, 
		       hstate_t from, 
		       const L& letter,
		       delta_kind::edges k)
  {
    op_delta(s, v, res, from, make_letter_query(s.self(), v, letter), k);
  }

  /*! store the output spontaneous transitions. */
  template <class S, class T,
	    typename OutputIterator>
  inline
  void op_spontaneous_delta(const AutomataBase<S>& s, 
			    const T& v,
			    OutputIterator res, 
			    hstate_t from, 
			    delta_kind::edges k)
  {
    op_delta(s, v, res, from, make_spontaneous_query(s.self(), v), k);
  }

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	        = output

  /*! store the output edges of the state 'from' in the container
    'res' */
  template <class S, class T,
	    typename Container>
  inline
  void op_deltac(const AutomataBase<S>& s, const T& v,
		 Container& res, hstate_t from, delta_kind::edges k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_delta(s, v, i, from, k);
  }

  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  inline
  void op_deltac(const AutomataBase<S>& s, 
		 const T& v,
		 Container& res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::edges k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_delta(s, v, i, from, query, k);
  }


  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  inline
  void op_letter_deltac(const AutomataBase<S>& s, 
			const T& v,
			Container& res, 
			hstate_t from, 
			const L& letter,
			delta_kind::edges k)
  {
    op_letter_delta(s, v,
		    std::insert_iterator<Container>(res, res.begin()),
		    from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template <class S, class T, class Container>
  inline
  void op_spontaneous_deltac(const AutomataBase<S>& s, 
			     const T& v,
			     Container& res, 
			     hstate_t from, 
			     delta_kind::edges k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_spontaneous_delta(s, v, i, from, k);
  }

  // output_return_type = OutputIterator
  // output_type        = hstate_t
  // direction	  = output

  /*! store the output states of the state 'from' using 'res'. */
  template <class S, class T, 
	    typename OutputIterator>					
  inline
  void op_delta(const AutomataBase<S>& s, const T& v,
		OutputIterator res, 
		hstate_t from, 
		delta_kind::states k)
  {
    op_delta(s, v, res, from, always_true(), k);
  }

  /*! store the output states of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  inline
  void op_delta(const AutomataBase<S>&, const T& v,
		OutputIterator res, 
		hstate_t from, 
		const L& query,
		delta_kind::states)
  {
    v.delta(res, from, query, delta_kind::states());
  }
    
  /*! store the output states of the state 'from' where
    the label matches the letter. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  inline
  void op_letter_delta(const AutomataBase<S>& s, const T& v,
		       OutputIterator res, 
		       hstate_t from, 
		       const L& letter,
		       delta_kind::states k)
  {
    op_delta(s, v, res, from, make_letter_query(s.self(), v, letter), k);
  }

  /*! store the output spontaneous transitions. */
  template <class S, class T,
	    typename OutputIterator>
  inline
  void op_spontaneous_delta(const AutomataBase<S>& s, const T& v,
			    OutputIterator res, 
			    hstate_t from, 
			    delta_kind::states k)
  {
    op_delta(s, v, res, from, make_spontaneous_query(s.self(), v), k);
  }

  // output_return_type = Container
  // output_type        = hstate_t
  // direction	  = output

  /*! store the output states of the state 'from' in the container
    'res' */
  template <class S, class T,
	    typename Container>
  inline
  void op_deltac(const AutomataBase<S>& s, const T& v,
		 Container& res, hstate_t from, delta_kind::states k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_delta(s, v, i, from, k);
  }

  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  inline
  void op_deltac(const AutomataBase<S>& s, 
		 const T& v,
		 Container& res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::states k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_delta(s, v, i, from, query, k);
  }


  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  inline
  void op_letter_deltac(const AutomataBase<S>& s, 
			const T& v,
			Container& res, 
			hstate_t from, 
			const L& letter,
			delta_kind::states k)
  {
    op_letter_delta(s.self(), v,
		    std::insert_iterator<Container>(res, res.begin()),
		    from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template <class S, class T, class Container>
  inline
  void op_spontaneous_deltac(const AutomataBase<S>& s, 
			     const T& v,
			     Container& res, 
			     hstate_t from, 
			     delta_kind::states k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_spontaneous_delta(s, v, i, from, k);
  }

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = output

  /*! store the output edges of the state 'from' using 'res'. */
  template <class S, class T, 
	    typename OutputIterator>					
  inline
  void op_rdelta(const AutomataBase<S>& s, const T& v,
		 OutputIterator res, 
		 hstate_t from, 
		 delta_kind::edges k)
  {
    op_rdelta(s, v, res, from, always_true(), k);
  }

  /*! store the output edges of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  inline
  void op_rdelta(const AutomataBase<S>&, const T& v,
		 OutputIterator res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::edges k)
  {
    v.rdelta(res, from, query, k);
  }
    
  /*! store the output edges of the state 'from' where
    the label matches the letter. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  inline
  void op_letter_rdelta(const AutomataBase<S>& s, const T& v,
			OutputIterator res, 
			hstate_t from, 
			const L& letter,
			delta_kind::edges k)
  {
    op_rdelta(s, v, res, from, make_letter_query(s.self(), v, letter), k);
  }

  /*! store the output spontaneous transitions. */
  template <class S, class T,
	    typename OutputIterator>
  inline
  void op_spontaneous_rdelta(const AutomataBase<S>& s, const T& v,
			     OutputIterator res, 
			     hstate_t from, 
			     delta_kind::edges k)
  {
    op_rdelta(s, v, res, from, make_spontaneous_query(s.self(), v), k);
  }

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	  = output

  /*! store the output edges of the state 'from' in the container
    'res' */
  template <class S, class T,
	    typename Container>
  inline
  void op_rdeltac(const AutomataBase<S>& s, const T& v,
		  Container& res, hstate_t from, delta_kind::edges k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_rdelta(s, v, i, from, k);
  }

  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  inline
  void op_rdeltac(const AutomataBase<S>& s, 
		  const T& v,
		  Container& res, 
		  hstate_t from, 
		  const L& query,
		  delta_kind::edges k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_rdelta(s, v, i, from, query, k);
  }


  /*! store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  inline
  void op_letter_rdeltac(const AutomataBase<S>& s, 
			 const T& v,
			 Container& res, 
			 hstate_t from, 
			 const L& letter,
			 delta_kind::edges k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_letter_rdelta(s, v, i, from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template <class S, class T, class  Container>
  inline
  void op_spontaneous_rdeltac(const AutomataBase<S>& s, 
			      const T& v,
			      Container& res, 
			      hstate_t from, 
			      delta_kind::edges k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_spontaneous_rdelta(s, v, i, from, k);
  }

  // output_return_type = OutputIterator
  // output_type        = hstate_t
  // direction	  = output

  /*! store the output states of the state 'from' using 'res'. */
  template <class S, class T, 
	    typename OutputIterator>					
  inline
  void op_rdelta(const AutomataBase<S>&, const T& v,
		 OutputIterator res, 
		 hstate_t from, 
		 delta_kind::states k)
  {
    v.rdelta(res, from, always_true(), k);
  }

  /*! store the output states of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  inline
  void op_rdelta(const AutomataBase<S>& s, const T& v,
		 OutputIterator res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::states)
  {
    std::set<hedge_t> ret;
    std::insert_iterator<std::set<hedge_t> > ret_i(ret, ret.begin());
    op_rdelta(s, v, ret_i, from, query, delta_kind::edges());
    const Element<S, T> a(s.self(), v);
    for (typename std::set<hedge_t>::const_iterator e = ret.begin();
	 e != ret.end(); ++e)
      {
	*res = a.origin_of(*e);
	++res;
      }
  }
    
  /*! store the output states of the state 'from' where
    the label matches the letter. */
  template <class S, class T,
	    typename OutputIterator, typename L>	
  inline
  void op_letter_rdelta(const AutomataBase<S>& s, const T& v,
			OutputIterator res, 
			hstate_t from, 
			const L& letter,
			delta_kind::states k)
  {
    op_rdelta(s, v, res, from, make_letter_query(s.self(), v, letter), k);
  }

  /*! store the output spontaneous transitions. */
  template <class S, class T,
	    typename OutputIterator>
  inline
  void op_spontaneous_rdelta(const AutomataBase<S>& s, const T& v,
			     OutputIterator res, 
			     hstate_t from, 
			     delta_kind::states k)
  {
    op_rdelta(s, v, res, from, make_spontaneous_query(s.self(), v), k);
  }

  // output_return_type = Container
  // output_type        = hstate_t
  // direction	  = output

  /*! store the output states of the state 'from' in the container
    'res' */
  template <class S, class T,
	    typename Container>
  inline
  void op_rdeltac(const AutomataBase<S>& s, const T& v,
		  Container& res, hstate_t from, delta_kind::states k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_rdelta(s, v, i, from, k);
  }

  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  inline
  void op_rdeltac(const AutomataBase<S>& s, 
		  const T& v,
		  Container& res, 
		  hstate_t from, 
		  const L& query,
		  delta_kind::states k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_rdelta(s, v, i, from, query, k);
  }


  /*! store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <class S, class T,
	    typename Container, typename L>	
  inline
  void op_letter_rdeltac(const AutomataBase<S>& s, 
			 const T& v,
			 Container& res, 
			 hstate_t from, 
			 const L& letter,
			 delta_kind::states k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_letter_rdelta(s, v, i, from, letter, k);
  }

  /*! store the output op_spontaneous transitions. */
  template <class S, class T, class Container>
  inline
  void op_spontaneous_rdeltac(const AutomataBase<S>& s, 
			      const T& v,
			      Container& res, 
			      hstate_t from, 
			      delta_kind::states k)
  {
    std::insert_iterator<Container> i(res, res.begin());
    op_spontaneous_rdelta(s, v, i, from, k);
  }

} // vcsn

# undef AutoType

#endif // VCSN_AUTOMATA_CONCEPT_AUTOMATA_OPS_HXX
