// manylinks_carriers.hh
//
// $Id$
// VCSN_HEADER
#ifndef AUTOMATA_MANYLINK_CARRIERS_HH
# define AUTOMATA_MANYLINK_CARRIERS_HH

#include <vector>
#include <stack>

#include <vaucanson/automata/concrete/manylinks_edges.hh>
#include <vaucanson/automata/concrete/manylinks_states.hh>

// FIXME: move implementations to a .hxx file

namespace vcsn
{

  /*-----------------.
  | States container |
  `-----------------*/

  template<typename StateTag, typename EdgeTag, typename Label>
  class ManyLinksStatesCarrier
  {
  public:
    typedef ManyLinksState<StateTag, EdgeTag, Label>    state_t;
    typedef state_iterator<state_t, st_global>		const_iterator;

    ManyLinksStatesCarrier()
      : root_(&state_counts_)
    {
      for (int i = 0; i < 3; ++i)
	state_counts_[i] = 0;
    }

    const_iterator begin() const
    { return const_iterator(root_.next(st_global)); }

    const_iterator end() const
    { return const_iterator(& root_); }

    const_iterator find(unsigned i) const
    { 
      const state_t *s;

      if (i >= state_map_.size() || 
	  ! (s = state_map_[i]))
	return const_iterator(& root_);

      return const_iterator(s);
    }

    const_iterator operator[](unsigned i) const
    { return const_iterator(state_map_[i]); }

    const_iterator alloc(unsigned i) 
    {
      if (i >= state_map_.size())
	state_map_.resize(i + 1, (state_t*)0);

      assert(state_map_[i] == 0);
      return const_iterator(state_map_[i] = new state_t(i, & root_));
    }

    void collect_free_slots()
    {
      while(!free_states_.empty())
	free_states_.pop();
      for (unsigned idx = 0; idx < state_map_.size(); ++idx)
	if (! state_map_[idx])
	  free_states_.push(idx);
    }


    const_iterator alloc() 
    {
      unsigned idx = 0;

      if (! state_counts_[st_global])
	{
	  while(!free_states_.empty())
	    free_states_.pop();
	  state_map_.resize(1, 0);
	}
      else
	if (! free_states_.empty())
	  {
	    idx = free_states_.top();
	    free_states_.pop();
	  }
	else
	  {
	    idx = state_map_.size();
	    state_map_.resize(state_map_.size() + 1, 0);
	  }

      assert(state_map_[idx] == 0);
      return const_iterator(state_map_[idx] = new state_t(idx, & root_));
    }

    void erase(const_iterator i)
    { erase(*i); }

    void erase(unsigned idx)
    {
      assert(state_map_[idx] != 0);

      free_states_.push(idx);
      delete state_map_[idx];
      state_map_[idx] = 0;
    }


    size_t size(state_link_type k = st_global) const 
    { return state_counts_[k]; }

    bool empty() const
    { return ! state_count_[st_global]; }

    // for edge maintenance purposes only:
    
    state_t* state_at(unsigned i) const
    { return state_map_[i]; }

    ~ManyLinksStatesCarrier()
    {
      state_t* s;

      for (state_t* p = root_.next(st_global);
	   p != & root_;
	   p = s)
	{
	  s = p->next(st_global);
	  delete p;
	}

      for(int i = 0; i < 3; ++i)
	{
	  assert(state_counts_[i] == 0);
	  state_counts_[i] = 1; /* for deletion of root_; */
	}
    }

    // this is not for public use AT ALL:
    state_t& root() { return root_; }
    const state_t& root() const { return root_; }
    
  protected:

    size_t state_counts_[3];

    std::stack<unsigned> free_states_;
    std::vector<state_t*> state_map_;

    state_t root_;
  };


  /*----------------.
  | Edges container |
  `----------------*/

  template<typename State, typename EdgeTag, typename Label>
  class ManyLinksEdgesCarrier
  {
  public:
    typedef State state_t;
    typedef ManyLinksEdge<state_t, EdgeTag, Label> edge_t;
    typedef edge_iterator<edge_t> const_iterator;

    ManyLinksEdgesCarrier()
      : edge_count(0),
	root_(& edge_count)
    { 
      root_.set_next(co_global, &root_);
      root_.set_prev(co_global, &root_);
      root_.set_next(co_in, &root_);
      root_.set_prev(co_in, &root_);
      root_.set_next(co_out, &root_);
      root_.set_prev(co_out, &root_);
    }

    const_iterator begin() const
    { return const_iterator(root_.next(co_global)); }

    const_iterator end() const
    { return const_iterator(& root_); }

    const_iterator find(unsigned i) const
    { 
      const edge_t *e;

      if (i >= edge_map_.size() || 
	  ! (e = edge_map_[i]))
	return const_iterator(& root_);

      return const_iterator(e);
    }

    const_iterator operator[](unsigned i) const
    { return const_iterator(edge_map_[i]); }


    ~ManyLinksEdgesCarrier()
    {
      edge_t* e;
      
      for (edge_t* p = root_.next(co_global);
	   p != & root_;
	   p = e)
	{
	  e = p->next(co_global);
	  delete p;
	}
      assert(edge_count == 0);
      edge_count = 1; /* for deletion of root_ */
    }

