/*****************************************
 * <vaucanson/automata/automata_base.hh> *
 *****************************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef AUTOMATA_AUTOMATA_BASE_HH
# define AUTOMATA_AUTOMATA_BASE_HH


# include <vaucanson/algebra/concept/algebra_base.hh>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/history.hh>
# include <iterator>

namespace vcsn
{

  template<typename Self>
  struct AutomataBase
    : Structure<Self>
  {
    // Nothing interesting here 

  protected:
    AutomataBase();
    AutomataBase(const AutomataBase& other);
  };

  template<typename T>
  struct automaton_traits;

  /*-----------------------------------.
  | MetaElement<AutomataBase<Self>, T> |
  `-----------------------------------*/

  template<typename Self, typename T>
  struct MetaElement<AutomataBase<Self>, T>
    : MetaElement<Structure<Self>, T>, 
      AutoKind<typename automaton_traits<T>::adapter_kind_t,
	       Element<Self, T>,
	       typename automaton_traits<T>::series_t,
	       typename automaton_traits<T>::series_value_t,
	       typename automaton_traits<T>::label_t>
  {
    typedef MetaElement<AutomataBase<Self>, T>		self_t;
    typedef typename automaton_traits<T>::series_t		series_t;
    typedef typename automaton_traits<T>::series_value_t	series_value_t;
    typedef Element<series_t, series_value_t>			series_elt_t;
    
    typedef typename series_t::monoid_t			monoid_t;
    typedef typename series_t::weights_t			weights_t;
    typedef typename automaton_traits<T>::tag_t		tag_t;
    typedef typename automaton_traits<T>::label_t		label_t;

    typedef typename automaton_traits<T>::states_t		states_t;
    typedef typename automaton_traits<T>::state_iterator	state_iterator;

    typedef typename automaton_traits<T>::edges_t		edges_t;
    typedef typename automaton_traits<T>::edge_iterator	edge_iterator;
      
    typedef typename automaton_traits<T>::initial_t		initial_t;
    typedef typename initial_t::const_iterator		initial_iterator;
    typedef typename automaton_traits<T>::final_t		final_t;
    typedef typename final_t::const_iterator			final_iterator;
      
    void create();

    void emancipate();

    const history::AutomatonHistory<self_t>&
    history() const;

    history::AutomatonHistory<self_t>&
    history();

    bool exists() const;

    typename automaton_traits<T>::states_ret_t
    states() const;

    typename automaton_traits<T>::edges_ret_t
    edges() const;

    typename automaton_traits<T>::initial_ret_t
    initial() const;

    typename automaton_traits<T>::final_ret_t
    final() const;

    bool is_initial(hstate_t what) const;

    bool is_final(hstate_t what) const;

    void set_initial(hstate_t what);

    template<typename U>
    void set_initial(hstate_t what, const U& t);
   
    void set_final(hstate_t what);

    template<typename U>
    void set_final(hstate_t what, const U& t);

    void unset_initial(hstate_t what);

    void unset_final(hstate_t what);


    // FIXME : make this a method of all
    void clear_initial();

    void clear_final();

    Element<series_t, series_value_t>
    get_initial(hstate_t what) const;

    Element<series_t, series_value_t>
    get_final(hstate_t what) const;

    hstate_t add_state();

    hedge_t add_edge(hstate_t from, hstate_t to, const label_t& label);

    void del_state(hstate_t s);

    void del_edge(hedge_t e);

    void safe_del_state(hstate_t s);

    bool has_state(hstate_t s) const;

    bool has_edge(hedge_t e) const;

    hstate_t origin_of(hedge_t e) const;

    hstate_t aim_of(hedge_t e) const;

    typename automaton_traits<T>::label_ret_t
    label_of(hedge_t e) const;


#define DELTA_DECL(Name, Type, Kind_type, Init)						\
      template<typename OutputIterator>							\
      void Name (OutputIterator res, hstate_t from,					\
		 Kind_type k Init) const;					\
											\
      template<typename OutputIterator, typename L>					\
      void Name (OutputIterator res, hstate_t from, const L& query,			\
		 Kind_type k Init) const;				\
											\
      template<typename Container>							\
      void Name ## c (Container& dst, hstate_t from,					\
		      Kind_type k Init) const;						\
											\
      template<typename Container, typename L>						\
      void Name ## c (Container& dst, hstate_t from, const L& query,			\
		      Kind_type k Init) const;

    DELTA_DECL(delta, edges, delta_kind::edges, = delta_kind::edges());
    DELTA_DECL(rdelta, edges, delta_kind::edges, = delta_kind::edges());

    DELTA_DECL(delta, states, delta_kind::states, );
    DELTA_DECL(rdelta, states, delta_kind::states, );

#undef DELTA_DECL


    series_t& series();

    const series_t& series() const;


    tag_t& tag();
    const tag_t& tag() const;

    MetaElement();
    MetaElement(const MetaElement& other);

  protected:
    history::AutomatonHistory<self_t>		history_;
  };

  template<typename S, typename St, typename T>
  St& op_rout(const AutomataBase<S>& s, St& st, const T& r);
      
}

# include <vaucanson/automata/concept/automata_base.hxx>

#endif
