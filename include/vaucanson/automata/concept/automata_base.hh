// automata_base.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

#ifndef AUTOMATA_CONCEPT_AUTOMATA_BASE_HH
# define AUTOMATA_CONCEPT_AUTOMATA_BASE_HH

# include <iterator>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/history.hh>

namespace vcsn {

  /*! \addtogroup automata */  /* @{ */
  /*! \addtogroup concept */  /* @{ */

  /*-------------------.
  | AutomataBase<Self> |
  `-------------------*/
  //! The most general concept of automaton. 
  /*! It symbolises the set of automata with multiplicity over a fixed
    semiring and a fixed free monoid. Note that this class is abstract
    in the static hierarchy.
  */
  template<typename Self>
  struct AutomataBase
    : Structure<Self>
  {
  protected:
    AutomataBase();
    AutomataBase(const AutomataBase& other);
  };

  template<typename T>
  struct automaton_traits;

  /*-----------------------------------.
  | MetaElement<AutomataBase<Self>, T> |
  `-----------------------------------*/
  //! Services of every element of the automata set. 
  /*! MetaElement<AutomataBase<Self>, T> defines the interface of
    every automaton that is the result of the interaction of a
    structural element (AutomataBase<Self>) and an implementation T.
    
    The implementation must be compatible with the automaton
    implementation concept. For this purpose, you can either use
    directly your implementation of automaton or use for example the
    class automaton_impl which is an adapter that enrich basic data
    structures to make them compatible with automaton implementation
    concept.
    
    This class is derivated from AutoKind which is paramaterized by the
    kind of label that are hold by the data structure. Indeed, you
    have the choice to use series element or implementation that can
    be converted easily to series element (as letter or series
    implementation). AutoKind will adapt accessors to label so as to
    enrich them where they are not series element or to extract their
    implementations when we want a low-level access.

   */

