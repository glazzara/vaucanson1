// manylinks_states.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef AUTOMATA_MANYLINKS_STATES_HH
# define AUTOMATA_MANYLINKS_STATES_HH

# include <vaucanson/config/system.hh>
# include <iterator>
# include <vaucanson/automata/concrete/manylinks_edges.hh>

namespace vcsn {

  enum state_link_type { st_global = 0, st_final = 1, st_initial = 2 };

  /*------.
  | state |
  `------*/
  template<typename StateTag, typename EdgeTag, typename Label>
  class ManyLinksState
  {
  public:
    typedef ManyLinksEdge<ManyLinksState<StateTag, EdgeTag, Label>, EdgeTag, Label> edge_t;

    ManyLinksState(unsigned index, ManyLinksState* root)
      : mark_(0),
	index_(index),
	counters_(root->counters_)
    {
      initialize(root);

      ++(*counters_)[st_global];
    }

    ~ManyLinksState()
    {
      edge_t *e;
      edge_t *p;
      for (e = mark_.next(co_in); e != &mark_; e = p)
	{
	  p = e->next(co_in);
	  delete e;
	}
      for (e = mark_.next(co_out); e != &mark_; e = p)
	{
	  p = e->next(co_out);
	  delete e;
	}

      assert(mark_.next(co_in) == mark_.prev(co_in));
      assert(mark_.next(co_in) == &mark_);
      assert(mark_.next(co_out) == mark_.prev(co_out));
      assert(mark_.next(co_out) == &mark_);

      // unlink from the states lists
      // assert((*counters_)[st_global] != 0);
      --(*counters_)[st_global];

      if (is_special(st_initial))
	{
	  assert((*counters_)[st_initial] != 0);
	  --(*counters_)[st_initial];
	}
      if (is_special(st_final))
	{
	  assert((*counters_)[st_final] != 0);
	  --(*counters_)[st_final];
	}

      for (int i = 0; i < 3; ++i)
	{
	  ManyLinksState *before = prev_[i];
	  ManyLinksState *after = next_[i];
	  before->next_[i] = after;
	  after->prev_[i] = before;
	}

    }


    edge_t* mark()
    { return & mark_; }

    const edge_t* mark() const
    { return & mark_; }


    StateTag& tag() { return tag_; }
    const StateTag& tag() const { return tag_; }
    
    unsigned index() const { return index_; }
    void set_index(unsigned j) { index_ = j; }


    ManyLinksState* next(state_link_type k) const { return next_[k]; }
    ManyLinksState* prev(state_link_type k) const { return prev_[k]; }
    
//     void set_next(state_link_type k, ManyLinksState* p) { next_[k] = p; }
//     void set_prev(state_link_type k, ManyLinksState* p) { prev_[k] = p; }

    void set_special(state_link_type k, ManyLinksState* root)
    {
      // we must check whether this state is already initial/final
      if (prev_[k] == this)
	{
	  ManyLinksState* before = root;
	  ManyLinksState* after = root->next_[k];
	  before->next_[k] = this;
	  after->prev_[k] = this;
	  prev_[k] = before;
	  next_[k] = after;
	  ++(*counters_)[k];
	}
    }
	  
    void clear_special(state_link_type k) 
    {
      ManyLinksState *before = prev_[k];
      ManyLinksState *after = next_[k];
      before->next_[k] = after;
      after->prev_[k] = before;
      prev_[k] = next_[k] = this;

      assert((*counters_)[k] != 0);
      --(*counters_)[k];
    }

    bool is_special(state_link_type k) const
    {
      return prev_[k] != this;
    }

    // for initialization purposes only
    ManyLinksState(size_t (*counters)[3])
      : mark_(0), counters_(counters)
    {
      for (int i = 0; i < 3; ++i)
	next_[i] = prev_[i] = this;
    }

  protected:

    void initialize(ManyLinksState* root)
    {
      ManyLinksState* before = root;
      ManyLinksState* after = root->next_[st_global];
      before->next_[st_global] = this;
      after->prev_[st_global] = this;
      prev_[st_global] = before;
      next_[st_global] = after;

      prev_[st_initial] = next_[st_initial] = 
      prev_[st_final] = next_[st_final] = this;
    }

    ManyLinksState* next_[3];
    ManyLinksState* prev_[3];
    edge_t mark_;

    unsigned index_;
    size_t (*counters_)[3];

    StateTag tag_;

  };


  /*---------------.
  | State iterator |
  `---------------*/
  template<typename State, state_link_type kind>
  class state_iterator /* : public std::iterator<std::bidirectional_iterator_tag,
					     unsigned,
					     ptrdiff_t,
					     const unsigned*,
					     const unsigned&> */
  {
  public:
    
    state_iterator() : p_(0) {}
    state_iterator(const state_iterator& other)
      : p_(other.p_) 
    {}

    unsigned operator*() const { return p_->index(); }

    state_iterator& operator++()
    {
      p_ = p_->next(kind);
      return *this;
    }

    state_iterator& operator--()
    {
      p_ = p_->prev(kind);
      return *this;
    }

    state_iterator operator++(int)
    {
      state_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    state_iterator operator--(int)
    {
      state_iterator tmp(*this);
      --(*this);
      return tmp;
    }

    // not for public use:

    explicit state_iterator(const State* s)
      : p_(s)
    {}
    const State* target() const
    { return p_; }


  protected:
    const State *p_;
  };
}

namespace vcsn {

#define STATE_ITERATOR_OP(Op)							\
template<typename State, vcsn::state_link_type k>				\
static inline bool operator Op (const vcsn::state_iterator<State, k>& a,	\
				const vcsn::state_iterator<State, k>& b)	\
{ 										\
  return a.target() Op b.target(); 						\
}

STATE_ITERATOR_OP(==);
STATE_ITERATOR_OP(!=);
STATE_ITERATOR_OP(<);
STATE_ITERATOR_OP(>);
STATE_ITERATOR_OP(<=);
STATE_ITERATOR_OP(>=);

#undef STATE_ITERATOR_OP

}

#endif
