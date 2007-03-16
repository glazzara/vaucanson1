// graph.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_GRAPH_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_GRAPH_HXX

# include <fstream>
# include <sstream>

# include <algorithm>
# include <utility>

# include <vaucanson/automata/implementation/graph.hh>
# include <vaucanson/misc/contract.hh>
# include <vaucanson/misc/static.hh>

namespace vcsn
{

  /*---------------------------.
  | Decorators' implementation |
  `---------------------------*/

  template<typename EdgeLabel>
  edge_value<EdgeLabel>::edge_value(hstate_t h1, hstate_t h2,
				    const EdgeLabel& l)
    : label(l),
      from(h1),
      to(h2)
  {}

  inline
  state_value::state_value()
  {}


  /*--------------------.
  | Convenient macros.  |
  `--------------------*/

# define TParam								\
  template <class Kind, class WordValue, class WeightValue,		\
	    class SeriesValue, class Letter, class Tag, class Geometry>

# define GClass								\
  Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag, Geometry>


  /*-------------------------.
  | Graph's implementation.  |
  `-------------------------*/

  /*---------------.
  | Constructors.  |
  `---------------*/

  TParam
  GClass::Graph()
  { }

  TParam
  GClass::Graph (unsigned initial_number_of_state,
		 unsigned reserve_number_of_edge)
  {
    states_.resize(initial_number_of_state);
    edges_.reserve(reserve_number_of_edge);
  }


  /*------------------.
  | Basic accessors.  |
  `------------------*/

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


  /*----------------------.
  | States manipulation.  |
  `----------------------*/

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
    precondition (has_state(n));

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


  /*---------------------.
  | Edges manipulation.  |
  `---------------------*/

