// automata_base.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HH
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HH

# include <iterator>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/delta_kind.hh>
# include <vaucanson/algebra/concept/series_base.hh>

namespace vcsn {

  /** @addtogroup automata */  /** @{ */
  /** @addtogroup concept  */  /** @{ */

  /*-------------------.
  | AutomataBase<Self> |
  `-------------------*/
  /// The most general concept of automaton.
  /** It symbolises the set of automata with multiplicity over a fixed
    semiring and a fixed free monoid. Note that this class is abstract
    in the hierarchy.
  */
  template <typename Self>
  struct AutomataBase
    : Structure<Self>
  {
  public:
    /// The type of the series set associated with the automaton.
    typedef typename virtual_types<Self>::series_t  series_t;

  protected:
    /// The default constructor is protected since it is an abstract class.
    AutomataBase();

    /// The copy constructor is protected since it is an abstract class.
    AutomataBase(const AutomataBase& other);

  public:
    /// Accessor to the set of series of the automaton.
    const series_t& series() const;
  };

  // traits for automaton implementation.
  template <typename T>
  struct automaton_traits {
    typedef undefined_type label_t;
    typedef undefined_type series_value_t;
    typedef undefined_type word_value_t;
    typedef undefined_type semiring_elt_value_t;
    typedef undefined_type letter_t;
    typedef undefined_type tag_t;
    typedef undefined_type states_t;
    typedef undefined_type state_data_t;
    typedef undefined_type state_iterator;
    typedef undefined_type edges_t;
    typedef undefined_type edge_data_t;
    typedef undefined_type edge_iterator;
    typedef undefined_type initial_t;
    typedef undefined_type initial_iterator;
    typedef undefined_type initial_support_t;
    typedef undefined_type final_t;
    typedef undefined_type final_iterator;
    typedef undefined_type final_support_t;
 };

  /*-----------------------------------.
  | virtual_types<AutomataBase<Self> > |
  `-----------------------------------*/
  template <class S>
  struct virtual_types<AutomataBase<S> >
    : virtual_types<Structure<S> >
  { };

  /*------------------------------------.
  | dynamic_traits<AutomataBase<Self> > |
  `------------------------------------*/
  template <class S>
  struct dynamic_traits<AutomataBase<S> >
    : dynamic_traits<Structure<S> >
  { };

  /*-----------------------------------.
  | MetaElement<AutomataBase<Self>, T> |
  `-----------------------------------*/
  /// Services of every element of the automata set.
  /** MetaElement<AutomataBase<Self>, T> defines the interface of
    every automaton that is the result of the interaction of a
    structural element (AutomataBase<Self>) and an implementation T.

    The implementation must be compatible with the automaton
    implementation concept. For this purpose, you can either use
    directly your implementation of automaton or use for example the
    class automaton_impl which is an adapter that enrich basic data
    structures to make them compatible with automaton implementation
    concept.

   */

