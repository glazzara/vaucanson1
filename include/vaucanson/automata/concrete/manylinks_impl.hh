// manylinks_impl.hh
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

#ifndef AUTOMATA_MANYLINK_IMPL_HH
#define AUTOMATA_MANYLINK_IMPL_HH

#include <vaucanson/automata/manylinks_edges.hh>
#include <vaucanson/automata/manylinks_states.hh>

#include <vector>
#include <stack>

namespace vcsn
{

  template<typename StateTag, typename EdgeTag, typename Label>
  class StatesCarrier
  {
  public:
    typedef State<StateTag, EdgeTag, Label> state_t;
    typedef state_iterator<state_t> const_iterator;

    StatesCarrier()
      : state_count(0),
        root_(& state_count)
    {
      root_.set_next( &state_root);
      root_.set_prev( &state_root);
    }

    const_iterator begin() const
    { return const_iterator(root_.next()); }

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

    const_iterator alloc(unsigned i) const
    {
      if (i >= state_map_.size())
	state_map_.resize(i + 1, 0);

      assert(state_map_[i] == 0);
      return const_iterator(state_map_[i] = new state_t(i, & root_));
    }

    const_iterator alloc() const
    {
      unsigned idx = 0;

      if (! state_count)
	state_map_.resize(10 /* arbitrary */, 0);
      else
	if (! free_states_.empty())
	  {
	    idx = free_states_.top();
	    free_states_.pop();
	  }
	else
	  {
	    for (idx = 0; 
		 idx < state_map_.size() &&
		   state_map_[idx] != 0;
		 ++idx);
	    if (idx == state_map_.size())
	      state_map_.resize(state_map_.size() * 2, 0);
	  }

      assert(state_map_[idx] == 0);
      return const_iterator(state_map_[idx] = new state_t(idx, & root));
    }

    void erase(const_iterator i)
    {
      unsigned idx = *i;

      assert(state_map_[idx] != 0);

      free_states_.push(idx);
      delete state_map_[idx];
      state_map_[idx] = 0;
    }

    size_t size() const 
    { return state_count_; }

    // for edge maintenance purposes only:
    
    state_t* state_at(unsigned i) const
    { return state_map_[i]; }

    ~StatesCarrier()
    {
      state_t* s;

      for (state_t* p = root_.next();
	   p != & root_;
	   p = s)
	{
	  s = p->next();
	  delete p;
	}
    }
    
  protected:

    size_t state_count;

    std::stack<unsigned> free_states_;
    std::vector<state_t*> state_map_;

    state_t root_;
  };


  template<typename State, typename EdgeTag, typename Label>
  class EdgesCarrier
  {
  public:
    typedef State<StateTag, EdgeTag, Label> state_t;
    typedef Edge<State, EdgeTag, Label> edge_t;
    typedef edge_iterator<edge_t> const_iterator;

    EdgesCarrier()
      : edge_count(0),
	root_(& edge_count)
    { 
      root_.set_next(co_global, &root_);
      root_.set_prev(co_global, &root_);
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


    ~EdgesCarrier()
    {
      edge_t* e;
      
      for (edge_t* p = root_.next(co_global);
	   p != & root_;
	   p = e)
	{
	  e = p->next(co_global);
	  delete p;
	}
    }

    const_iterator alloc(unsigned i, 
			 state_t* org, state_t* aim,
			 const Label& l) const
    {
      if (i >= edge_map_.size())
	edge_map_.resize(i + 1, 0);

      assert(edge_map_[i] == 0);
      return const_iterator(edge_map_[i] = new edge_t(i, & root_, org, aim, l));
    }

    const_iterator alloc(state_t* org, state_t* aim, const Label& l) const
    {
      unsigned idx = 0;

      if (! edge_count)
	edge_map_.resize(10 /* arbitrary */, 0);
      else
	if (! free_edges_.empty())
	  {
	    idx = free_edges_.top();
	    free_edges_.pop();
	  }
	else
	  {
	    for (idx = 0; 
		 idx < edge_map_.size() &&
		   edge_map_[idx] != 0;
		 ++idx);
	    if (idx == edge_map_.size())
	      edge_map_.resize(edge_map_.size() * 2, 0);
	  }

      assert(edge_map_[idx] == 0);
      return const_iterator(edge_map_[idx] = new edge_t(idx, & root, org, aim, l));
    }

    void erase(const_iterator i)
    {
      unsigned idx = *i;

      assert(edge_map_[idx] != 0);

      free_edges_.push(idx);
      delete edge_map_[idx];
      edge_map_[idx] = 0;
    }

    size_t size() const
    { return edge_count; }

  protected:
    size_t edge_count;

    std::stack<unsigned> free_edges_;
    
    std::vector<edge_t*> edge_map_;

    edge_t root_;
  }
 
  template<typename Label, typename StateTag, typename EdgeTag>
  class ManyLinks
  {
  public:
    typedef StatesCarrier<StateTag, EdgeTag, Label> states_t;
    typedef State<StateTag, EdgeTag, Label> state_t;
    typedef EdgesCarrier<state_t, EdgeTag, Label> edges_t;

    ManyLinks()
    {}

    ManyLinks(const ManyLinks& other)
    {
      for (typename states_t::const_iterator i = other.states_.begin();
	   i != other.states_.end();
	   ++i)
	states_.alloc(*i);

      for (typename edges_t::const_iterator i = other.edges_.begin();
	   i != other.edges_.end();
	   ++i)
	edges_.alloc(*i, 
		     states_.state_at(i->origin()), 
		     states_.state_at(i->aim()),
		     i->label());
    }

    states_t& states() { return states_; }
    const states_t& states() const { return states_; }
    

    edges_t& edges() { return edges_; }
    const edges_t& edges() const { return edges_; }

  protected:
    states_t states_;
    edges_t edges_;

  };



}


#endif
