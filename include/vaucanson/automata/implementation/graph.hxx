// graph.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//    * Michael Cadilhac <michael.cadilhac@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_GRAPH_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_GRAPH_HXX

# include <fstream>
# include <sstream>

# include <algorithm>
# include <utility>

# include <vaucanson/automata/implementation/graph.hh>
# include <vaucanson/misc/contract.hh>


namespace vcsn
{

  /*---------------------------.
  | Decorators' implementation |
  `---------------------------*/

  template<typename EdgeLabel>
  edge_value<EdgeLabel>::edge_value(hstate_t h1,
				    hstate_t h2,
				    const EdgeLabel& l) :
    label(l),
    from(h1),
    to(h2)
  {}

  state_value::state_value()
  {}


  /*------------------.
  | Convenient macros |
  `------------------*/

# define TParam							\
  template <class Kind, class WordValue, class WeightValue,	\
	    class SeriesValue, class Letter, class Tag>

# define GClass							\
  Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag>


  /*-----------------------.
  | Graph's implementation |
  `-----------------------*/

  /*-------------.
  | Constructors |
  `-------------*/

  TParam
  GClass::Graph()
  { }

  TParam
  GClass::Graph
  (unsigned initial_number_of_state,
   unsigned reserve_number_of_edge)
  {
    states_.resize(initial_number_of_state);
    edges_.reserve(reserve_number_of_edge);
  }


  /*----------------.
  | Basic accessors |
  `----------------*/

  TParam
  typename GClass::states_t
  GClass::states() const
  {
    return states_t(hstate_t(0),
		    hstate_t(states_.size()) - 1,
		    removed_states_);
  }

  TParam
  typename GClass::edges_t
  GClass::edges() const
  {
    return edges_t(hedge_t(0),
		   hedge_t(edges_.size()) - 1,
		   removed_edges_);
  }

  TParam
  typename GClass::initial_support_t
  GClass::initial() const
  {
    return initial_support_t(initial_);
  }

  TParam
  typename GClass::final_support_t
  GClass::final() const
  {
    return final_support_t(final_);
  }

  /*---------------------.
  | State's manipulation |
  `---------------------*/

  TParam
  bool
  GClass::has_state(hstate_t n) const
  {
    bool res = ((removed_states_.find(n) == removed_states_.end())
		&& n >= 0
		&& n < int(states_.size()));
# ifndef VCSN_NDEBUG
    if (res == false)
      for (int i = 0; i < int(edges_.size()); ++i)
	if (removed_edges_.find(hedge_t(i)) == removed_edges_.end())
	  postcondition(edges_[i].from != n
			&& edges_[i].to != n);
# endif // !VCSN_NDEBUG
    return res;
  }

  TParam
  hstate_t
  GClass::add_state()
  {
    if (removed_states_.size() == 0)
    {
      states_.push_back(state_value_t());
      return states_.size() - 1;
    }

    hstate_t n = *removed_states_.begin();
    removed_states_.erase(n);
    assertion(n < int(states_.size()));

    states_[n].output_edges.clear();
    states_[n].input_edges.clear();

    postcondition(has_state(n));
    return n;
  }

  TParam
  void
  GClass::del_state(hstate_t n)
  {
    if (!has_state(n))
      return;

    const state_value_t& v = states_[n];
    state_value::edges_t::const_iterator e = v.output_edges.begin();
    state_value::edges_t::const_iterator end = v.output_edges.end();
    state_value::edges_t::const_iterator next = e;

    for (; e != end; e = next)
    {
      ++next;
      this->del_edge(*e);
    }

    e = v.input_edges.begin();
    end = v.input_edges.end();
    for (next = e; e != end; e = next)
    {
      ++next;
      this->del_edge(*e);
    }

    removed_states_.insert(n);
    initial_.erase(n);
    final_.erase(n);
    postcondition(!has_state(n));
  }

  TParam
  void
  GClass::set_initial(hstate_t n, const series_set_elt_value_t& v,
		      const series_set_elt_value_t& z)
  {
    if (z == v)
      initial_.erase(n);
    else
      initial_[n] = v;
  }

  TParam
  const typename GClass::series_set_elt_value_t&
  GClass::get_initial(hstate_t n, const series_set_elt_value_t& z) const
  {
    typename initial_t::const_iterator i = initial_.find(n);
    if (i == initial_.end())
      return z;
    return i->second;
  }