  template <typename Self, typename T>
  struct MetaElement<AutomataBase<Self>, T>
    : MetaElement<Structure<Self>, T>
  {
    /** type of the interface of an automaton. */
    typedef MetaElement<AutomataBase<Self>, T>		      self_t;

    /** type the series set from which is build the automaton. */
    typedef typename AutomataBase<Self>::series_t	      series_t;

    /** type of the implementation of series that holds the automaton. */
    typedef typename automaton_traits<T>::series_value_t      series_value_t;

    /** type of the element of the set of series that holds the automaton. */
    typedef Element<series_t, series_value_t>		      series_elt_t;
    typedef Element<series_t, series_value_t>		      series_elt_t;

    /** type of the free monoid. */
    typedef typename series_t::monoid_t			      monoid_t;

    /** type of the free monoid element. */
    typedef typename series_elt_t::monoid_elt_t		      monoid_elt_t;

    /** type of the implementation of a word. */
    typedef typename monoid_elt_t::value_t		   monoid_elt_value_t;

    /** type of the letter. */
    typedef typename monoid_t::letter_t			      letter_t;

    /** type of the semiring set. */
    typedef typename series_t::semiring_t		      semiring_t;

    /** type of the free monoid element. */
    typedef typename series_elt_t::semiring_elt_t	      semiring_elt_t;

    /** type of the implementation of a semiring_elt. */
    typedef typename series_elt_t::semiring_elt_value_t	     semiring_elt_value_t;

    /** type of additional information that is aggregated to the automaton. */
    typedef typename automaton_traits<T>::tag_t		      tag_t;

    /** type of the label of the automaton implementation. */
    typedef typename automaton_traits<T>::label_t	      label_t;

    /** type of the states container. */
    typedef typename automaton_traits<T>::states_t	      states_t;

    /** type of the iterator over the states set. */
    typedef typename automaton_traits<T>::state_iterator     state_iterator;

    /** type of the edges set. */
    typedef typename automaton_traits<T>::edges_t	      edges_t;

    /** type of the iterator over the edges. */
    typedef typename automaton_traits<T>::edge_iterator      edge_iterator;

    /** type of the initial application. */
    typedef typename automaton_traits<T>::initial_t	      initial_t;

    /** type of the initial application support. */
    typedef typename automaton_traits<T>::initial_support_t  initial_support_t;

    /** type of the iterator of the initial application support. */
    typedef typename automaton_traits<T>::initial_iterator    initial_iterator;

    /** type of the final application. */
    typedef typename automaton_traits<T>::final_t	      final_t;

    /** type of the iterator of the final application support. */
    typedef typename automaton_traits<T>::final_iterator      final_iterator;

    /** the set of series from which is build the automaton (const version). */
    const series_t& series() const;

    /** the optional information aggregated to the automaton. */
    tag_t& tag();

    /** the optional information aggregated to the automaton. */
    const tag_t& tag() const;

    /** return true if the automaton is consistent. */
    bool exists() const;

    /** accessor to the set of states. (const version) */
    typename automaton_traits<T>::states_t
    states() const;

    /** accessor to the set of states. (const version) */
    typename automaton_traits<T>::edges_t
    edges() const;

    /** accessor to the initial application. */
    typename automaton_traits<T>::initial_support_t
    initial() const;

    /** accessor to the final application. */
    typename automaton_traits<T>::final_support_t
    final() const;

    /** return true if the state is initial (ie it is in the initial
      support) . */
    bool is_initial(hstate_t state) const;

    /** return true if the state is final (ie it is in the final support). */
    bool is_final(hstate_t state) const;

    /** set the state to be initial. */
    void set_initial(hstate_t state);

    /** set an initial multiplicity to the state. */
    void set_initial(hstate_t state, const series_elt_t& m);

    /** set the state to be final. */
    void set_final(hstate_t state);

    /** set a final multiplicity to the state. */
    void set_final(hstate_t state, const series_elt_t& m);

    /** set the state not to be initial. */
    void unset_initial(hstate_t state);

    /** set the set not to be final. */
    void unset_final(hstate_t state);

    /** make the support of the initial application to be empty. */
    void clear_initial();

    /** make the support of the final application to be empty. */
    void clear_final();

    /** return the initial multiplicity of the state. */
    Element<series_t, series_value_t>
    get_initial(hstate_t state) const;

    /** return the final multiplicity of the state. */
    Element<series_t, series_value_t>
    get_final(hstate_t what) const;

    /** add a new state to the automaton. */
    hstate_t add_state();

    /** return a randomly chosen state. (valid only if the automaton
      is not empty) */
    hstate_t choose_state() const;

    /** add a new edge between 'from' and 'to' labelled by 'label' */
    hedge_t add_edge(hstate_t from, hstate_t to, const label_t& label);

    /** add an edge using a series. */
    /** If the underlying implementation is not sufficiently general
     *  to support this operation, you will have several edges created.*/
    hedge_t add_series_edge(hstate_t from, hstate_t to, const series_elt_t& e);

    /** add a spontaneous transition between 'from' and 'to'. */
    hedge_t add_spontaneous(hstate_t from, hstate_t to,
			    const semiring_elt_t& w);

    hedge_t add_spontaneous(hstate_t from, hstate_t to);

    /** add a transition between 'from' and 'to' labelled by a letter. */
    hedge_t add_letter_edge(hstate_t from, hstate_t to,
			    const letter_t& l);

    /** update the label of an edge. */
    void update(hedge_t e, const label_t& l);

    /** delete the state 's'. */
    void del_state(hstate_t s);

    /** delete the edge 'e'. */
    void del_edge(hedge_t e);

    /** delete the state 's' and every references to it in the automaton. */
    void safe_del_state(hstate_t s);

    /** check if the state 's' is in the automaton. */
    bool has_state(hstate_t s) const;

    /** check if the edge 'e' is in the automaton. */
    bool has_edge(hedge_t e) const;

    /** return the origin of the edge 'e'. */
    hstate_t origin_of(hedge_t e) const;

    /** return the aim of the edge 'e'. */
    hstate_t aim_of(hedge_t e) const;

    /** return the label of the edge 'e'. */
    typename automaton_traits<T>::label_t
    label_of(hedge_t e) const;

    /** return the label seen as a series. */
    series_elt_t series_of(hedge_t e) const;

    /** return the label seen as a series implementation. */
    series_value_t series_value_of(hedge_t e) const;

    /** return true if the transition is spontaneous. */
    bool is_spontaneous(hedge_t e) const;

    /** return the label seen as a word. */
    monoid_elt_t word_of(hedge_t e) const;

    /** returns the label seen as word implementation. */
    monoid_elt_value_t word_value_of(hedge_t e) const;

    /** return the label seen as a letter. */
    /** Becareful, when you have more general label this method is
     *! probably invalidated (in that case, an exception should be
     *! raised.) */
    letter_t letter_of(hedge_t e) const;

    // output_return_type = OutputIterator
    // output_type        = hedge_t
    // direction	  = output

    /** store the output edges of the state 'from' using 'res'. */
    template <typename OutputIterator>
    void delta(OutputIterator res,
	       hstate_t from,
	       delta_kind::edges k) const;

    /** store the output edges of the state 'from' where
        query(a.set(), a.value(), e)) = true using 'res'. */
    template <typename OutputIterator, typename L>
    void delta(OutputIterator res,
	       hstate_t from,
	       const L& query,
	       delta_kind::edges k) const;

    /** store the output edges of the state 'from' where
      the label matches the letter. */
    template <typename OutputIterator, typename L>
    void letter_delta(OutputIterator res,
		      hstate_t from,
		      const L& letter,
		      delta_kind::edges k) const;

    /** store the output spontaneous transitions. */
    template <typename OutputIterator>
    void spontaneous_delta(OutputIterator res,
			   hstate_t from,
			   delta_kind::edges k) const;

    // output_return_type = Container
    // output_type        = hedge_t
    // direction	  = output

    /** store the output edges of the state 'from' in the container
      'res' */
    template <typename Container>
    void deltac(Container& res, hstate_t from, delta_kind::edges k) const;

    /** store the output edges of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template <typename Container, typename L>
    void deltac(Container& res,
	       hstate_t from,
	       const L& query,
	       delta_kind::edges k) const;

    /** store the output edges of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template <typename Container, typename L>
    void letter_deltac(Container& res,
		       hstate_t from,
		       const L& letter,
		       delta_kind::edges k) const;

    /** store the output spontaneous transitions. */
    template <typename Container>
    void spontaneous_deltac(Container& res,
			    hstate_t from,
			    delta_kind::edges k) const;

    // output_return_type = OutputIterator
    // output_type        = hstate_t
    // direction	  = output

    /** store the output states of the state 'from' using 'res'. */
    template <typename OutputIterator>
    void delta(OutputIterator res,
	       hstate_t from,
	       delta_kind::states k) const;

    /** store the output states of the state 'from' where
        query(label(e)) = true using 'res'. */
    template <typename OutputIterator, typename L>
    void delta(OutputIterator res,
	       hstate_t from,
	       const L& query,
	       delta_kind::states k) const;

    /** store the output states of the state 'from' where
      the label matches the letter. */
    template <typename OutputIterator, typename L>
    void letter_delta(OutputIterator res,
		      hstate_t from,
		      const L& letter,
		      delta_kind::states k) const;

    /** store the output spontaneous transitions. */
    template <typename OutputIterator>
    void spontaneous_delta(OutputIterator res,
			   hstate_t from,
			   delta_kind::states k) const;

    // output_return_type = Container
    // output_type        = hstate_t
    // direction	  = output

    /** store the output states of the state 'from' in the container
      'res' */
    template <typename Container>
    void deltac(Container& res, hstate_t from, delta_kind::states k) const;

    /** store the output states of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template <typename Container, typename L>
    void deltac(Container& res,
	       hstate_t from,
	       const L& query,
	       delta_kind::states k) const;

    /** store the output states of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template <typename Container, typename L>
    void letter_deltac(Container& res,
		       hstate_t from,
		       const L& letter,
		       delta_kind::states k) const;

    /** store the output spontaneous transitions. */
    template <typename Container>
    void spontaneous_deltac(Container& res,
			    hstate_t from,
			    delta_kind::states k) const;

    // output_return_type = OutputIterator
    // output_type        = hedge_t
    // direction	  = input

    /** store the output edges of the state 'from' using 'res'. */
    template <typename OutputIterator>
    void rdelta(OutputIterator res,
		hstate_t from,
		delta_kind::edges k) const;

    /** store the output edges of the state 'from' where
        query(label(e)) = true using 'res'. */
    template <typename OutputIterator, typename L>
    void rdelta(OutputIterator res,
	       hstate_t from,
	       const L& query,
	       delta_kind::edges k) const;

    /** store the output edges of the state 'from' where
      the label matches the letter. */
    template <typename OutputIterator, typename L>
    void letter_rdelta(OutputIterator res,
		      hstate_t from,
		      const L& letter,
		      delta_kind::edges k) const;

    /** store the output spontaneous transitions. */
    template <typename OutputIterator>
    void spontaneous_rdelta(OutputIterator res,
			   hstate_t from,
			   delta_kind::edges k) const;

    // output_return_type = Container
    // output_type        = hedge_t
    // direction	  = input

    /** store the output edges of the state 'from' in the container
      'res' */
    template <typename Container>
    void rdeltac(Container& res, hstate_t from, delta_kind::edges k) const;

    /** store the output edges of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template <typename Container, typename L>
    void rdeltac(Container& res,
	       hstate_t from,
	       const L& query,
	       delta_kind::edges k) const;

    /** store the output edges of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template <typename Container, typename L>
    void letter_rdeltac(Container& res,
		       hstate_t from,
		       const L& letter,
		       delta_kind::edges k) const;

    /** store the output spontaneous transitions. */
    template <typename Container>
    void spontaneous_rdeltac(Container& res,
			    hstate_t from,
			    delta_kind::edges k) const;


    // output_return_type = OutputIterator
    // output_type        = hstate_t
    // direction	  = input

    /** store the output states of the state 'from' using 'res'. */
    template <typename OutputIterator>
    void rdelta(OutputIterator res,
	       hstate_t from,
	       delta_kind::states k) const;

    /** store the output states of the state 'from' where
        query(label(e)) = true using 'res'. */
    template <typename OutputIterator, typename L>
    void rdelta(OutputIterator res,
	       hstate_t from,
	       const L& query,
	       delta_kind::states k) const;

    /** store the output states of the state 'from' where
      the label matches the letter. */
    template <typename OutputIterator, typename L>
    void letter_rdelta(OutputIterator res,
		      hstate_t from,
		      const L& letter,
		      delta_kind::states k) const;

    /** store the output spontaneous transitions. */
    template <typename OutputIterator>
    void spontaneous_rdelta(OutputIterator res,
			   hstate_t from,
			   delta_kind::states k) const;

    // output_return_type = Container
    // output_type        = hstate_t
    // direction	  = input

    /** store the output states of the state 'from' in the container
      'res' */
    template <typename Container>
    void rdeltac(Container& res, hstate_t from, delta_kind::states k) const;

    /** store the output states of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template <typename Container, typename L>
    void rdeltac(Container& res,
	       hstate_t from,
	       const L& query,
	       delta_kind::states k) const;

    /** store the output states of the state 'from' where
      query(label(e)) = true in the container 'res' */
    template <typename Container, typename L>
    void letter_rdeltac(Container& res,
		       hstate_t from,
		       const L& letter,
		       delta_kind::states k) const;

    /** store the output spontaneous transitions. */
    template <typename Container>
    void spontaneous_rdeltac(Container& res,
			    hstate_t from,
			    delta_kind::states k) const;

  protected:
    MetaElement();
    MetaElement(const MetaElement& other);
  };

  /** @} @} */

  template <typename S, typename St, typename T>
  St& op_rout(const AutomataBase<S>& s, St& st, const T& r);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/concept/automata_base.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HH