    const_iterator alloc(unsigned i, 
			 state_t* org, state_t* aim,
			 const Label& l) 
    {
      if (i >= edge_map_.size())
	edge_map_.resize(i + 1, (edge_t*)0);

      assert(edge_map_[i] == 0);
      return const_iterator(edge_map_[i] = new edge_t(i, & root_, org, aim, l));
    }

    void collect_free_slots()
    {
      while(!free_edges_.empty())
	free_edges_.pop();
      for (unsigned idx = 0; idx < edge_map_.size(); ++idx)
	if (! edge_map_[idx])
	  free_edges_.push(idx);
    }

    const_iterator alloc(state_t* org, state_t* aim, const Label& l) 
    {
      unsigned idx = 0;

      if (! edge_count)
	{
	  while (!free_edges_.empty())
	    free_edges_.pop();
	  edge_map_.resize(1, 0);
	}
      else
	if (! free_edges_.empty())
	  {
	    idx = free_edges_.top();
	    free_edges_.pop();
	  }
	else
	  {
	    idx = edge_map_.size();
	    edge_map_.resize(edge_map_.size() + 1, 0);
	  }

      assert(edge_map_[idx] == 0);
      return const_iterator(edge_map_[idx] = new edge_t(idx, & root_, org, aim, l));
    }

    void erase(const_iterator i)
    { erase(*i); }

    void erase(unsigned idx)
    {
      assert(edge_map_[idx] != 0);

      free_edges_.push(idx);
      delete edge_map_[idx];
      edge_map_[idx] = 0;
    }

    size_t size() const
    { return edge_count; }

    bool empty() const
    { return ! edge_count; }

  protected:
    size_t edge_count;

    std::stack<unsigned> free_edges_;
    
    std::vector<edge_t*> edge_map_;

    edge_t root_;
  };


  /*------------------.
  | Initial container |
  `------------------*/

  // what follows is simply horribly infamous. Beat me !
  template<typename StateTag, typename EdgeTag, typename Label>
  class ManyLinksInitialCarrier
  {
  protected:
    typedef ManyLinksStatesCarrier<StateTag, EdgeTag, Label> states_t;
    typedef ManyLinksState<StateTag, EdgeTag, Label> state_t;
  public:
    typedef state_iterator<state_t, st_initial> const_iterator;

    const_iterator begin() const
    { return const_iterator(root().next(st_initial)); }

    const_iterator end() const
    { return const_iterator(& root()); }

    const_iterator find(unsigned idx) const
    { 
      typename states_t::const_iterator i = states().find(idx);

      if (i == states().end() || ! i.target()->is_special(st_initial))
	return const_iterator(& root());

      return const_iterator(i.target());
    }

    void erase(const_iterator i)
    { erase(*i); }

    void erase(unsigned idx)
    {
      assert(states().find(idx) != states().end());

      typename states_t::state_t *p = states().state_at(idx);
      if (p->is_special(st_initial))
	p->clear_special(st_initial);

    }

    void insert(unsigned idx)
    {
      assert(states().find(idx) != states().end());

      states().state_at(idx)->set_special(st_initial, & root());
    }

    size_t size() const 
    { return states().size(st_initial); }

    bool empty() const
    { return ! states().size(st_initial); }

    // for maintenance purposes only:

    states_t& states() { return states_; }
    const states_t& states() const { return states_; }
    
    state_t& root() { return states_.root(); }
    const state_t& root() const { return states_.root(); }

  protected:

    states_t states_;
  };
  

  /*----------------.
  | final container |
  `----------------*/

  // more horror follows...
  template<typename StateTag, typename EdgeTag, typename Label>
  class ManyLinksFinalCarrier
  {
  protected:
    typedef ManyLinksStatesCarrier<StateTag, EdgeTag, Label> states_t;
    typedef ManyLinksInitialCarrier<StateTag, EdgeTag, Label> initial_t;
    typedef ManyLinksState<StateTag, EdgeTag, Label> state_t;
  public:
    typedef state_iterator<state_t, st_final> const_iterator;

    const_iterator begin() const
    { return const_iterator(root().next(st_final)); }

    const_iterator end() const
    { return const_iterator(& root()); }

    const_iterator find(unsigned idx) const
    { 
      typename states_t::const_iterator i = states().find(idx);

      if (i == states().end() || ! i.target()->is_special(st_final))
	return const_iterator(& root());

      return const_iterator(i.target());
    }

    void erase(const_iterator i)
    { erase(*i); }

    void erase(unsigned idx)
    {
      assert(states().find(idx) != states().end());
      typename states_t::state_t *p = states().state_at(idx);
      if (p->is_special(st_final))
	p->clear_special(st_final);
    }

    void insert(unsigned idx)
    {
      assert(states().find(idx) != states().end());

      states().state_at(idx)->set_special(st_final, & root());
    }

    size_t size() const 
    { return states().size(st_final); }

    bool empty() const
    { return ! states().size(st_final); }

    // for maintenance purposes only:

    states_t& states() { return initial_.states(); }
    const states_t& states() const { return initial_.states(); }
    
    initial_t& initial() { return initial_; }
    const initial_t& initial() const { return initial_; }

    state_t& root() { return initial_.root(); }
    const state_t& root() const { return initial_.root(); }

  protected:

    initial_t initial_;
  };
  

}


#endif