  TParam
  void
  GClass::clear_initial()
  {
    return initial_.clear();
  }

  TParam
  void
  GClass::set_final(hstate_t n, const series_set_elt_value_t& v,
		    const series_set_elt_value_t& z)
  {
    if (v == z)
      final_.erase(n);
    else
      final_[n] = v;
  }

  TParam
  const typename GClass::series_set_elt_value_t&
  GClass::get_final(hstate_t n, const series_set_elt_value_t& z) const
  {
    typename final_t::const_iterator i = final_.find(n);
    if (i == final_.end())
      return z;
    return i->second;
  }

  TParam
  void
  GClass::clear_final()
  {
    return final_.clear();
  }


  /*--------------------.
  | Edge's manipulation |
  `--------------------*/

  TParam
  bool
  GClass::has_edge(hedge_t e) const
  {
    bool res =(removed_edges_.find(e) == removed_edges_.end()
	       && (e < int(edges_.size())));
# ifndef VCSN_NDEBUG
    if (res == false)
      for (int i = 0; i < int(states_.size()); ++i)
	if (removed_states_.find(hstate_t(i)) == removed_states_.end())
	  postcondition(states_[i].output_edges.find(e) ==
			states_[i].output_edges.end());
# endif // !VCSN_NDEBUG
    return res;
  }

  TParam
  hedge_t
  GClass::add_edge(hstate_t n1, hstate_t n2,
		   const label_t& v)
  {
    precondition(has_state(n1));
    precondition(has_state(n2));
    std::pair<bool, hedge_t> edge;
    hedge_t e;
    if (removed_edges_.size() == 0)
    {
      edges_.push_back(edge_value_t(n1, n2, v));
      e = edges_.size() - 1;
    }
    else
    {
      e = *removed_edges_.begin();
      removed_edges_.erase(e);
      assertion(e < int(edges_.size()));
      edges_[e].from = n1;
      edges_[e].to = n2;
      edges_[e].label = v;
    }
    states_[n1].output_edges.insert(e);
    states_[n2].input_edges.insert(e);

    postcondition(has_edge(e));
    return e;
  }

  TParam
  void
  GClass::del_edge(hedge_t e)
  {
    if (!has_edge(e))
      return;

    const edge_value_t& ev = edges_[e];
    states_[ev.from].output_edges.erase(e);
    states_[ev.to].input_edges.erase(e);
    removed_edges_.insert(e);

    postcondition(!has_edge(e));
  }


  TParam
  hstate_t
  GClass::origin_of(hedge_t e1) const
  {
    precondition(has_edge(e1));
    return edges_[e1].from;
  }

  TParam
  hstate_t
  GClass::aim_of(hedge_t e2) const
  {
    precondition(has_edge(e2));
    return edges_[e2].to;
  }

  TParam
  const typename GClass::label_t&
  GClass::label_of(hedge_t n) const
  {
    precondition(has_edge(n));
    return edges_[n];
  }

  TParam
  void
  GClass::update(hedge_t e, label_t l)
  {
    precondition(has_edge(e));
    edges_[e].label = l;
  }


  /// Check the consistency of an automata.
  TParam
  template <class S>
  bool
  GClass::exists(const AutomataBase<S>& s) const
  {
    typename WordValue::iterator	it;
    typename label_t::const_iterator	r;
    label_t				l;
    WordValue				w;

    for (int i = 0; i < int(edges_.size()); ++i)
    {
      if (removed_edges_.find(hedge_t(i)) == removed_edges_.end())
	continue;
      // Make sure that origin and aim of edge are part of the automaton
      if (!has_state(aim_of(hedge_t(i))) ||
	  !has_state(origin_of(hedge_t(i))))
	return false;

      // Make sure that every letter of the edge is in the alphabet.
      l = label_of(hedge_t(i));
      for (r = l.begin(); r != l.end(); ++r)
      {
	w = r->first;
	for (it = w.begin(); it != w.end(); ++it)
	  if (!s.series().monoid().alphabet().contains(*it))
	    return false;
      }
    }
    return true;
  }

  /*----------------.
  | Delta functions |
  `----------------*/

