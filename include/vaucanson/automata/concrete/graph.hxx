// graph.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey 
// and Regis-Gianas.
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

#ifndef VCSN_AUTOMATA_CONCRETE_GRAPH_HXX
# define VCSN_AUTOMATA_CONCRETE_GRAPH_HXX

# include <vaucanson/automata/concrete/graph.hh>
# include <vaucanson/misc/contract.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  template <class EdgeLabel>
  inline
  edge_value<EdgeLabel>::edge_value()
  {}

  template <class EdgeLabel>
  inline
  edge_value<EdgeLabel>::edge_value(const EdgeLabel& label, 
				    hstate_t from, 
				    hstate_t to):
    label(label),
    from(from),
    to(to)
  {
  }

  // Convenient macros.
#define TParam					\
    template <					\
    class Kind,					\
    class WordValue,				\
    class WeightValue,				\
    class SerieValue,				\
    class Letter,				\
    class Tag> 

#define GClass \
    Graph<Kind, WordValue, WeightValue, SerieValue, Letter, Tag>

  TParam
  inline
  GClass::Graph()
  {
    first_state_ = 0;
    first_edge_ = 0;
  }

  TParam
  inline
  hstate_t GClass::add_state()
  {
    // case 1: there is no empty cells in the chunk.
    if (removed_states_.size() == 0)
      {
	// case 1a: before the first used index.
	if (first_state_ > 0)
	  {
	    first_state_--;
	    return first_state_;
	  }
	// case 1b: after the last used index.
	states_.push_back(state_value_t());
	return states_.size() - 1;
      }

    // case 2: at least one empty cell, take the first.
    hstate_t n = *removed_states_.begin();
    removed_states_.erase(n);
    assertion(n < int(states_.size()));

    // make the associated data clean.
    states_[n].input_edges.clear();
    states_[n].output_edges.clear();
    states_[n].successors.clear();
    states_[n].predecessors.clear();
    
    postcondition(has_state(n));
    return n;
  }

  TParam
  inline 
  void GClass::del_state(hstate_t n)
  {
    assertion(has_state(n));
    // this assertion is not critical.
    if (!has_state(n))
      return;

    // remove linked edges.
    std::list<hedge_t> edges = states_[n].input_edges;
    for_each_const_(std::set<hedge_t>, e, edges)
      this->del_edge(*e);
    edges = states_[n].output_edges;
    for_each_const_(std::list<hedge_t>, e, edges)
      this->del_edge(*e);

    // remove in the initial and final applications.
    initial_.erase(n);
    final_.erase(n);

    // add the cell to empty data.
    removed_states_.insert(n);

    // states_.size() - 1 must always be used.
    // (invariant)
    if (n == int(states_.size() - 1))
      {
	int s = states_.size() - 1;
	while ((removed_states_.find(s) != removed_states_.end()) &&
	       s >= first_state_)
	  {
	    removed_states_.erase(s);
	    --s;
	  }
	states_.resize(s + 1);
      }
    assertion(states().size() == 0 || has_state(states_.size() - 1));

    // first_state_ must always be used.
    // (invariant)
    if (n == first_state_)
      {
	int s = first_state_;
	while ((removed_states_.find(s) != removed_states_.end()) &&
	       s < int(states_.size()))
	  {
	    removed_states_.erase(s);
	    ++s;
	  }
	first_state_ = s;
      }
    assertion(states().size() == 0 || has_state(first_state_)); 

    postcondition(! has_state(n));
  }

  TParam
  inline
  void 
  GClass::del_edge(hedge_t e)
  {
    assertion(has_edge(e));
    // this assertion is not critical:
    if (!has_edge(e))
      return;

    const edge_value_t& ev = edges_[e];

    // remove reference to this edge in linked states.
    states_[ev.from].successors.remove(ev.to);
    states_[ev.from].output_edges.remove(e);
    states_[ev.to].predecessors.remove(ev.from);
    states_[ev.to].input_edges.remove(e);
    removed_edges_.insert(e);

    // edges_.size() - 1 must be used.
    if (e == int(edges_.size() - 1))
      {
	int s = edges_.size() - 1;
	while ((removed_edges_.find(s) != removed_edges_.end()) &&
	       s >= 0)
	  {
	    removed_edges_.erase(s);
	    --s;
	  }
	edges_.resize(s + 1);
      }
    assertion(int(edges_.size()) == first_edge_ 
	      || has_edge(edges_.size() - 1));

    // first_edge_ must be used.
    if (e == first_edge_)
      {
	int s = first_edge_;
	while ((removed_edges_.find(s) != removed_edges_.end()) &&
	       s < int(edges_.size()))
	  {
	    removed_edges_.erase(s);
	    ++s;
	  }
	first_edge_ = s;
      }
    assertion(int(edges_.size()) == first_edge_ || has_edge(first_edge_));

    postcondition(! has_edge(e));
  }

  TParam
  inline
  bool
  GClass::has_state(hstate_t n) const
  {
    bool ret = 
      (n >= first_state_ &&
       removed_states_.find(n) == removed_states_.end())
      && (n >= 0) && (n < int(states_.size()));

    // if the index is not used, check that there is no
    // reference to it.
    if (ret == false)
      {
	for (int i = first_edge_; i < int(edges_.size()); ++i)
	  if (removed_edges_.find(hedge_t(i)) == removed_edges_.end())
	    {
	      assertion (((edges_[i].from != n) &&
			  (edges_[i].to != n)));
	    }

      }
    return ret;
  }

  TParam
  inline
  hedge_t
  GClass::add_edge(hstate_t n1, hstate_t n2, const label_t& l)
  {
    precondition(has_state(n1) && has_state(n2));

    hedge_t e;
    // case 1: no empty cell in the chunk.
    if (removed_edges_.size() == 0)
      {
	// case 1a: cells before first_edge_ are not used.
	if (first_edge_ > 0)
	  {
	    first_edge_--;
	    e = first_edge_;
	  }
	else
	  {
	    edges_.push_back(edge_value_t(l, n1, n2));
	    e = edges_.size() - 1;
	  }
      }
    // case 2: empty cells found in the chunk.
    else
      {
	e = *removed_edges_.begin();
	removed_edges_.erase(e);
	assertion(e < int(edges_.size()));
      }

    edges_[e].from = n1;
    edges_[e].to   = n2;
    edges_[e].label = l;
    if (std::find(states_[n1].output_edges.begin(),
		  states_[n1].output_edges.end(),
		  e) == states_[n1].output_edges.end())
      states_[n1].output_edges.push_back(e);
    if (std::find(states_[n2].input_edges.begin(),
		  states_[n2].input_edges.end(),
		  e) == states_[n2].input_edges.end())
      states_[n2].input_edges.push_back(e);
    if (std::find(states_[n2].predecessors.begin(),
		  states_[n2].predecessors.end(),
		  e) == states_[n2].predecessors.end())
      states_[n2].predecessors.push_back(n1);
    if (std::find(states_[n1].successors.begin(),
		  states_[n1].successors.end(),
		  e) == states_[n1].successors.end())
      states_[n1].successors.push_back(n2);

    postcondition(has_edge(e));
    return e;
  }

  TParam
  inline
  bool
  GClass::has_edge(hedge_t e) const
  {
    bool ret =
      (e >= first_edge_ &&
      ((std::find(removed_edges_.begin(), removed_edges_.end(), e)
	== removed_edges_.end())
       && (e < int(edges_.size()))));
    if (ret == false)
      {
	for (int i = first_state_; i < int(states_.size()); ++i)
	  if (std::find(removed_states_.begin(), removed_states_.end(),
			hstate_t(i))
	      == removed_states_.end())
	    {
	      postcondition(std::find(states_[i].input_edges.begin(),
				      states_[i].input_edges.end(),
				      e) ==
			    states_[i].input_edges.end());
	      postcondition(std::find(states_[i].output_edges.begin(),
				      states_[i].output_edges.end(),
				      e) ==
			    states_[i].output_edges.end());
	    }
      }
    return ret;
  }

  TParam
  inline
  hstate_t
  GClass::aim_of(hedge_t e) const
  {
    precondition(has_edge(e));
    return edges_[e].to;
  }

  TParam
  inline
  hstate_t
  GClass::origin_of(hedge_t e) const
  {
    precondition(has_edge(e));
    return edges_[e].from;
  }

  TParam
  inline
  const typename GClass::label_t&
  GClass::label_of(hedge_t e) const
  {
    precondition(has_edge(e));
    return edges_[e].label;
  }

  TParam
  inline
  typename GClass::states_t
  GClass::states() const
  {
    return states_t(hstate_t(first_state_), 
		    hstate_t(states_.size()) - 1,
		    removed_states_);
  }

  TParam
  inline
  typename GClass::edges_t
  GClass::edges() const
  {
    return edges_t(hedge_t(first_edge_), 
		   hedge_t(edges_.size()) - 1, 
		   removed_edges_);
  }

  TParam
  inline
  const typename GClass::serie_value_t&
  GClass::get_initial(hstate_t n, const serie_value_t& z) const
  {
    typename initial_t::const_iterator i = initial_.find(n);
    if (i == initial_.end())
      return z;
    return i->second;
  }

  TParam
  inline
  void
  GClass::set_initial(hstate_t n, const serie_value_t& v, 
		      const serie_value_t& z)
  {
    if (z == v)
      initial_.erase(n);
    else
      initial_[n] = v;
  }

  TParam
  inline
  const typename GClass::serie_value_t&
  GClass::get_final(hstate_t n, const serie_value_t& z) const
  {
    typename final_t::const_iterator i = final_.find(n);
    if (i == final_.end())
      return z;
    return i->second;
  }

  TParam
  inline
  void
  GClass::set_final(hstate_t n, const serie_value_t& v, 
		    const serie_value_t& z)
  {
    if (v == z)
      final_.erase(n);
    else
      final_[n] = v;
  }

  TParam
  inline
  void
  GClass::clear_final()
  {
    return final_.clear();
  }

  TParam
  inline
  void
  GClass::clear_initial()
  {
    return initial_.clear();
  }

  TParam
  inline
  typename GClass::initial_support_t
  GClass::initial() const
  {
    return initial_support_t(initial_);
  }

  TParam
  inline
  typename GClass::final_support_t
  GClass::final() const
  {
    return final_support_t(final_);
  }

  TParam
  inline
  void
  GClass::update(hedge_t e, label_t l)
  {
    edges_[e].label = l;
  }

  TParam
  template <class OutputIterator, class Query>
  inline
  void
  GClass::delta(OutputIterator res, 
		hstate_t from,
		const Query& q,
		delta_kind::edges) const
  {
    const std::list<hedge_t>& edges = states_[from].output_edges;
    for_each_const_(std::list<hedge_t>, e, edges)
      if (q(*e))
	*res++ = *e;
  }

  TParam
  template <class OutputIterator, class Query>
  inline
  void
  GClass::delta(OutputIterator res, 
		hstate_t from,
		const Query& query,
		delta_kind::states) const
  {
    const std::list<hedge_t>& edges = states_[from].output_edges;
    for_each_const_(std::list<hedge_t>, e, edges)
      if (query(*e))
	*res++ = edges_[*e].to;
  }

  TParam
  template <class OutputIterator, class Query>
  inline
  void
  GClass::rdelta(OutputIterator res, 
		 hstate_t from,
		 const Query& q,
		 delta_kind::edges) const
  {
    const std::list<hedge_t>& edges = states_[from].input_edges;
    for_each_const_(std::list<hedge_t>, e, edges)
      if (q(*e))
      {
	*res = *e;
	++res;
      }
  }

  TParam
  template <class OutputIterator, class Query>
  inline
  void
  GClass::rdelta(OutputIterator res, 
		 hstate_t from,
		 const Query& q,
		 delta_kind::states) const
  {
    const std::list<hedge_t>& edges = states_[from].input_edges;
    for_each_const_(std::list<hedge_t>, e, edges)
      if (q(*e))
      {
	*res = edges_[*e].from;
	++res;
      }
  }

  // Remove macros to avoid name clashes.
#undef TParam
#undef GClass

} // vcsn

#endif // VCSN_AUTOMATA_CONCRETE_GRAPH_HXX
