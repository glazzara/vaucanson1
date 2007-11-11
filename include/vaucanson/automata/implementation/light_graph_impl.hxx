// light_graph_impl.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_GRAPH_IMPL_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_GRAPH_IMPL_HXX

# include <fstream>
# include <sstream>

# include <algorithm>
# include <utility>

# include <vaucanson/automata/implementation/light_graph_impl.hh>
# include <vaucanson/misc/contract.hh>
# include <vaucanson/misc/static.hh>

namespace vcsn
{
  namespace light
  {

    /*--------------------.
    | Convenient macros.  |
    `--------------------*/

    # define TParam								\
    template <class Kind, class WordValue, class WeightValue,		\
            class SeriesValue, class Letter, class Tag, class GeometryCoords>

    # define GClass								\
    Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag, GeometryCoords>

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
    GClass::Graph (unsigned reserve_number_of_state,
                   unsigned reserve_number_of_edge)
    {
      states_.reserve(reserve_number_of_state);
      edges_.reserve(reserve_number_of_edge);
			edge_data_.reserve(reserve_number_of_edge);
    }

    /*------------------.
    | Basic accessors.  |
    `------------------*/

    TParam
    typename GClass::states_t
    GClass::states() const
    {
      std::cout << "states() " << std::endl;
      for (unsigned i = 0; i < states_.size(); ++i)
	std::cout << states_[i] << ", ";
      std::cout << std::endl;
      return states_t(states_);
    }

    TParam
    typename GClass::edges_t
    GClass::edges() const
    {
      std::cout << "edges() " << std::endl;
      for (unsigned i = 0; i < edges_.size(); ++i)
	std::cout << "(" << edge_data_[i].from_ << ", " << edge_data_[i].to_ << "), ";
      std::cout << std::endl;
      return edges_t(edges_);
    }

    TParam
    typename GClass::initial_support_t
    GClass::initial() const
    {
      std::cout << "initial() " << std::endl;
      return initial_support_t(initial_);
    }

    TParam
    typename GClass::final_support_t
    GClass::final() const
    {
      std::cout << "final() " << std::endl;
      return final_support_t(final_);
    }


    /*----------------------.
    | States manipulation.  |
    `----------------------*/

    TParam
    bool
    GClass::has_state(hstate_t n) const
    {
      return n >= 0 && n < int(states_.size());
    }

    TParam
    typename GClass::hstate_t
    GClass::add_state()
    {
        states_.push_back(states_.size());
        return states_.size() - 1;
    }

