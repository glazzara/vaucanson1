// automaton_impl.hh
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
#ifndef AUTOMATA_CONCEPT_AUTOMATON_IMPL_HH
# define AUTOMATA_CONCEPT_AUTOMATON_IMPL_HH

# include <vaucanson/fundamental/slots.hh>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup automata */  /* @{ */
  /*! \addtogroup concept */  /* @{ */

  /*--------------.
  | AutomatonImpl |
  `--------------*/
  //! AutomatonImpl is an data structure adapter to automaton
  //! implementation concept.
  /*! AutomatonImpl is a parameterized class whose role is to equipped
   *  a data structure with automaton implementation compatible
   *  methods.  The data structure must provides a way of storing
   *  states, edges and some basic delta functions.  An instance of
   *  AutomatonImpl holds the implementation, the series set, initial
   *  and final applications and, optionally the tags associated with
   *  the automaton.  
   * 
   *  Proxy delegation is not done as usual. We use external operators
   *  to permit a finer specialization power and to avoid binary
   *  methods problems.
   */
  template <
    typename			  Kind,
    typename			  Series,
    typename		  	  SeriesT, 
    class			  Backend, 
    typename			  Tag, 
    template <class, class> class Container 
  >
  class AutomatonImpl
    {
    protected:
      /*! type of initial and final application. */
      typedef Container<unsigned, SeriesT>      map_t;

    public:
      /*! the kind of label that the data structure hold. 
       *  can be : 
       *  - label_are_series
       *  - label_are_couples
       */
      typedef Kind				adapter_kind_t;

      /*! the type of tag held by the automaton. (can be empty) */
      typedef Tag				tag_t;

      /*! the type of the set of series. */
      typedef Series				series_t;

      /*! the type of implementation of series element. */
      typedef SeriesT				series_value_t;

      /*! the type of the data structure label. */
      typedef typename Backend::label_t		label_t;

      /*! the type of the states container. */
      typedef typename Backend::states_t	states_t;

      /*! the type of the edges container. */
      typedef typename Backend::edges_t		edges_t;
      
      /*! default constructor. */
      AutomatonImpl();

      /*! copy constructor. */
      AutomatonImpl(const AutomatonImpl& other);

      /*! states container accessor. */
      typename automaton_traits<Backend>::states_ret_t
      states() const;

      /*! edges container accessor. */
      typename automaton_traits<Backend>::edges_ret_t
      edges() const;
      
      /*! initial application accessor. */
      typename automaton_traits<Backend>::initial_ret_t
      initial() const;
      
      /*! final application accessor. */
      typename automaton_traits<Backend>::final_ret_t
      final() const;

      /*! series set accessor. */
      Series& series();

      /*! series set accessor. (const version) */
      const Series& series() const;

      /*! tag accessor. */
      Tag&	 tag();
      
      /*! tag accessor. (const version) */
      const Tag& tag() const;

      /*! return a fresh state. */
      hstate_t add_state();
      
      /*! return a fresh edge. */
      hedge_t add_edge(hstate_t from, hstate_t to, const label_t& label);

      /*! remove a state. */
      void del_state(hstate_t s);
      
      /*! remove an edge. */
      void del_edge(hedge_t e);

      /*! remove a state and every references to it. */
      void safe_del_state(hstate_t s);
      
      /*! check if a given state is in the automaton. */
      bool has_state(hstate_t s) const;
      
      /*! check if an edge is in the automaton. */
      bool has_edge(hedge_t e) const;
      
      /*! store the output states of 'from' using 'out'. */
      template<typename Iter>
      void delta_states(Iter out, hstate_t from) const;
      
      /*! store the output edges of 'from' using 'out'. */
      template<typename Iter>
      void delta_edges(Iter out, hstate_t from) const;
      
      /*! store the output states of 'from' which matches 'q' query
	using 'out' */
      template<typename Iter, typename T>
      void delta_states(Iter out, hstate_t from, const T& q) const;

      /*! store the output edges of 'from' which matches 'q' query
	using 'out' */      
      template<typename Iter, typename T>
      void delta_edges(Iter out, hstate_t from, const T& q) const;
      
      /*! store the input states of 'from' using 'out'. */
      template<typename Iter>
      void rdelta_states(Iter out, hstate_t from) const;
      
      /*! store the input edges of 'from' using 'out'. */
      template<typename Iter>
      void rdelta_edges(Iter out, hstate_t from) const;

      /*! store the input states of 'from' which matches 'q' query
	using 'out' */      
      template<typename Iter, typename T>
      void rdelta_states(Iter out, hstate_t from, const T& q) const;
      
      /*! store the input edges of 'from' which matches 'q' query
	using 'out' */
      template<typename Iter, typename T>
      void rdelta_edges(Iter out, hstate_t from, const T& q) const;

      /*! return true if the state 's' is initial. */
      bool is_initial(hstate_t s) const;
      
      /*! return true if the state 's' is final. */
      bool is_final(hstate_t s) const;
      
      /*! set the state 's' to be initial. */
      void set_initial(hstate_t s);
      
      /*! unset the state 's' to be initial. */
      void unset_initial(hstate_t s);
      
      /*! make the support of the initital application to be empty. */
      void clear_initial();

      /*! associate an initial multiplicity to 's'. */
      template<typename T>
      void set_initial(hstate_t s, const Element<series_t, T>& v);

      /*! set the state 's' to be final. */
      void set_final(hstate_t s);

      /*! unset the state 's' to be final. */
      void unset_final(hstate_t s);

      /*! make the support of the final application to be empty. */
      void clear_final();
      
      /*! associate a final multiplicity to 's'. */
      template<typename T>
      void set_final(hstate_t s, const Element<series_t, T>& v);

      /*! return the initial multiplicity of 's'. */
      Element<series_t, series_value_t>
      get_initial(hstate_t s) const;

      /*! return the final multiplicity of 's'. */
      Element<series_t, series_value_t>
      get_final(hstate_t s) const;

      /*! return the origin of the edge 'e'. */
      hstate_t origin_of(hedge_t e) const;

      /*! return the aim of the edge 'e'. */
      hstate_t aim_of(hedge_t e) const;

      /*! return the label of the edge 'e'. */
      typename automaton_traits<Backend>::label_ret_t
      label_of(hedge_t e) const;
     
      // this is not for public use: (Raph)
      // FIXME: so why is it public ? (Yann)
      Backend& impl();
      const Backend& impl() const;

    protected:
      Backend		impl_;
      Tag		tag_;
      Series		series_;
      map_t		initial_;
      map_t		final_;
    };

  template<typename K, typename S, typename T, typename B, typename Tg, 
	   template<class,class> class C>
  struct automaton_traits<AutomatonImpl<K, S, T, B, Tg, C> >
  {
    typedef K					adapter_kind_t;
    typedef S					series_t;
    typedef T					series_value_t;
    typedef Tg					tag_t;
    typedef typename B::label_t			label_t;
    typedef typename B::states_t		states_t;
    typedef typename B::edges_t			edges_t;
    typedef typename B::initial_t		initial_t;
    typedef typename B::final_t			final_t;

    typedef typename states_t::const_iterator   state_iterator;
    typedef typename edges_t::const_iterator    edge_iterator;

    typedef typename automaton_traits<B>::states_ret_t	states_ret_t;
    typedef typename automaton_traits<B>::edges_ret_t	edges_ret_t;
    typedef typename automaton_traits<B>::initial_ret_t initial_ret_t;
    typedef typename automaton_traits<B>::final_ret_t	final_ret_t;
    typedef typename automaton_traits<B>::label_ret_t	label_ret_t;
  };

  /*! @} @} */

} // vcsn

# include <vaucanson/automata/concept/automaton_impl.hxx>

#endif // AUTOMATA_CONCEPT_AUTOMATON_IMPL_HH
