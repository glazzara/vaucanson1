// manylinks.hh
//
// $Id$
// VCSN_HEADER
#ifndef AUTOMATA_MANYLINKS_HH
# define AUTOMATA_MANYLINKS_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concrete/manylinks_carriers.hh>

namespace vcsn
{
 
  template<typename Label, typename StateTag, typename EdgeTag>
  class ManyLinks
  {
  public:
    typedef ManyLinksStatesCarrier<StateTag, EdgeTag, Label>	states_t;
    typedef ManyLinksInitialCarrier<StateTag, EdgeTag, Label>	initial_t;
    typedef ManyLinksFinalCarrier<StateTag, EdgeTag, Label>	final_t;
    typedef ManyLinksState<StateTag, EdgeTag, Label>		state_t;
    typedef ManyLinksEdgesCarrier<state_t, EdgeTag, Label>	edges_t;
    typedef Label						label_t;

    ManyLinks()
    {}

    ManyLinks(const ManyLinks& other)
    {
      for (typename states_t::const_iterator i = other.states().begin();
	   i != other.states().end();
	   ++i)
	{
	  states().alloc(*i);
	  if (other.initial().find(*i) != other.initial().end())
	    initial().insert(*i);
	  if (other.final().find(*i) != other.final().end())
	    final().insert(*i);
	}
      states().collect_free_slots();

      for (typename edges_t::const_iterator i = other.edges().begin();
	   i != other.edges().end();
	   ++i)
	edges().alloc(*i, 
		     states().state_at(i.origin()), 
		     states().state_at(i.aim()),
		     i.label());
      
      edges().collect_free_slots();
    }

    states_t& states() { return final_.states(); }
    const states_t& states() const { return final_.states(); }
    
    edges_t& edges() { return edges_; }
    const edges_t& edges() const { return edges_; }

    final_t& final() { return final_; }
    const final_t& final() const { return final_; }

    initial_t& initial() { return final_.initial(); }
    const initial_t& initial() const { return final_.initial(); }

  protected:
    final_t final_;
    edges_t edges_;
  };


  template<typename L, typename S, typename E>
  struct automaton_traits<ManyLinks<L, S, E> >
  {
    typedef const ManyLinksStatesCarrier<S, E, L>& states_ret_t;
    typedef const ManyLinksInitialCarrier<S, E, L>& initial_ret_t;
    typedef const ManyLinksFinalCarrier<S, E, L>& final_ret_t;
    typedef const ManyLinksEdgesCarrier<ManyLinksState<S, E, L>,
					E, L>& edges_ret_t;
    typedef L label_ret_t;
  };

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  const ManyLinksStatesCarrier<StateTag, EdgeTag, Label>&
  auto_op_states(const Structure<S>& series,
		 const ManyLinks<Label, StateTag, EdgeTag>& impl)
  { return impl.states(); }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  const ManyLinksEdgesCarrier<ManyLinksState<StateTag, EdgeTag, Label>, EdgeTag, Label>&
  auto_op_edges(const Structure<S>& series,
		const ManyLinks<Label, StateTag, EdgeTag>& impl)
  { return impl.edges(); }
		 
  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  const ManyLinksInitialCarrier<StateTag, EdgeTag, Label>&
  auto_op_initial(const Structure<S>& series,
		 const ManyLinks<Label, StateTag, EdgeTag>& impl)
  { return impl.initial(); }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  const ManyLinksFinalCarrier<StateTag, EdgeTag, Label>&
  auto_op_final(const Structure<S>& series,
		 const ManyLinks<Label, StateTag, EdgeTag>& impl)
  { return impl.final(); }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  unsigned auto_op_add_state(const Structure<S>& series,
			     ManyLinks<Label, StateTag, EdgeTag>& impl)
  { 
    (void)(&series);
    return *impl.states().alloc(); 
  }


  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  unsigned auto_op_new_edge(const Structure<S>& series,
			    ManyLinks<Label, StateTag, EdgeTag>& impl,
			    unsigned from, unsigned to,
			    const Label& l)
  { 
    typedef typename ManyLinks<Label, StateTag, EdgeTag>::states_t states_t;
    const states_t& s = impl.states();

    return *impl.edges().alloc(s.state_at(from),
			      s.state_at(to),
			      l);
  }
			     
  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  unsigned auto_op_add_edge(const Structure<S>& series,
			    ManyLinks<Label, StateTag, EdgeTag>& impl,
			    unsigned from, unsigned to,
			    const Label& l)
  { 
    // FIXME: the behaviour should be different here

    return auto_op_new_edge(series, impl, from, to, l);
  }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_clear_initial(const Structure<S>& series,
			     ManyLinks<Label, StateTag, EdgeTag>& impl, unsigned s)
  { impl.initial().erase(s); }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_clear_final(const Structure<S>& series,
			   ManyLinks<Label, StateTag, EdgeTag>& impl, unsigned s)
  { impl.final().erase(s); }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_set_initial(const Structure<S>& series,
			     ManyLinks<Label, StateTag, EdgeTag>& impl, unsigned s)
  { impl.initial().insert(s); }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_set_final(const Structure<S>& series,
			 ManyLinks<Label, StateTag, EdgeTag>& impl, unsigned s)
  { impl.final().insert(s); }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_del_state(const Structure<S>& series,
			 ManyLinks<Label, StateTag, EdgeTag>& impl, unsigned s)
  { impl.states().erase(s); }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_del_edge(const Structure<S>& series,
			ManyLinks<Label, StateTag, EdgeTag>& impl, unsigned s)
  { impl.edges().erase(s); }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_safe_del_state(const Structure<S>& series,
			      ManyLinks<Label, StateTag, EdgeTag>& impl, unsigned s)
  { 
    // in our case it is the same as del_state, but this is possible
    // only because the destructor ~State takes care of everything.
    impl.states().erase(s); 
  }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  bool auto_op_has_state(const Structure<S>& series,
			 const ManyLinks<Label, StateTag, EdgeTag>& impl, unsigned s)
  { return impl.states().find(s) != impl.states().end(); }

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  bool auto_op_has_edge(const Structure<S>& series,
			const ManyLinks<Label, StateTag, EdgeTag>& impl, unsigned e)
  { return impl.edges().find(e) != impl.edges().end(); }





