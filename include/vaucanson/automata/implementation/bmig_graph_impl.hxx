// boost_graph.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008 The Vaucanson Group.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPH_IMPL_HXX_
# define VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPH_IMPL_HXX_

# include <vaucanson/automata/implementation/bmig_graph_impl.hh>

namespace vcsn
{
  namespace bmig
  {

    /*--------------------.
    | Convenient macros.  |
    `--------------------*/

# define BMIGRAPH_TPARAM						\
    template <class Kind, class WordValue, class WeightValue,		\
              class SeriesValue, class Letter, class Tag, class GeometryCoords>

# define BMIGRAPH							\
    Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag, GeometryCoords>

    /*-------------------------.
    | Graph's implementation.  |
    `-------------------------*/

    /*---------------.
    | Constructors.  |
    `---------------*/

    BMIGRAPH_TPARAM
    BMIGRAPH::Graph ()
      : initial_bitset_(0),
        final_bitset_(0),
        number_of_epsilon_(0),
        number_of_state_(0)
    {
    }

    /*!
    **  Constructor provided for convenience.
    **  Keep compatibility with other implementations.
    **  Because of BMI, this constructor doesn't allocate memory in advance
    **  even if the 'reserve_number_of_edge' is specified.
    **
    **  However, the 'initial_number_of_state' parameter is used and implies
    **  the creation of this number of states.
    */
    BMIGRAPH_TPARAM
    BMIGRAPH::Graph (unsigned initial_number_of_states,
                      unsigned)
      : initial_bitset_(initial_number_of_states),
        final_bitset_(initial_number_of_states),
        number_of_epsilon_(0),
        number_of_state_(initial_number_of_states),
        states_(initial_number_of_states)
    {
      for (unsigned i = 0; i < initial_number_of_states; ++i)
      {
	boost::shared_ptr<std::size_t> p(new std::size_t(i));
        states_[i] = p;
      }
    }

    BMIGRAPH_TPARAM
    BMIGRAPH::Graph (const self_t& g)
    {
      tag_ = g.tag_;
      initial_bitset_ = g.initial_bitset_;
      final_bitset_ = g.final_bitset_;
      number_of_epsilon_ = g.number_of_epsilon_;
      number_of_state_ = g.number_of_state_;
      label_container_ = g.label_container_;
      initial_.clear();
      final_.clear();
      states_.resize(g.number_of_state_);
      for (unsigned i = 0; i < g.number_of_state_; ++i)
      {
	boost::shared_ptr<std::size_t> p(new std::size_t(i));
        states_[i] = p;
      }
      graph_.clear();
      for (typename graph_data_t::const_iterator i = g.graph_.begin();
          i != g.graph_.end();
          ++i)
        graph_.insert(edge_data_t(states_[*i->from_],
				  states_[*i->to_],
				  i->label_));
//				  label_container_.get_hlabel(g.label_container_.get_label(i->label_))));
  # define VCSN_COPY_I_T(Set)									\
      for (typename Set##t::const_iterator i = g.Set.begin();					\
          i != g.Set.end();									\
          ++i)											\
        Set.insert(initial_value_t (states_[*i->first], i->second));
      VCSN_COPY_I_T(initial_)
      VCSN_COPY_I_T(final_)
  # undef VCSN_COPY_I_T

  # define VCSN_COPY_GEOMETRY(Type)									\
      {													\
        typename geometry_t::Type##_geometry_map_t& map_##Type = geometry_.Type();			\
	map_##Type.clear();										\
	for (typename geometry_t::Type##_geometry_map_t::const_iterator i = g.geometry_.Type().begin();	\
	    i != g.geometry_.Type().end();								\
	    ++i)												\
	map_##Type[i->first] = i->second;								\
      }
      VCSN_COPY_GEOMETRY(states)
      VCSN_COPY_GEOMETRY(initials)
      VCSN_COPY_GEOMETRY(finals)
# undef VCSN_COPY_GEOMETRY
      {
	typename geometry_t::transitions_geometry_map_t& map_transitions = geometry_.transitions();
	map_transitions.clear();
	for (typename geometry_t::transitions_geometry_map_t::const_iterator i = g.geometry_.transitions().begin();
	    i != g.geometry_.transitions().end();
	    ++i)
	{
	  typename graph_data_t::const_iterator tmp = find_edge(states_[*i->first.value()->from_],
	      states_[*i->first.value()->to_],
	      i->first.value()->label_);
	  //label_container_.get_hlabel(g.label_container_.get_label(i->first.value()->label_)));
	  if (tmp != graph_.end())
	    map_transitions[htransition_t(tmp)] = i->second;
	}
      }
    }

    /*--------------.
    | Destructors.  |
    `--------------*/

    BMIGRAPH_TPARAM
    BMIGRAPH::~Graph ()
    {
    }