  TParam
  template <class OutputIterator, class Query>
  void
  GClass::delta(OutputIterator res,
		hstate_t from,
		const Query& q,
		delta_kind::edges) const
  {
    assertion(has_state(from));
    const std::set<hedge_t>& edges = states_[from].output_edges;
    for_each_const_(std::set<hedge_t>, e, edges)
      if (q(*e))
	*res++ = *e;
  }

  TParam
  template <class OutputIterator, class Query>
  void
  GClass::delta(OutputIterator res,
		hstate_t from,
		const Query& query,
		delta_kind::states) const
  {
    assertion(has_state(from));
    const std::set<hedge_t>& edges = states_[from].output_edges;
    for_each_const_(std::set<hedge_t>, e, edges)
      if (query(*e))
	*res++ = edges_[*e].to;
  }

  TParam
  template <class OutputIterator, class Query>
  void
  GClass::rdelta(OutputIterator res,
		 hstate_t from,
		 const Query& q,
		 delta_kind::edges) const
  {
    assertion(has_state(from));
    const std::set<hedge_t>& edges = states_[from].input_edges;
    for_each_const_(std::set<hedge_t>, e, edges)
      if (q(*e))
	*res++ = *e;
  }

  TParam
  template <class OutputIterator, class Query>
  void
  GClass::rdelta(OutputIterator res,
		 hstate_t from,
		 const Query& q,
		 delta_kind::states) const
  {
    assertion(has_state(from));
    const state_value_t::edges_t& edges =
      states_[from].input_edges;
    for_each_const_(std::set<hedge_t>, e, edges)
      if (q(*e))
	*res++ = edges_[*e].from;
  }

  template <class S,
	    class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    typename  OutputIterator,
	    typename L>
  void op_rdelta(const AutomataBase<S>&,
		 const GClass& v,
		 OutputIterator res,
		 hstate_t from,
		 const L& query,
		 delta_kind::states k)
  {
    v.rdelta(res, from, query, k);
  }

  template <class S, class WordValue, class WeightValue, class SeriesValue,
	    class Letter, class Tag,
	    typename OutputIterator, typename L>
  void op_letter_delta(const AutomataBase<S>& s,
		       const Graph<labels_are_letters,
		       WordValue, WeightValue,
		       SeriesValue, Letter, Tag>& v,
		       OutputIterator res,
		       hstate_t from,
		       const L& letter,
		       delta_kind::states k)
  {
    typedef typename state_value::edges_t edges_t;
    const edges_t& edges = v.states_[from].output_edges;
    for_each_const_(edges_t, e, edges)
      if (v.edges_[*e].label == letter)
	*res++ = v.edges_[*e].to;
  }


  /*----.
  | Tag |
  `----*/

  TParam
  inline
  Tag& GClass::tag()
  {
    return tag_;
  }

  TParam
  const Tag& GClass::tag() const
  {
    return tag_;
  }

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
            class Letter, class Tag, class I>
  Tag& op_tag(const AutomataBase<I>&,
              Graph<Kind, WordValue, WeightValue,
                    SerieValue ,Letter, Tag>& v)
  {
    return v.tag();
  }

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
            class Letter, class Tag, class I>
  const Tag& op_tag(const AutomataBase<I>&,
                    const Graph<Kind, WordValue, WeightValue,
		                SerieValue ,Letter, Tag>& v)
  {
    return v.tag();
  }

  
  /*---------.
  | Geometry |
  `---------*/

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
	    class Letter, class Tag, class I>
  std::map<hstate_t, std::pair<double, double> >&
  op_geometry(const AutomataBase<I>&,
	      Graph<Kind, WordValue, WeightValue,
	      SerieValue, Letter, Tag>& v)
  {
    return v.geometry();
  }

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
            class Letter, class Tag, class I>
  const std::map<hstate_t, std::pair<double, double> >&
  op_geometry(const AutomataBase<I>&,
	      const Graph<Kind, WordValue, WeightValue,
	      SerieValue, Letter, Tag>& v)
  {
    return v.geometry();
  }

  
  TParam
  const typename GClass::geometry_map_t&
  GClass::geometry() const
  {
    return geometry_;
  }

  TParam
  typename GClass::geometry_map_t&
  GClass::geometry()
  {
    return geometry_;
  }
  
  
  // Remove macros to avoid name clashes.
#undef TParam
#undef GClass

}

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_GRAPH_HXX
