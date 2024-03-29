// listg_graph_impl.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_LISTG_GRAPH_IMPL_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_LISTG_GRAPH_IMPL_HXX

# include <fstream>
# include <sstream>

# include <algorithm>
# include <utility>

# include <vaucanson/automata/implementation/listg_graph_impl.hh>
# include <vaucanson/misc/contract.hh>
# include <vaucanson/misc/static.hh>

namespace vcsn
{
  namespace listg
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
                      hstate_t(states_.size() - 1),
                      removed_states_);
    }

    TParam
    typename GClass::edges_t
    GClass::edges() const
    {
      return edges_t(hedge_t(0),
		     hedge_t(edges_.size() - 1),
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
    GClass::has_state(const hstate_t& n) const
    {
      bool res = (n.is_valid() &&
		  n < unsigned(states_.size()) &&
		  (removed_states_.find(n) == removed_states_.end()));
     # ifndef VCSN_NDEBUG
      if (res == false)
      for (unsigned i = 0; i < edges_.size(); ++i)
              if (removed_edges_.find(hedge_t(i)) == removed_edges_.end())
              postcondition(edges_[i].from != n
                              && edges_[i].to != n);
      # endif // !VCSN_NDEBUG
      return res;
    }

    TParam
    typename GClass::hstate_t
    GClass::get_state(int n) const
    {
      precondition(has_state(hstate_t(n)));
      return hstate_t(n);
    }

    TParam
    typename GClass::hstate_t
    GClass::add_state()
    {
      if (removed_states_.size() == 0)
      {
        states_.push_back(state_value_t());
        return hstate_t(states_.size() - 1);
      }

      hstate_t n = *removed_states_.begin();
      removed_states_.erase(n);
      assertion(n < states_.size());

      states_[n].output_edges.clear();
      states_[n].input_edges.clear();

      postcondition(has_state(n));
      return n;
    }

    TParam
    void
    GClass::del_state(const hstate_t& n)
    {
      precondition (has_state(n));

      const state_value_t& v = states_[n];
      typename state_value::edges_t::const_iterator e = v.output_edges.begin();
      typename state_value::edges_t::const_iterator end = v.output_edges.end();
      typename state_value::edges_t::const_iterator next = e;

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
    GClass::set_initial(const hstate_t& n, const series_set_elt_value_t& v,
			const series_set_elt_value_t& z)
    {
      precondition (has_state(n));
      if (z == v)
        initial_.erase(n);
      else
        initial_[n] = v;
    }

    TParam
    const typename GClass::series_set_elt_value_t&
    GClass::get_initial(const hstate_t& n, const series_set_elt_value_t& z) const
    {
      precondition(has_state(n));
      typename initial_t::const_iterator i = initial_.find(n);
      if (i == initial_.end())
        return z;
      return i->second;
    }

    TParam
    bool
    GClass::is_initial(const hstate_t& s, const series_set_elt_value_t& z) const
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
    GClass::set_final(const hstate_t& n, const series_set_elt_value_t& v,
		      const series_set_elt_value_t& z)
    {
      precondition (has_state(n));
      if (v == z)
        final_.erase(n);
      else
        final_[n] = v;
    }

    TParam
    const typename GClass::series_set_elt_value_t&
    GClass::get_final(const hstate_t& n, const series_set_elt_value_t& z) const
    {
      precondition (has_state(n));
      typename final_t::const_iterator i = final_.find(n);
      if (i == final_.end())
        return z;
      return i->second;
    }

    TParam
    bool
    GClass::is_final(const hstate_t& s, const series_set_elt_value_t& z) const
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
    GClass::has_edge(const hedge_t& e) const
    {
      bool res = (removed_edges_.find(e) == removed_edges_.end()
                  && (e < edges_.size()));
      # ifndef VCSN_NDEBUG
      if (res == false)
        for (unsigned i = 0; i < states_.size(); ++i)
          if (removed_states_.find(hstate_t(i)) == removed_states_.end())
            postcondition(states_[i].output_edges.find(e) ==
                          states_[i].output_edges.end());
      # endif // !VCSN_NDEBUG
      return res;
    }

    TParam
    typename GClass::hedge_t
    GClass::add_edge(const hstate_t& n1, const hstate_t& n2,
		     const label_t& v)
    {
      precondition(has_state(n1));
      precondition(has_state(n2));
      hedge_t e;
      if (removed_edges_.size() == 0)
      {
        edges_.push_back(edge_value_t(n1, n2, v));
        e = hedge_t(edges_.size() - 1);
      }
      else
      {
        e = *removed_edges_.begin();
        removed_edges_.erase(e);
        assertion(e < edges_.size());
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
    GClass::del_edge(const hedge_t& e)
    {
      precondition (has_edge(e));

      const edge_value_t& ev = edges_[e];
      states_[ev.from].output_edges.erase(e);
      states_[ev.to].input_edges.erase(e);
      removed_edges_.insert(e);

      postcondition(!has_edge(e));
    }


    TParam
    typename GClass::hstate_t
    GClass::src_of(const hedge_t& e1) const
    {
      precondition(has_edge(e1));
      return edges_[e1].from;
    }

    TParam
    typename GClass::hstate_t
    GClass::dst_of(const hedge_t& e2) const
    {
      precondition(has_edge(e2));
      return edges_[e2].to;
    }

    TParam
    const typename GClass::label_t&
    GClass::label_of(const hedge_t& n) const
    {
      precondition(has_edge(n));
      return edges_[n];
    }

    TParam
    void
    GClass::update(const hedge_t& e, label_t l)
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

      for (unsigned i = 0; i < edges_.size(); ++i)
      {
        if (removed_edges_.find(hedge_t(i)) != removed_edges_.end())
          continue;
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

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_LISTG_GRAPH_IMPL_HXX