    BMIGRAPH_TPARAM
    typename BMIGRAPH::self_t&
    BMIGRAPH::operator= (const self_t& g)
    {
      if (this == &g)
	return *this;
      tag_ = g.tag_;
      initial_bitset_ = g.initial_bitset_;
      final_bitset_ = g.final_bitset_;
      number_of_epsilon_ = g.number_of_epsilon_;
      number_of_state_ = g.number_of_state_;
      label_container_ = g.label_container_;
      initial_.clear();
      final_.clear();
      states_.resize(g.number_of_state_);
      for (unsigned i = 0; i < g.number_of_state_; ++i)
      {
	boost::shared_ptr<std::size_t> p(new std::size_t(i));
	states_[i] = p;
      }
      graph_.clear();
      for (typename graph_data_t::const_iterator i = g.graph_.begin();
	  i != g.graph_.end();
	  ++i)
	graph_.insert(edge_data_t(states_[*i->from_],
	      states_[*i->to_],
	      i->label_));
# define VCSN_COPY_I_T(Set)									\
      for (typename Set##t::const_iterator i = g.Set.begin();					\
	  i != g.Set.end();									\
	  ++i)											\
      Set.insert(initial_value_t (states_[*i->first], i->second));
      VCSN_COPY_I_T(initial_)
      VCSN_COPY_I_T(final_)
# undef VCSN_COPY_I_T

# define VCSN_COPY_GEOMETRY(Type)									\
      {													\
	typename geometry_t::Type##_geometry_map_t& map_##Type = geometry_.Type();			\
	map_##Type.clear();										\
	for (typename geometry_t::Type##_geometry_map_t::const_iterator i = g.geometry_.Type().begin();	\
	    i != g.geometry_.Type().end();								\
	    ++i)												\
	map_##Type[i->first] = i->second;								\
      }
      VCSN_COPY_GEOMETRY(states)
      VCSN_COPY_GEOMETRY(initials)
      VCSN_COPY_GEOMETRY(finals)
# undef VCSN_COPY_GEOMETRY
      {
	typename geometry_t::transitions_geometry_map_t& map_transitions = geometry_.transitions();
	map_transitions.clear();
	for (typename geometry_t::transitions_geometry_map_t::const_iterator i = g.geometry_.transitions().begin();
	    i != g.geometry_.transitions().end();
	    ++i)
	{
	  typename graph_data_t::const_iterator tmp = find_edge(states_[*i->first.value()->from_],
	      states_[*i->first.value()->to_],
	      i->first.value()->label_);
	  //label_container_.get_hlabel(g.label_container_.get_label(i->first.value()->label_)));
	  if (tmp != graph_.end())
	    map_transitions[htransition_t(tmp)] = i->second;
	}
      }
      return *this;
    }

    /*------------------.
    | Basic accessors.  |
    `------------------*/

    BMIGRAPH_TPARAM
    typename BMIGRAPH::states_t
    BMIGRAPH::states() const
    {
      return misc::Support<states_data_t>(states_);
    }

    BMIGRAPH_TPARAM
    typename BMIGRAPH::edges_t
    BMIGRAPH::edges() const
    {
      return edges_t(graph_);
    }

    BMIGRAPH_TPARAM
    typename BMIGRAPH::initial_support_t
    BMIGRAPH::initial () const
    {
      return initial_support_t(initial_);
    }

    BMIGRAPH_TPARAM
    typename BMIGRAPH::final_support_t
    BMIGRAPH::final () const
    {
      return final_support_t(final_);
    }


    /*----------------------.
    | State manipulations.  |
    `----------------------*/

    BMIGRAPH_TPARAM
    bool
    BMIGRAPH::has_state (const hstate_t& s) const
    {
      // May be we should add a set or a hashtable to have
      // a searching time better than linear
      bool b = false;
      for_all_iterator(states_data_t::const_iterator, i, states_)
	if (*i == s.value())
	  b = true;
      return b;
    }

    BMIGRAPH_TPARAM
    typename BMIGRAPH::hstate_t
    BMIGRAPH::add_state ()
    {
      initial_bitset_.append(false);
      final_bitset_.append(false);
      boost::shared_ptr<std::size_t> p(new std::size_t(number_of_state_++));
      state_t h(p);
      states_.push_back(h);
      return hstate_t(h);
    }

    BMIGRAPH_TPARAM
    typename BMIGRAPH::hstate_t
    BMIGRAPH::get_state (unsigned s) const
    {
      precondition(s < states_.size());
      return hstate_t(states_[s]);
    }