    TParam
    void
    GClass::del_state(hstate_t n)
    {
      precondition (has_state(n));
      std::cout << "del_state = " << n << std::endl;

      initial_.erase(n);
      final_.erase(n);

      if (states_.size() > 1 && n != int(states_.size() - 1))
      {
	int moved_state = states_.size() - 1;
	for (unsigned i = 0; i < edges_.size();)
	{
	  if (edge_data_[i].from_ == n || edge_data_[i].to_ == n)
	  {
	    edges_.erase(edges_.begin() + i);
	    edge_data_.erase(edge_data_.begin() + i);
	  }
	  else
	  {
	    if (edge_data_[i].from_ == moved_state)
	      edge_data_[i].from_ = n;
	    else if (edge_data_[i].to_ == moved_state)
	      edge_data_[i].to_ = n;
	    ++i;
	  }
	}
	if (initial_.find(moved_state) != initial_.end())
	{
	  initial_[n] = initial_[moved_state];
	  initial_.erase(moved_state);
	}
	if (final_.find(moved_state) != final_.end())
	{
	  final_[n] = final_[moved_state];
	  final_.erase(moved_state);
	}
      }
      else
      {
	for (unsigned i = 0; i < edges_.size();)
	{
	  if (edge_data_[i].from_ == n || edge_data_[i].to_ == n)
	  {
	    edges_.erase(edges_.begin() + i);
	    edge_data_.erase(edge_data_.begin() + i);
	  }
	  else
	    ++i;
	}
      }
      states_.pop_back();
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
    bool
    GClass::is_initial(const hstate_t s, const series_set_elt_value_t& z) const
    {
      return get_initial(s, z) != z;
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
    bool
    GClass::is_final(const hstate_t s, const series_set_elt_value_t& z) const
    {
      return get_final(s, z) != z;
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
      return e >= 0 && e < int(edges_.size());
    }

    TParam
    typename GClass::hedge_t
    GClass::add_edge(hstate_t n1, hstate_t n2,
		     const label_t& v)
    {
				std::cout << "add_edge() " << std::endl;
      precondition(has_state(n1));
      precondition(has_state(n2));

      edge_data_.push_back(EdgeValue(n1, n2, v));
			edges_.push_back(edges_.size());
      return edges_.size() - 1;
    }

    TParam
    void
    GClass::del_edge(hedge_t e)
    {
      std::cout << "del_edge() " << std::endl;
      precondition (has_edge(e));

      if (edges_.size() > 1)
      {
	edge_data_[e] = edge_data_[edge_data_.size() - 1];
	edge_data_.erase(edge_data_.begin() + edge_data_.size() - 1);
	edges_.erase(edges_.begin() + edges_.size() - 1);
      }
      else
      {
	edges_.erase(edges_.begin() + e);
	edge_data_.erase(edge_data_.begin() + e);
      }
    }


    TParam
    typename GClass::hstate_t
    GClass::src_of(hedge_t e1) const
    {
      precondition(has_edge(e1));
      return edge_data_[e1].from_;
    }

    TParam
    typename GClass::hstate_t
    GClass::dst_of(hedge_t e2) const
    {
      std::cout << "dst_of " << e2 << " = " << edge_data_[e2].to_<< std::endl;
      precondition(has_edge(e2));
      return edge_data_[e2].to_;
    }

    TParam
    const typename GClass::label_t&
    GClass::label_of(hedge_t n) const
    {
      precondition(has_edge(n));
      return edge_data_[n].label_;
    }

    TParam
    void
    GClass::update(hedge_t e, label_t l)
    {
      precondition(has_edge(e));
      edge_data_[e].label_ = l;
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
        // Make sure that source and destination of edge are part of the
        // automaton.
        if (!has_state(dst_of(hedge_t(i)))
            || !has_state(src_of(hedge_t(i))))
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

    # define DEFINE_DELTA_FUNCTION(DeltaName, DKind, IO, WhatFromE)	\
    TParam								\
    template <class OutputIterator, class Query>			\
    void								\
    GClass::DeltaName(OutputIterator res,				\
                      hstate_t from,					\
                      const Query& query,				\
                      ::vcsn::delta_kind::DKind) const			\
    {									\
      assertion(has_state(from));					\
      for_all_const_(std::vector<htransition_t>, e, edges_)		\
	if (IO == from && query(*e))					\
	{								\
	  std::cout << "add this to the result: " << WhatFromE << std::endl; \
	  *res++ = WhatFromE;						\
	}								\
    }									\

    DEFINE_DELTA_FUNCTION (delta, transitions, src_of(*e), *e);
    DEFINE_DELTA_FUNCTION (delta, states, src_of(*e), dst_of(*e));
    DEFINE_DELTA_FUNCTION (rdelta, transitions, dst_of(*e), *e);
    DEFINE_DELTA_FUNCTION (rdelta, states, dst_of(*e), src_of(*e));

    # undef DEFINE_DELTA_FUNCTION

    // Delta with functor.  Much more than the previous one, because
    // functor is statically checked for return type of its operator(),
    // and behave differently if it is bool: loop breaks if false is
    // returned.
    # define DEFINE_DELTAF_FUNCTION(DeltaName, DKind, IO, IsBool, Action)\
    TParam								\
    template <typename Functor, class Query>				\
    void								\
    GClass::DeltaName(Functor& fun,					\
                      hstate_t from,					\
                      const Query& query,				\
                      ::vcsn::delta_kind::DKind,			\
                      misc::IsBool ## _t) const				\
    {									\
      assertion(has_state(from));					\
      for_all_const_(std::vector<htransition_t>, e, edges_)		\
        if (IO == from && query(*e))					\
          { Action; }							\
    }

    DEFINE_DELTAF_FUNCTION (deltaf, states, edge_data_[*e].from_, true,
                            if (not fun(edge_data_[*e].to_)) break);
    DEFINE_DELTAF_FUNCTION (deltaf, states, edge_data_[*e].from_, false, fun(edge_data_[*e].to_));
    DEFINE_DELTAF_FUNCTION (deltaf, transitions, edge_data_[*e].from_, true,
                            if (not fun(*e)) break);
    DEFINE_DELTAF_FUNCTION (deltaf, transitions, edge_data_[*e].from_, false, fun(*e));

    DEFINE_DELTAF_FUNCTION (rdeltaf, states, edge_data_[*e].to_, true,
                            if (not fun(edge_data_[*e].from_)) break);
    DEFINE_DELTAF_FUNCTION (rdeltaf, states, edge_data_[*e].to_, false, fun(edge_data_[*e].from_));
    DEFINE_DELTAF_FUNCTION (rdeltaf, transitions, edge_data_[*e].to_, true,
                            if (not fun(*e)) break);
    DEFINE_DELTAF_FUNCTION (rdeltaf, transitions, edge_data_[*e].to_, false, fun(*e));

    # undef DEFINE_DELTAF_FUNCTION

    // Helpers for static dispatch.
    namespace deltaf_helper {
      template <typename T, typename R, typename Arg>
      char is_returning_bool_helper (R (T::*) (Arg));

      template <typename T, typename Arg>
      int is_returning_bool_helper (bool (T::*) (Arg));

      # define is_returning_bool(T)					  \
      (sizeof (deltaf_helper::is_returning_bool_helper (T)) == sizeof (int))
    }

    # define DEFINE_DELTAF_HELPER(DeltaName)				\
    TParam								\
    template <typename Functor, class Query, typename DKind>		\
    void								\
    GClass::DeltaName(Functor& fun,					\
                    hstate_t from,					\
                    const Query& query,					\
                    delta_kind::kind<DKind> k) const			\
    {									\
      DeltaName (fun, from, query, k,					\
            BOOL_TO_TYPE (is_returning_bool (&Functor::operator ())) ());\
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
              class Letter, class Tag, class GeometryCoords, class I>
    Tag& op_tag(const AutomataBase<I>&,
                Graph<Kind, WordValue, WeightValue,
                SerieValue ,Letter, Tag, GeometryCoords>& v)
    {
      return v.tag();
    }

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
              class Letter, class Tag, class GeometryCoords, class I>
    const Tag& op_tag(const AutomataBase<I>&,
                      const Graph<Kind, WordValue, WeightValue,
                      SerieValue ,Letter, Tag, GeometryCoords>& v)
    {
      return v.tag();
    }


    /*-----------.
    | Geometry.  |
    `-----------*/

    template <class Kind, class WordValue, class WeightValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    typename GClass::geometry_t&
    op_geometry(const AutomataBase<I>&,
                Graph<Kind, WordValue, WeightValue,
                SeriesValue, Letter, Tag, GeometryCoords>& v)
    {
      return v.geometry();
    }

    template <class Kind, class WordValue, class WeightValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    const typename GClass::geometry_t&
    op_geometry(const AutomataBase<I>&,
                const Graph<Kind, WordValue, WeightValue,
                SeriesValue, Letter, Tag, GeometryCoords>& v)
    {
      return v.geometry();
    }


    TParam
    const typename GClass::geometry_t&
    GClass::geometry() const
    {
      return geometry_;
    }

    TParam
    typename GClass::geometry_t&
    GClass::geometry()
    {
      return geometry_;
    }


    // Remove macros to avoid name clashes.
# undef TParam
# undef GClass
  }
}

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_GRAPH_IMPL_HXX