  template<typename Self, typename T>
  struct MetaElement<AutomataBase<Self>, T>
    : MetaElement<Structure<Self>, T>, 
      AutoKind<typename automaton_traits<T>::adapter_kind_t,
	       Element<Self, T>,
	       typename automaton_traits<T>::series_t,
	       typename automaton_traits<T>::series_value_t,
	       typename automaton_traits<T>::label_t>
  {
    /*! type of the finally instantiated object. */
    typedef MetaElement<AutomataBase<Self>, T>		      self_t;

    /*! type the series set from which is build the automaton. */
    typedef typename automaton_traits<T>::series_t	      series_t;

    /*! type of the implementation of series that holds the automaton. */
    typedef typename automaton_traits<T>::series_value_t      series_value_t;

    /*! type of the element of the set of series that holds the automaton. */
    typedef Element<series_t, series_value_t>		      series_elt_t;

    /*! type of the free monoid. */
    typedef typename series_t::monoid_t			      monoid_t;

    /*! type of the weights set. */
    typedef typename series_t::weights_t		      weights_t;

    /*! type of additional information that is aggregate to the automaton. */
    typedef typename automaton_traits<T>::tag_t		      tag_t;

    /*! type of the label of the automaton. can be different from
      series_value_t. */
    typedef typename automaton_traits<T>::label_t	      label_t;

    /*! type of the states container. */
    typedef typename automaton_traits<T>::states_t	      states_t;

    /*! type of the iterator over the states set. */
    typedef typename automaton_traits<T>::state_iterator      state_iterator;

    /*! type of the edges set. */
    typedef typename automaton_traits<T>::edges_t	      edges_t;

    /*! type of the iterator over the edges. */
    typedef typename automaton_traits<T>::edge_iterator	      edge_iterator;

    /*! type of the initial application. */
    typedef typename automaton_traits<T>::initial_t	      initial_t;

    /*! type of the iterator of the initial application support. */
    typedef typename initial_t::const_iterator		      initial_iterator;

    /*! type of the final application. */
    typedef typename automaton_traits<T>::final_t	      final_t;

    /*! type of the iterator of the final application support. */
    typedef typename final_t::const_iterator		      final_iterator;

    /*! the set of series from which is build the automaton. */
    series_t& series();

    /*! the set of series from which is build the automaton (const version). */
    const series_t& series() const;

    /*! the optional information aggregated to the automaton. */
    tag_t& tag();

    /*! the optional information aggregated to the automaton. */
    const tag_t& tag() const;

    /*! this method MUST be call when you have used a default
      constructor to build the instance. It is due to the fact that:
      - automaton are reference-counted (1) ;
      - automaton can be constructed from dynamic structures (2) ;
      Even if (1) will probably be optional in the future, (2) will not.
      If unsure, use it.
    */
    void create();

    /*! if the instance is sharing its implementation with
      another. This method clones it so as to make it independant.
     */
    void emancipate();

    /*! return the history of the automaton. (const version) */
    const history::AutomatonHistory<self_t>&
    history() const;

    /*! return the history of the automaton. */
    history::AutomatonHistory<self_t>&
    history();

    /*! return true if the automaton is consistent. */
    bool exists() const;

    /*! accessor to the set of states. (const version) */
    typename automaton_traits<T>::states_ret_t
    states() const;

    /*! accessor to the set of states. (const version) */
    typename automaton_traits<T>::edges_ret_t
    edges() const;

    /*! accessor to the initial application. */
    typename automaton_traits<T>::initial_ret_t
    initial() const;

    /*! accessor to the final application. */
    typename automaton_traits<T>::final_ret_t
    final() const;
    
    /*! return true if the state is initial (ie it is in the initial
      support) . */
    bool is_initial(hstate_t state) const;

    /*! return true if the state is final (ie it is in the final support). */
    bool is_final(hstate_t state) const;

    /*! set the state to be initial. */
    void set_initial(hstate_t state);

    /*! set an initial multiplicity to the state. */
    template<typename U>
    void set_initial(hstate_t state, const U& m);
   
    /*! set the state to be final. */
    void set_final(hstate_t state);

    /*! set a final multiplicity to the state. */
    template<typename U>
    void set_final(hstate_t state, const U& m);

    /*! set the state not to be initial. */
    void unset_initial(hstate_t state);

    /*! set the set not to be final. */
    void unset_final(hstate_t state);

    /*! make the support of the initial application to be empty. */
    void clear_initial();

    /*! make the support of the final application to be empty. */
    void clear_final();

    /*! return the initial multiplicity of the state. */
    Element<series_t, series_value_t>
    get_initial(hstate_t state) const;

    /*! return the final multiplicity of the state. */
    Element<series_t, series_value_t>
    get_final(hstate_t what) const;

    /*! add a new state to the automaton. */
    hstate_t add_state();

    /*! return a randomly chosen state. (valid only if the automaton
      is not empty) */
    hstate_t choose_state() const;

    /*! add a new edge between 'from' and 'to' labelled by 'label' */
    hedge_t add_edge(hstate_t from, hstate_t to, const label_t& label);

    /*! delete the state 's'. */
    void del_state(hstate_t s);

    /*! delete the edge 'e'. */
    void del_edge(hedge_t e);

    /*! delete the 's' and every references to it in the automaton. */
    void safe_del_state(hstate_t s);

    /*! check if the state 's' is in the automaton. */
    bool has_state(hstate_t s) const;

    /*! check if the edge 'e' is in the automaton. */
    bool has_edge(hedge_t e) const;

    /*! return the origin of the edge 'e'. */
    hstate_t origin_of(hedge_t e) const;

    /*! return the aim of the edge 'e'. */
    hstate_t aim_of(hedge_t e) const;

    /*! return the label of the edge 'e'. */
    typename automaton_traits<T>::label_ret_t
    label_of(hedge_t e) const;

    /*! store the output edges of the state 'from' using 'res'. */
    template<typename OutputIterator>					
    void delta(OutputIterator res, 
	       hstate_t from, 
	       delta_kind::edges k) const;

    /*! store the output edges of the state 'from' where
        query(label(e)) = true using 'res'. */
    template<typename OutputIterator, typename L>	
    void delta(OutputIterator res, 
	       hstate_t from, 
	       const L& query,
	       delta_kind::edges k) const;
    
    //FIXME: doc, define the concept of container.
    /*! store the output edges of the state 'from' in the container
      'res' */
    template<typename Container>
    void deltac(Container& res, hstate_t from, delta_kind::edges k) const;

    /*! store the output edges of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template<typename Container, typename L>	
    void deltac(Container& res, 
	       hstate_t from, 
	       const L& query,
	       delta_kind::edges k) const;

    /*! store the input edges of the state 'from' using 'res'. */
    template<typename OutputIterator>					
    void rdelta(OutputIterator res, 
	       hstate_t from, 
	       delta_kind::edges k) const;

    /*! store the output edges of the state 'from' where
        query(label(e)) = true using 'res'. */
    template<typename OutputIterator, typename L>	
    void rdelta(OutputIterator res, 
	       hstate_t from, 
	       const L& query,
	       delta_kind::edges k) const;
    
    //FIXME: doc, define the concept of container.
    /*! store the input edges of the state 'from' in the container
      'res' */
    template<typename Container>
    void rdeltac(Container& res, hstate_t from, delta_kind::edges k) const;

    /*! store the input edges of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template<typename Container, typename L>	
    void rdeltac(Container& res, 
	       hstate_t from, 
	       const L& query,
	       delta_kind::edges k) const;

    /*! store the output states of the state 'from' using 'res'. */
    template<typename OutputIterator>					
    void delta(OutputIterator res, 
	       hstate_t from, 
	       delta_kind::states k) const;

    /*! store the output states of the state 'from' where
        query(label(e)) = true using 'res'. */
    template<typename OutputIterator, typename L>	
    void delta(OutputIterator res, 
	       hstate_t from, 
	       const L& query,
	       delta_kind::states k) const;
    
    //FIXME: doc, define the concept of container.
    /*! store the output states of the state 'from' in the container
      'res' */
    template<typename Container>
    void deltac(Container& res, hstate_t from, delta_kind::states k) const;

    /*! store the output states of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template<typename Container, typename L>	
    void deltac(Container& res, 
	       hstate_t from, 
	       const L& query,
	       delta_kind::states k) const;

    /*! store the input states of the state 'from' using 'res'. */
    template<typename OutputIterator>					
    void rdelta(OutputIterator res, 
	       hstate_t from, 
	       delta_kind::states k) const;

    /*! store the input states of the state 'from' where
        query(label(e)) = true using 'res'. */
    template<typename OutputIterator, typename L>	
    void rdelta(OutputIterator res, 
	       hstate_t from, 
	       const L& query,
	       delta_kind::states k) const;
    
    //FIXME: doc, define the concept of container.
    /*! store the input states of the state 'from' in the container
      'res' */
    template<typename Container>
    void rdeltac(Container& res, hstate_t from, delta_kind::states k) const;

    /*! store the input states of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template<typename Container, typename L>	
    void rdeltac(Container& res, 
		 hstate_t from, 
		 const L& query,
		 delta_kind::states k) const;


  protected:
    MetaElement();
    MetaElement(const MetaElement& other);
    history::AutomatonHistory<self_t>		history_;
  };

  /*! @} @} */

  template<typename S, typename St, typename T>
  St& op_rout(const AutomataBase<S>& s, St& st, const T& r);
      
}

# include <vaucanson/automata/concept/automata_base.hxx>

#endif // AUTOMATA_CONCEPT_AUTOMATA_BASE_HH