    BMIGRAPH_TPARAM
    void
    BMIGRAPH::del_state (const hstate_t& s)
    {
      precondition (has_state(s));

      // One removes the state h
      graph_.template get<src>().erase(s.value());
      graph_.template get<dst>().erase(s.value());

      if (s != (number_of_state_ - 1) && (number_of_state_ - 1))
      {
	state_t lastone = states_.back();
        states_[s] = lastone;
  # define VCSN_UPDATE(Set)				      \
        if (Set##bitset_[*lastone])			      \
        {						      \
          if (Set##bitset_[s])				      \
            Set.erase(s.value());			      \
          else						      \
            Set##bitset_[s] = true;			      \
        }						      \
        else						      \
        {						      \
          if (Set##bitset_[s])				      \
          {						      \
            Set##bitset_[s] = false;			      \
            Set.erase(s.value());			      \
          }						      \
        }

        //Updating initial/final states information
        VCSN_UPDATE(initial_)
        VCSN_UPDATE(final_)
  # undef VCSN_UPDATE
	*lastone = *s.value();
      }
      else
      {
        initial_.erase(s.value());
        final_.erase(s.value());
      }

      --number_of_state_;
      states_.pop_back();
      postcondition(states_.size() == number_of_state_);
      //delete s.value();
      initial_bitset_.resize(number_of_state_);
      final_bitset_.resize(number_of_state_);

      //Useless postcondition since the states are 'renamed'
      //postcondition(!has_state(h));
    }

    BMIGRAPH_TPARAM
    void
    BMIGRAPH::set_initial (const hstate_t& s,
                           const series_set_elt_value_t& v,
                           const series_set_elt_value_t& z)
    {
      precondition(has_state(s));
      if (z == v)
      {
        initial_.erase (s.value());
        initial_bitset_[s] = false;
      }
      else if (!initial_bitset_[s])
      {
        initial_.insert (initial_value_t (s.value(), v));
        initial_bitset_[s] = true;
      }
      else
	initial_.modify(initial_.find(s.value()), update_label<initial_value_t>(v));
    }

    BMIGRAPH_TPARAM
    const typename BMIGRAPH::series_set_elt_value_t&
    BMIGRAPH::get_initial(const hstate_t& s, const series_set_elt_value_t &zero) const
    {
      precondition(has_state(s));
      typename initial_t::const_iterator it = initial_.find(s.value());

      if (it == initial_.end())
        return zero;
      return it->second;
    }

    BMIGRAPH_TPARAM
    bool
    BMIGRAPH::is_initial(const hstate_t& s, const series_set_elt_value_t&) const
    {
      precondition(has_state(s));
      return initial_bitset_[s];
    }

    BMIGRAPH_TPARAM
    void
    BMIGRAPH::clear_initial()
    {
      initial_.clear();
      initial_bitset_.reset();
    }

    BMIGRAPH_TPARAM
    void
    BMIGRAPH::set_final(const hstate_t& s,
                          const series_set_elt_value_t& v,
                          const series_set_elt_value_t& z)
    {
      precondition(has_state(s));
      if (z == v)
      {
        final_.erase (s.value());
        final_bitset_[s] = false;
      }
      else if (!final_bitset_[s])
      {
        final_.insert (initial_value_t (s.value(), v));
        final_bitset_[s] = true;
      }
      else
	final_.modify(final_.find(s.value()), update_label<final_value_t>(v));
    }

    BMIGRAPH_TPARAM
    const typename BMIGRAPH::series_set_elt_value_t&
    BMIGRAPH::get_final(const hstate_t& s, const series_set_elt_value_t &zero) const
    {
      precondition(has_state(s));
      typename final_t::const_iterator it = final_.find(s.value());

      if (it == final_.end())
        return zero;
      return it->second;
    }

    BMIGRAPH_TPARAM
    bool
    BMIGRAPH::is_final(const hstate_t& s, const series_set_elt_value_t&) const
    {
      precondition(has_state(s));
      return final_bitset_[s];
    }

    BMIGRAPH_TPARAM
    void
    BMIGRAPH::clear_final()
    {
      final_.clear();
      final_bitset_.reset();
    }

    /*---------------------.
    | Edge manipulations.  |
    `---------------------*/

    BMIGRAPH_TPARAM
    bool
    BMIGRAPH::has_edge (const hedge_t& h) const
    {
      succ_range r = graph_.equal_range(boost::make_tuple(h.value()->from_,
                                                    h.value()->label_));
      succ_iterator it;
      state_t to = h.value()->to_;
      for (it = r.first; it != r.second && it->to_ != to; ++it)
        /*Nothing*/;

      return it != r.second;
    }

    BMIGRAPH_TPARAM
    typename BMIGRAPH::hedge_t
    BMIGRAPH::add_edge (const hstate_t& from, const hstate_t& to, const label_t& l)
    {
      //hlabel_t hl = label_container_.insert (l);
      return hedge_t (graph_.insert (edge_data_t (from.value(), to.value(), l)).first);
    }

    BMIGRAPH_TPARAM
    void
    BMIGRAPH::del_edge (const hedge_t& h)
    {
      precondition (has_edge(h));

      hlabel_t l = h.value()->label_;
      graph_.erase(h.value());
      //label_container_.erase(l);

      // h points to an invalid edgeValue since it is already destroyed.
      // We can't check this postcondition anymore!
      //postcondition(!has_edge(h));
    }

    BMIGRAPH_TPARAM
    typename BMIGRAPH::hstate_t
    BMIGRAPH::src_of (const hedge_t& h) const
    {
      return hstate_t(h.value()->from_);
    }

    BMIGRAPH_TPARAM
    typename BMIGRAPH::hstate_t
    BMIGRAPH::dst_of (const hedge_t& h) const
    {
      return hstate_t(h.value()->to_);
    }

    BMIGRAPH_TPARAM
    const typename BMIGRAPH::label_t&
    BMIGRAPH::label_of (const hedge_t& h) const
    {
      return h.value()->label_;
//      return label_container_.get_label(h.value()->label_);
    }

    BMIGRAPH_TPARAM
    void
    BMIGRAPH::update(const hedge_t& h, const label_t& l)
    {
      label_container_.update(h->label_, l);
      graph_.modify(h.value(), update_hlabel<hlabel_t>(h->label_));
    }

    BMIGRAPH_TPARAM
    template <class S>
    bool
    BMIGRAPH::exists (const AutomataBase<S>& s) const
    {
      typename WordValue::iterator	it;
      typename label_t::const_iterator	r;
      label_t				l;
      WordValue				w;

      for (typename graph_data_t::iterator i = graph_.begin(); i != graph_.end(); ++i)
      {
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

    BMIGRAPH_TPARAM
    inline
    typename BMIGRAPH::tag_t&
    BMIGRAPH::tag ()
    {
      return tag_;
    }

    BMIGRAPH_TPARAM
    inline
    const typename BMIGRAPH::tag_t&
    BMIGRAPH::tag () const
    {
      return tag_;
    }

    BMIGRAPH_TPARAM
    inline
    typename BMIGRAPH::geometry_t&
    BMIGRAPH::geometry ()
    {
      return geometry_;
    }

    BMIGRAPH_TPARAM
    inline
    const typename BMIGRAPH::geometry_t&
    BMIGRAPH::geometry () const
    {
      return geometry_;
    }

    template <class Kind, class WordValue, class WeightValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    Tag&
    op_tag(const AutomataBase<I>&, BMIGRAPH &g)
    {
      return g.tag();
    }

    template <class Kind, class WordValue, class WeightValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    const Tag&
    op_tag(const AutomataBase<I>&, BMIGRAPH &g)
    {
      return g.tag();
    }

    template <class Kind, class WordValue, class WeightValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    typename BMIGRAPH::geometry_t&
    op_geometry(const AutomataBase<I>&, BMIGRAPH &g)
    {
      return g.geometry();
    }

    template <class Kind, class WordValue, class WeightValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    const typename BMIGRAPH::geometry_t&
    op_geometry(const AutomataBase<I>&, const BMIGRAPH &g)
    {
      return g.geometry();
    }

    BMIGRAPH_TPARAM
    typename BMIGRAPH::graph_data_t::const_iterator
    BMIGRAPH::find_edge(const state_t& from, const state_t& to,
                          const hlabel_t& label) const
    {
      succ_range r = graph_.equal_range(::boost::make_tuple(from, label));
      for (succ_iterator i = r.first; i != r.second; ++i)
        if (i->to_ == to)
          return i;
      return graph_.end();
    }

    /*------------------.
    | Delta functions.  |
    `------------------*/

  # define DEFINE_DELTAI_FUNCTION(DeltaKind)					\
    BMIGRAPH_TPARAM								\
    std::pair<typename BMIGRAPH::DeltaKind##_iterator,				\
	      typename BMIGRAPH::DeltaKind##_iterator>				\
    BMIGRAPH::deltai(const hstate_t& s, DeltaKind##_iterator) const		\
    {										\
      assertion(has_state(s));							\
      return graph_.template get<DeltaKind>().equal_range(s.value());		\
    }

    DEFINE_DELTAI_FUNCTION(src);
    DEFINE_DELTAI_FUNCTION(dst);
  # undef DEFINE_DELTAI_FUNCTION

    BMIGRAPH_TPARAM
    template <typename I>
    typename BMIGRAPH::htransition_t
    BMIGRAPH::get_htransition(const I& i) const
    {
      return htransition_t(graph_.project<0>(i));
    }

    // End of syntactic sugar
# undef BMIGRAPH_TPARAM
# undef BMIGRAPH
  } // End of namespace bmig
} // End of namespace vcsn

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPH_IMPL_HXX_ //
