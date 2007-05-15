// boost_graph.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HXX_
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HXX_

# include <vaucanson/automata/implementation/boost_graph.hh>

namespace vcsn
{
  /*--------------------.
  | Convenient macros.  |
  `--------------------*/

# define BOOSTGRAPH_TPARAM						\
  template <class Kind, class WordValue, class WeightValue,		\
	    class SeriesValue, class Letter, class Tag, class GeometryCoords>

# define BOOSTGRAPH							\
  Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag, GeometryCoords>


  /*
  ** class EdgeLabel
  */

  BOOSTGRAPH_TPARAM
  inline
  BOOSTGRAPH::EdgeValue::EdgeValue (bgstate_t h1, bgstate_t h2, hlabel_t l)
    : label_ (l), from_ (h1), to_ (h2)
  { }

  /*-------------------------.
  | Graph's implementation.  |
  `-------------------------*/

  /*---------------.
  | Constructors.  |
  `---------------*/

  BOOSTGRAPH_TPARAM
  inline
  BOOSTGRAPH::Graph ()
    : initial_bitset_(0),
      final_bitset_(0),
      number_of_epsilon_(0),
      number_of_state_(0)
  { }

  /*!
  **  Constructor provided for convenience.
  **  Keep compatibility with other implementations.
  **  Because of BMI, this constructor doesn't allocate memory in advance
  **  even if the 'reserve_number_of_edge' is specified.
  **
  **  However, the 'initial_number_of_state' parameter is used and implies
  **  the creation of this number of states.
  */
  BOOSTGRAPH_TPARAM
  BOOSTGRAPH::Graph (unsigned initial_number_of_states,
		     unsigned reserve_number_of_edge)
    : initial_bitset_(initial_number_of_states),
      final_bitset_(initial_number_of_states),
      number_of_epsilon_(0),
      number_of_state_(initial_number_of_states),
      states_(initial_number_of_states)
  {
    for (unsigned i = 0; i < initial_number_of_states; ++i)
      states_[i] = bgstate_t(new unsigned(i));
  }