  TParam
  bool
  GClass::has_edge(hedge_t e) const
  {
    bool res = (removed_edges_.find(e) == removed_edges_.end()
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
  GClass::src_of(hedge_t e1) const
  {
    precondition(has_edge(e1));
    return edges_[e1].from;
  }

  TParam
  hstate_t
  GClass::dst_of(hedge_t e2) const
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
      if (removed_edges_.find(hedge_t(i)) != removed_edges_.end())
	continue;
      // Make sure that source and destination of edge are part of the
      // automaton.
      if (!has_state(dst_of(hedge_t(i))) ||
	  !has_state(src_of(hedge_t(i))))
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

  /*------------------.
  | Delta functions.  |
  `------------------*/

  // Classical ones.

# define DEFINE_DELTA_FUNCTION(DeltaName, DKind, IO, WhatFromE)		\
  TParam								\
  template <class OutputIterator, class Query>				\
  void									\
  GClass::DeltaName(OutputIterator res,					\
		    hstate_t from,					\
		    const Query& query,					\
		    delta_kind::DKind) const				\
  {									\
    assertion(has_state(from));						\
    const std::set<hedge_t>& edges = states_[from].IO ## _edges;	\
    for_all_const_(std::set<hedge_t>, e, edges)				\
      if (query(*e))							\
	*res++ = WhatFromE;						\
  }									\

  DEFINE_DELTA_FUNCTION (delta, edges, output, *e);
  DEFINE_DELTA_FUNCTION (delta, states, output, edges_[*e].to);
  DEFINE_DELTA_FUNCTION (rdelta, edges, input, *e);
  DEFINE_DELTA_FUNCTION (rdelta, states, input, edges_[*e].from);

# undef DEFINE_DELTA_FUNCTION

  // Delta with functor.  Much more than the previous one, because
  // functor is statically checked for return type of its operator(),
  // and behave differently if it is bool: loop breaks if false is
  // returned.
# define DEFINE_DELTAF_FUNCTION(DeltaName, DKind, IO, IsBool, Action)	\
  TParam								\
  template <typename Functor, class Query>				\
  void									\
  GClass::DeltaName(Functor& fun,					\
		    hstate_t from,					\
		    const Query& query,					\
		    delta_kind::DKind,					\
		    misc::IsBool ## _t) const				\
  {									\
    assertion(has_state(from));						\
    const std::set<hedge_t>& edges = states_[from].IO ## _edges;	\
    for_all_const_(std::set<hedge_t>, e, edges)				\
      if (query(*e))							\
      { Action; }							\
  }

  DEFINE_DELTAF_FUNCTION (deltaf, states, output, true,
			  if (not fun(edges_[*e].to)) break);
  DEFINE_DELTAF_FUNCTION (deltaf, states, output, false, fun(edges_[*e].to));
  DEFINE_DELTAF_FUNCTION (deltaf, edges, output, true,
			  if (not fun(*e)) break);
  DEFINE_DELTAF_FUNCTION (deltaf, edges, output, false, fun(*e));

  DEFINE_DELTAF_FUNCTION (rdeltaf, states, input, true,
			  if (not fun(edges_[*e].from)) break);
  DEFINE_DELTAF_FUNCTION (rdeltaf, states, input, false, fun(edges_[*e].from));
  DEFINE_DELTAF_FUNCTION (rdeltaf, edges, input, true,
			  if (not fun(*e)) break);
  DEFINE_DELTAF_FUNCTION (rdeltaf, edges, input, false, fun(*e));

# undef DEFINE_DELTAF_FUNCTION

  // Helpers for static dispatch.
  namespace deltaf_helper {
    template <typename T, typename R, typename Arg>
    char is_returning_bool_helper (R (T::*) (Arg));

    template <typename T, typename Arg>
    int is_returning_bool_helper (bool (T::*) (Arg));

# define is_returning_bool(T)						\
    (sizeof (deltaf_helper::is_returning_bool_helper (T)) == sizeof (int))
  }

# define DEFINE_DELTAF_HELPER(DeltaName)				\
  TParam								\
  template <typename Functor, class Query, typename DKind>		\
  void									\
  GClass::DeltaName(Functor& fun,					\
		    hstate_t from,					\
		    const Query& query,					\
		    delta_kind::kind<DKind> k) const			\
  {									\
    DeltaName (fun, from, query, k,					\
	       BOOL_TO_TYPE (is_returning_bool (&Functor::operator ())) ()); \
  }

  DEFINE_DELTAF_HELPER (deltaf);
  DEFINE_DELTAF_HELPER (rdeltaf);

# undef DEFINE_DELTAF_HELPER
# undef is_returning_bool

  /*------.
  | Tag.  |
  `------*/

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
	    class Letter, class Tag, class Geometry, class I>
  Tag& op_tag(const AutomataBase<I>&,
	      Graph<Kind, WordValue, WeightValue,
	      SerieValue ,Letter, Tag, Geometry>& v)
  {
    return v.tag();
  }

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
	    class Letter, class Tag, class Geometry, class I>
  const Tag& op_tag(const AutomataBase<I>&,
		    const Graph<Kind, WordValue, WeightValue,
		    SerieValue ,Letter, Tag, Geometry>& v)
  {
    return v.tag();
  }


  /*-----------.
  | Geometry.  |
  `-----------*/

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
	    class Letter, class Tag, class Geometry, class I>
  Geometry&
  op_geometry(const AutomataBase<I>&,
	      Graph<Kind, WordValue, WeightValue,
	      SerieValue, Letter, Tag, Geometry>& v)
  {
    return v.geometry();
  }

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
	    class Letter, class Tag, class Geometry, class I>
  const Geometry&
  op_geometry(const AutomataBase<I>&,
	      const Graph<Kind, WordValue, WeightValue,
	      SerieValue, Letter, Tag, Geometry>& v)
  {
    return v.geometry();
  }


  TParam
  const Geometry&
  GClass::geometry() const
  {
    return geometry_;
  }

  TParam
  Geometry&
  GClass::geometry()
  {
    return geometry_;
  }


  // Remove macros to avoid name clashes.
# undef TParam
# undef GClass

}

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_GRAPH_HXX