  template<typename S, typename Label, typename StateTag, typename EdgeTag, typename Iter>
  void auto_op_delta_states(const Structure<S>& series,
			    const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			    Iter out,
			    unsigned s)
  {
    typedef typename ManyLinks<Label, StateTag, EdgeTag>::state_t state_t;
    typedef ManyLinksEdge<state_t, EdgeTag, Label> edge_t;

    const state_t* p = impl.states().state_at(s);
    
    for (const edge_t* e = p->mark()->next(co_out);
	 e != p->mark();
	 e = e->next(co_out))
      *(out++) = e->aim()->index();
  }

  template<typename S, typename Label, typename StateTag, typename EdgeTag, typename Iter>
  void auto_op_delta_edges(const Structure<S>& series,
			   const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			   Iter out,
			   unsigned s)
  {
    typedef typename ManyLinks<Label, StateTag, EdgeTag>::state_t state_t;
    typedef ManyLinksEdge<state_t, EdgeTag, Label> edge_t;

    const state_t* p = impl.states().state_at(s);
    
    for (const edge_t* e = p->mark()->next(co_out);
	 e != p->mark();
	 e = e->next(co_out))
      *(out++) = e->index();
  }

  template<typename S, typename Label, typename StateTag, typename EdgeTag, typename Iter>
  void auto_op_rdelta_states(const Structure<S>& series,
			     const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			     Iter out,
			     unsigned s)
  {
    typedef typename ManyLinks<Label, StateTag, EdgeTag>::state_t state_t;
    typedef ManyLinksEdge<state_t, EdgeTag, Label> edge_t;

    const state_t* p = impl.states().state_at(s);
    
    for (const edge_t* e = p->mark()->next(co_in);
	 e != p->mark();
	 e = e->next(co_in))
      *(out++) = e->origin()->index();
  }

  template<typename S, typename Label, typename StateTag, typename EdgeTag, typename Iter>
  void auto_op_rdelta_edges(const Structure<S>& series,
			    const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			    Iter out,
			    unsigned s)
  {
    typedef typename ManyLinks<Label, StateTag, EdgeTag>::state_t state_t;
    typedef ManyLinksEdge<state_t, EdgeTag, Label> edge_t;

    const state_t* p = impl.states().state_at(s);
    
    for (const edge_t* e = p->mark()->next(co_in);
	 e != p->mark();
	 e = e->next(co_in))
      *(out++) = e->index();
  }





  template<typename S, typename Label, typename StateTag, typename EdgeTag, typename Iter, typename Q>
  void auto_op_delta_states(const Structure<S>& series,
			    const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			    Iter out,
			    unsigned s,
			    const Q& q)
  {
    typedef typename ManyLinks<Label, StateTag, EdgeTag>::state_t state_t;
    typedef ManyLinksEdge<state_t, EdgeTag, Label> edge_t;

    const state_t* p = impl.states().state_at(s);
    
    for (const edge_t* e = p->mark()->next(co_out);
	 e != p->mark();
	 e = e->next(co_out))
      if (q(e->label()))
	*(out++) = e->aim()->index();
  }

  template<typename S, typename Label, typename StateTag, typename EdgeTag, typename Iter, typename Q>
  void auto_op_delta_edges(const Structure<S>& series,
			   const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			   Iter out,
			   unsigned s,
			   const Q& q)
  {
    typedef typename ManyLinks<Label, StateTag, EdgeTag>::state_t state_t;
    typedef ManyLinksEdge<state_t, EdgeTag, Label> edge_t;

    const state_t* p = impl.states().state_at(s);
    
    for (const edge_t* e = p->mark()->next(co_out);
	 e != p->mark();
	 e = e->next(co_out))
      if (q(e->label()))
	*(out++) = e->index();
  }

  template<typename S, typename Label, typename StateTag, typename EdgeTag, typename Iter, typename Q>
  void auto_op_rdelta_states(const Structure<S>& series,
			     const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			     Iter out,
			     unsigned s,
			     const Q& q)
  {
    typedef typename ManyLinks<Label, StateTag, EdgeTag>::state_t state_t;
    typedef ManyLinksEdge<state_t, EdgeTag, Label> edge_t;

    const state_t* p = impl.states().state_at(s);
    
    for (const edge_t* e = p->mark()->next(co_in);
	 e != p->mark();
	 e = e->next(co_in))
      if (q(e->label()))
	*(out++) = e->origin()->index();
  }

  template<typename S, typename Label, typename StateTag, typename EdgeTag, typename Iter, typename Q>
  void auto_op_rdelta_edges(const Structure<S>& series,
			    const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			    Iter out,
			    unsigned s,
			    const Q& q)
  {
    typedef typename ManyLinks<Label, StateTag, EdgeTag>::state_t state_t;
    typedef ManyLinksEdge<state_t, EdgeTag, Label> edge_t;

    const state_t* p = impl.states().state_at(s);
    
    for (const edge_t* e = p->mark()->next(co_in);
	 e != p->mark();
	 e = e->next(co_in))
      if (q(e->label()))
	*(out++) = e->index();
  }
  
}

#endif