  BOOSTGRAPH_TPARAM
  BOOSTGRAPH::Graph (const self_t& g)
  {
    tag_ = g.tag_;
    initial_bitset_ = g.initial_bitset_;
    final_bitset_ = g.final_bitset_;
    number_of_epsilon_ = g.number_of_epsilon_;
    number_of_state_ = g.number_of_state_;
    label_container_ = g.label_container_;
    for (states_data_t::iterator i = states_.begin();
	 i != states_.end();
	 ++i)
      delete i->value();
    states_.resize(g.number_of_state_);
    for (unsigned i = 0; i < g.number_of_state_; ++i)
      states_[i] = bgstate_t(new unsigned(i));
    graph_.clear();
    for (typename graph_data_t::const_iterator i = g.graph_.begin();
	 i != g.graph_.end();
	 ++i)
      graph_.insert(EdgeValue(states_[*i->from_.value()],
	                      states_[*i->to_.value()],
			      label_container_.get_hlabel(g.label_container_.get_label(i->label_))));
# define VCSN_COPY_I_T(Set)									\
    Set.clear();										\
    for (typename Set##t::const_iterator i = g.Set.begin();					\
	 i != g.Set.end();									\
	 ++i)											\
      Set.insert(InitialValue<series_set_elt_value_t> (states_[*i->first.value()], i->second));
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
	typename graph_data_t::const_iterator tmp = find_edge(states_[*i->first.value()->from_.value()],
				                              states_[*i->first.value()->to_.value()],
				                              label_container_.get_hlabel(g.label_container_.get_label(i->first.value()->label_)));
	if (tmp != graph_.end())
	  map_transitions[htransition_t(&*tmp)] = i->second;
      }
    }
  }

  /*--------------.
  | Destructors.  |
  `--------------*/

  BOOSTGRAPH_TPARAM
  inline
  BOOSTGRAPH::~Graph ()
  {
    for (states_data_t::iterator i = states_.begin();
	 i != states_.end();
	 ++i)
      delete i->value();
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::self_t&
  BOOSTGRAPH::operator= (const self_t& g)
  {
    if (this == &g)
      return *this;
    tag_ = g.tag_;
    initial_bitset_ = g.initial_bitset_;
    final_bitset_ = g.final_bitset_;
    number_of_epsilon_ = g.number_of_epsilon_;
    number_of_state_ = g.number_of_state_;
    label_container_ = g.label_container_;
    for (states_data_t::iterator i = states_.begin();
	 i != states_.end();
	 ++i)
      delete i->value();
    states_.resize(g.number_of_state_);
    for (unsigned i = 0; i < g.number_of_state_; ++i)
      states_[i] = bgstate_t(new unsigned(i));
    graph_.clear();
    for (typename graph_data_t::const_iterator i = g.graph_.begin();
	 i != g.graph_.end();
	 ++i)
      graph_.insert(EdgeValue(states_[*i->from_.value()],
	                      states_[*i->to_.value()],
			      label_container_.get_hlabel(g.label_container_.get_label(i->label_))));
# define VCSN_COPY_I_T(Set)									\
    Set.clear();										\
    for (typename Set##t::const_iterator i = g.Set.begin();					\
	 i != g.Set.end();									\
	 ++i)											\
      Set.insert(InitialValue<series_set_elt_value_t> (states_[*i->first.value()], i->second));
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
	typename graph_data_t::const_iterator tmp = find_edge(states_[*i->first.value()->from_.value()],
				                              states_[*i->first.value()->to_.value()],
				                              label_container_.get_hlabel(g.label_container_.get_label(i->first.value()->label_)));
	if (tmp != graph_.end())
	  map_transitions[htransition_t(&*tmp)] = i->second;
      }
    }
    return *this;
  }

  /*------------------.
  | Basic accessors.  |
  `------------------*/

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::states_t
  BOOSTGRAPH::states() const
  {
    return misc::Support<states_data_t>(states_);
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::edges_t
  BOOSTGRAPH::edges() const
  {
    return VGraphContainer(graph_);
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::initial_support_t
  BOOSTGRAPH::initial () const
  {
    return initial_support_t(initial_);
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::final_support_t
  BOOSTGRAPH::final () const
  {
    return final_support_t(final_);
  }


  /*----------------------.
  | State manipulations.  |
  `----------------------*/

  BOOSTGRAPH_TPARAM
  bool
  BOOSTGRAPH::has_state (hstate_t s) const
  {
    bgstate_t h(states_[s.value()]);
    typename states_t::const_iterator i;
    for (i = states_.begin();
	 i != states_.end() && *i != s;
	 ++i)
      ;
    return i != states_.end();
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::hstate_t
  BOOSTGRAPH::add_state ()
  {
    initial_bitset_.append(false);
    final_bitset_.append(false);
    bgstate_t h(new unsigned(number_of_state_++));
    states_.push_back(h);
    return hstate_t(*h.value());
  }

  BOOSTGRAPH_TPARAM
  void
  BOOSTGRAPH::del_state (hstate_t s)
  {
    precondition (has_state(s));
    bgstate_t h(states_[s.value()]);
    --number_of_state_;

    // One removes the state h
    graph_.get<src>().erase(h);
    graph_.get<dst>().erase(h);

    if (*h.value() != number_of_state_ && number_of_state_)
    {
      *(states_.back().value()) = *h.value();
      states_[*h.value()] = states_.back();

# define VCSN_UPDATE(Set)					      \
      if (Set##bitset_[number_of_state_])			      \
      {								      \
	if (Set##bitset_[*h.value()])				      \
	  Set.erase(h);						      \
	else							      \
	  Set##bitset_[*h.value()] = true;			      \
      }								      \
      else							      \
      {								      \
	if (Set##bitset_[*h.value()])				      \
	{							      \
	  Set##bitset_[*h.value()] = false;			      \
	  Set.erase(h);						      \
	}							      \
      }

      //Updating initial/final states information
      VCSN_UPDATE(initial_)
      VCSN_UPDATE(final_)
# undef VCSN_UPDATE
    }
    else
    {
      initial_.erase(h);
      final_.erase(h);
    }

    states_.pop_back();
    delete h.value();
    initial_bitset_.resize(number_of_state_);
    final_bitset_.resize(number_of_state_);

    //Useless postcondition since the states are 'renamed'
    //postcondition(!has_state(h));
  }

  BOOSTGRAPH_TPARAM
  void
  BOOSTGRAPH::set_initial (hstate_t h,
			   const series_set_elt_value_t& v,
			   const series_set_elt_value_t& z)
  {
    bgstate_t s(states_[h.value()]);
    if (z == v)
    {
      initial_.erase (s);
      initial_bitset_[*s.value()] = false;
    }
    else
      if (!initial_bitset_[*s.value()])
      {
	initial_.insert (InitialValue<series_set_elt_value_t> (s, v));
	initial_bitset_[*s.value()] = true;
      }
  }

  BOOSTGRAPH_TPARAM
  const typename BOOSTGRAPH::series_set_elt_value_t&
  BOOSTGRAPH::get_initial(hstate_t s, const series_set_elt_value_t &zero) const
  {
    bgstate_t state(states_[s.value()]);
    typename initial_t::const_iterator it = initial_.find(state);

    if (it == initial_.end())
      return zero;
    return it->second;
  }

  BOOSTGRAPH_TPARAM
  bool
  BOOSTGRAPH::is_initial(const hstate_t s, const series_set_elt_value_t&) const
  {
    return initial_bitset_[s.value()];
  }

  BOOSTGRAPH_TPARAM
  void
  BOOSTGRAPH::clear_initial()
  {
    initial_.clear();
    initial_bitset_.reset();
  }

  BOOSTGRAPH_TPARAM
  void
  BOOSTGRAPH::set_final(hstate_t h,
		        const series_set_elt_value_t& v,
		        const series_set_elt_value_t& z)
  {
    bgstate_t s(states_[h.value()]);
    if (z == v)
    {
      final_.erase (s);
      final_bitset_[*s.value()] = false;
    }
    else
      if (!final_bitset_[*s.value()])
      {
	final_.insert (InitialValue<series_set_elt_value_t> (s, v));
	final_bitset_[*s.value()] = true;
      }
  }

  BOOSTGRAPH_TPARAM
  const typename BOOSTGRAPH::series_set_elt_value_t&
  BOOSTGRAPH::get_final(hstate_t s, const series_set_elt_value_t &zero) const
  {
    bgstate_t state(states_[s.value()]);
    typename final_t::const_iterator it = final_.find(state);

    if (it == final_.end())
      return zero;
    return it->second;
  }

  BOOSTGRAPH_TPARAM
  bool
  BOOSTGRAPH::is_final(const hstate_t s, const series_set_elt_value_t&) const
  {
    return final_bitset_[s.value()];
  }

  BOOSTGRAPH_TPARAM
  void
  BOOSTGRAPH::clear_final()
  {
    final_.clear();
    final_bitset_.reset();
  }

  /*---------------------.
  | Edge manipulations.  |
  `---------------------*/

  BOOSTGRAPH_TPARAM
  bool
  BOOSTGRAPH::has_edge (hedge_t h) const
  {
    succ_range r = graph_.get<succ>().equal_range(boost::make_tuple(h.value()->from_,
						  h.value()->label_));
    succ_iterator it;
    bgstate_t to = h.value()->to_;
    for (it = r.first; it != r.second && it->to_ != to; ++it)
      /*Nothing*/;

    return it != graph_.get<succ>().end();
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::hedge_t
  BOOSTGRAPH::add_edge (hstate_t f, hstate_t t, const label_t& l)
  {
    bgstate_t from(states_[f.value()]);
    bgstate_t to(states_[t.value()]);
    hlabel_t hl = label_container_.insert (l);
    return hedge_t (&*graph_.insert (EdgeValue (from, to, hl)).first);
  }

  BOOSTGRAPH_TPARAM
  void
  BOOSTGRAPH::del_edge (hedge_t h)
  {
    precondition (has_edge(h));
    succ_range r = graph_.get<succ>().equal_range(boost::make_tuple(h.value()->from_,
							    h.value()->label_));

    bgstate_t to = h.value()->to_;
    succ_iterator it = r.first;
    for (; it != r.second && it->to_ != to; ++it)
      /* NOTHING */;
    hlabel_t l = h.value()->label_;
    graph_.get<succ>().erase(it);
    label_container_.erase(l);

    // h points to an invalid edgeValue since it is already destroyed.
    // We can't check this postcondition anymore!
    //postcondition(!has_edge(h));
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::hstate_t
  BOOSTGRAPH::src_of (hedge_t h) const
  {
    return hstate_t(*h.value()->from_.value());
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::hstate_t
  BOOSTGRAPH::dst_of (hedge_t h) const
  {
    return hstate_t(*h.value()->to_.value());
  }

  BOOSTGRAPH_TPARAM
  const typename BOOSTGRAPH::label_t&
  BOOSTGRAPH::label_of (hedge_t h) const
  {
    return h.value()->label_.value()->value();
  }

  BOOSTGRAPH_TPARAM
  void
  BOOSTGRAPH::update(hedge_t h, const label_t& l)
  {
    iterator it = graph_.find(h);
    label_container_.update(h->label_, l);
    graph_.get<succ>().modify(graph_.project<succ>(it), update_label(h.value()));
  }

  BOOSTGRAPH_TPARAM
  template <class S>
  bool
  BOOSTGRAPH::exists (const AutomataBase<S>& s) const
  {
    typename WordValue::iterator	it;
    typename label_t::const_iterator	r;
    label_t				l;
    WordValue				w;

    for (iterator i = graph_.begin(); i != graph_.end(); ++i)
    {
      // Make sure that source and destination of edge are part of the
      // automaton.
      if (!has_state(dst_of(hedge_t(*i))) ||
	  !has_state(src_of(hedge_t(*i))))
	return false;

      // Make sure that every letter of the edge is in the alphabet.
      l = label_of(hedge_t(*i));
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

  BOOSTGRAPH_TPARAM
  inline
  typename BOOSTGRAPH::tag_t&
  BOOSTGRAPH::tag ()
  {
    return tag_;
  }

  BOOSTGRAPH_TPARAM
  inline
  const typename BOOSTGRAPH::tag_t&
  BOOSTGRAPH::tag () const
  {
    return tag_;
  }

  BOOSTGRAPH_TPARAM
  inline
  typename BOOSTGRAPH::geometry_t&
  BOOSTGRAPH::geometry ()
  {
    return geometry_;
  }

  BOOSTGRAPH_TPARAM
  inline
  const typename BOOSTGRAPH::geometry_t&
  BOOSTGRAPH::geometry () const
  {
    return geometry_;
  }

  template <class Kind, class WordValue, class WeightValue, class SeriesValue,
	    class Letter, class Tag, class GeometryCoords, class I>
  Tag&
  op_tag(const AutomataBase<I>&, BOOSTGRAPH &g)
  {
    return g.tag();
  }

  template <class Kind, class WordValue, class WeightValue, class SeriesValue,
	    class Letter, class Tag, class GeometryCoords, class I>
  const Tag&
  op_tag(const AutomataBase<I>&, BOOSTGRAPH &g)
  {
    return g.tag();
  }

  template <class Kind, class WordValue, class WeightValue, class SeriesValue,
	    class Letter, class Tag, class GeometryCoords, class I>
  typename BOOSTGRAPH::geometry_t&
  op_geometry(const AutomataBase<I>&, BOOSTGRAPH &g)
  {
    return g.geometry();
  }

  template <class Kind, class WordValue, class WeightValue, class SeriesValue,
	    class Letter, class Tag, class GeometryCoords, class I>
  const typename BOOSTGRAPH::geometry_t&
  op_geometry(const AutomataBase<I>&, const BOOSTGRAPH &g)
  {
    return g.geometry();
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::graph_data_t::const_iterator
  BOOSTGRAPH::find_edge(const bgstate_t& from, const bgstate_t& to,
			const hlabel_t& label) const
  {
    succ_range r = graph_.get<succ>().equal_range(::boost::make_tuple(from, label));
    for (succ_iterator i = r.first; i != r.second; ++i)
      if (i->to_ == to)
	return graph_.project<0>(i);
    return graph_.end();
  }

  /*------------------.
  | Delta functions.  |
  `------------------*/

# define DEFINE_DELTA_FUNCTION(FunName, DeltaKind, Target, GetElt)		\
  BOOSTGRAPH_TPARAM								\
  template <typename OutputIterator, typename Query>				\
  void										\
  BOOSTGRAPH::FunName(OutputIterator res,					\
		      typename BOOSTGRAPH::hstate_t h,				\
		      const Query& query,					\
		      delta_kind::DeltaKind) const				\
  {										\
    assertion(has_state(h));							\
    bgstate_t s(states_[h.value()]);						\
    Target##_range r = graph_.get<Target>().equal_range(s);			\
    for (Target##_iterator e = r.first; e != r.second; e++)			\
      if (query(hedge_t(&*e)))							\
	*res++ = GetElt;							\
  }

  DEFINE_DELTA_FUNCTION (delta, edges, src, hedge_t(&*e));
  DEFINE_DELTA_FUNCTION (delta, states, src, hstate_t(*e->to_.value()));
  DEFINE_DELTA_FUNCTION (rdelta, edges, dst, hedge_t(&*e));
  DEFINE_DELTA_FUNCTION (rdelta, states, dst, hstate_t(*e->from_.value()));

# undef DEFINE_DELTA_FUNCTION

# define DEFINE_DELTAF_FUNCTION(FunName, DeltaKind, Target, IsBool, Action)	\
  BOOSTGRAPH_TPARAM								\
  template <typename Functor, typename Query>					\
  void										\
  BOOSTGRAPH::FunName(Functor& f,						\
		      typename BOOSTGRAPH::hstate_t h,				\
		      const Query& query,					\
		      delta_kind::DeltaKind,					\
		      misc::IsBool##_t) const					\
  {										\
    assertion(has_state(h));							\
    bgstate_t s(states_[h.value()]);						\
    Target##_range r = graph_.get<Target>().equal_range(s);			\
    for (Target##_iterator e = r.first; e != r.second; e++)			\
      if (query(htransition_t(&*e)))						\
      {										\
	Action;									\
      }										\
  }

  DEFINE_DELTAF_FUNCTION (deltaf, edges, src, true, if (not f(hedge_t(&*e))) break);
  DEFINE_DELTAF_FUNCTION (deltaf, edges, src, false, f(hedge_t(&*e)));
  DEFINE_DELTAF_FUNCTION (deltaf, states, src, true, if (not f(hstate_t(*e->to_.value()))) break);
  DEFINE_DELTAF_FUNCTION (deltaf, states, src, false, f(hstate_t(*e->to_.value())));

  DEFINE_DELTAF_FUNCTION (rdeltaf, edges, dst, true, if (not f(hedge_t(&*e))) break);
  DEFINE_DELTAF_FUNCTION (rdeltaf, edges, dst, false, f(hedge_t(&*e)));
  DEFINE_DELTAF_FUNCTION (rdeltaf, states, dst, true, if (not f(hstate_t(*e->from_.value()))) break);
  DEFINE_DELTAF_FUNCTION (rdeltaf, states, dst, false, f(hstate_t(*e->from_.value())));

# undef DEFINE_DELTAF_FUNCTION

  namespace deltaf_helper {
    template <typename T, typename R, typename Arg>
    char is_returning_bool_helper (R (T::*) (Arg));

    template <typename T, typename Arg>
    int is_returning_bool_helper (bool (T::*) (Arg));

# define is_returning_bool(T)							\
    (sizeof (deltaf_helper::is_returning_bool_helper (T)) == sizeof (int))
  }

# define DEFINE_DELTAF_HELPER(FunName)						\
  BOOSTGRAPH_TPARAM								\
  template <typename Functor, class Query, typename DeltaKind>			\
  void										\
  BOOSTGRAPH::FunName(Functor& f,						\
		  typename BOOSTGRAPH::hstate_t s,				\
		  const Query& query,						\
		  delta_kind::kind<DeltaKind> k) const				\
  {										\
    FunName (f, s, query, k,							\
	     BOOL_TO_TYPE (is_returning_bool (&Functor::operator ())) ());	\
  }

  DEFINE_DELTAF_HELPER (deltaf);
  DEFINE_DELTAF_HELPER (rdeltaf);

# undef DEFINE_DELTAF_HELPER
# undef is_returning_bool


  // End of syntactic sugar
# undef BOOSTGRAPH_TPARAM
# undef BOOSTGRAPH

} // End of namespace vcsn

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HXX_ //
