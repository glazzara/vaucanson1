// manylinks_edges.hh
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

#ifndef AUTOMATA_MANYLINKS_EDGES_HH
# define AUTOMATA_MANYLINKS_EDGES_HH

# include <vaucanson/config/system.hh>
# include <iterator>

namespace vcsn
{

  enum link_type { co_in = 0, co_out = 1, co_global = 2 };

  /*-----.
  | edge |
  `-----*/
  template<typename State, typename EdgeTag, typename Label>
  class ManyLinksEdge
  {
  public:
    typedef Label label_t;
    typedef EdgeTag tag_t;

    ManyLinksEdge(unsigned index, ManyLinksEdge* root, State* origin, State* aim, const Label& label)
      : index_(index), origin_(origin), aim_(aim), label_(label)
    {
      // first insert ourselves in the list of outgoing Edges
      // from the origin
      ManyLinksEdge *before = origin_->mark();
      ManyLinksEdge *after = before->next(co_out);

      set_prev(co_out, before);
      set_next(co_out, after);

      before->set_next(co_out, this);
      after->set_prev(co_out, this);

      // now insert ourselves in the list of ingoing Edge
      // to the aim
      before = aim_->mark();
      after = before->next(co_in);

      set_prev(co_in, before);
      set_next(co_in, after);

      before->set_next(co_in, this);
      after->set_prev(co_in, this);

      // finally insert ourselves in the global list
      initialize(root);

      ++*(counter_ = root->counter_);
    }

    ~ManyLinksEdge()
    {
      // now remove ourselves from the list of outgoing Edges
      ManyLinksEdge* before = prev_[co_out];
      ManyLinksEdge* after = next_[co_out];

      before->set_next(co_out, after);
      after->set_prev(co_out, before);

      // remove ourselves from the global list
      before = prev_[co_global];
      after = next_[co_global];
      
      before->set_next(co_global, after);
      after->set_prev(co_global, before);

      // finally remove ourselves from the list of incoming Edges
      before = prev_[co_in];
      after = next_[co_in];

      before->set_next(co_in, after);
      after->set_prev(co_in, before);

      if (counter_)
	{
	  assert(*counter_ != 0);
	  --*counter_;
	}
    }


    EdgeTag& tag() { return tag_; }
    const EdgeTag& tag() const { return tag_; }

    ManyLinksEdge* next(link_type t) const
    { return next_[t]; }

    ManyLinksEdge* prev(link_type t) const
    { return prev_[t]; }


    State* aim() const { return aim_; }
    State* origin() const { return origin_; }

    void set_aim(State *s) { aim_ = s; }
    void set_origin(State *s) { origin_ = s; }

    Label& label() { return label_; }
    const Label& label() const { return label_; }

    unsigned index() const { return index_; }
    void set_index(unsigned j) { index_ = j; }

    void set_next(link_type t, ManyLinksEdge* p)
    { next_[t] = p; }
    void set_prev(link_type t, ManyLinksEdge* p)
    { prev_[t] = p; }

    // for initialization purposes only
    ManyLinksEdge(size_t *counter)
      : counter_(counter)
    {
      set_prev(co_in, this);
      set_next(co_in, this);
      set_prev(co_out, this);
      set_next(co_out, this);
      set_prev(co_global, this);
      set_next(co_global, this);
     
      aim_ = 0;
      origin_ = 0;
    }

  protected:
    void initialize(ManyLinksEdge* root)
    {
      ManyLinksEdge* before = root;
      ManyLinksEdge* after = before->next(co_global);

      set_prev(co_global, before);
      set_next(co_global, after);

      before->set_next(co_global, this);
      after->set_prev(co_global, this);
    }

    unsigned	index_;

    State	*origin_;
    State	*aim_;
    Label	label_;

    ManyLinksEdge	*next_[3];
    ManyLinksEdge	*prev_[3];
    EdgeTag	tag_;

    size_t *counter_;

  };

  /*--------------.
  | Edge iterator |
  `--------------*/
  template<typename Edge>
  class edge_iterator /* : public iterator<bidirectional_iterator_tag,
					unsigned,
					ptrdiff_t,
					const unsigned*,
					const unsigned&> */
  {
  public:
    typedef typename Edge::label_t label_t;
    
    edge_iterator() : p_(0) {}
    edge_iterator(const edge_iterator& other)
      : p_(other.p_) 
    {}

    unsigned operator*() const { return p_->index(); }

    edge_iterator& operator++()
    {
      p_ = p_->next(co_global);
      return *this;
    }

    edge_iterator& operator--()
    {
      p_ = p_->prev(co_global);
      return *this;
    }

    edge_iterator operator++(int)
    {
      edge_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    edge_iterator operator--(int)
    {
      edge_iterator tmp(*this);
      --(*this);
      return tmp;
    }

    const label_t& label() const
    { return p_->label(); }

    unsigned aim() const
    { return p_->aim()->index(); }

    unsigned origin() const
    { return p_->origin()->index(); }


    // not for public use:

    explicit edge_iterator(const Edge* e)
      : p_(e)
    {}
    const Edge* target() const
    { return p_; }


  protected:
    const Edge *p_;
  };
}

namespace vcsn {

#define EDGE_ITERATOR_OP(Op)						\
template<typename Edge>							\
static inline bool operator Op (const vcsn::edge_iterator<Edge>& a,	\
				const vcsn::edge_iterator<Edge>& b)	\
{ return a.target() Op b.target(); }

EDGE_ITERATOR_OP(==);
EDGE_ITERATOR_OP(!=);
EDGE_ITERATOR_OP(<);
EDGE_ITERATOR_OP(>);
EDGE_ITERATOR_OP(<=);
EDGE_ITERATOR_OP(>=);


#undef EDGE_ITERATOR_OP

} // vcsn

#endif
