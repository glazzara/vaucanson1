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
  BOOSTGRAPH::EdgeValue::EdgeValue (hstate_t h1, hstate_t h2, hlabel_t l)
    : label_ (l), from_ (h1), to_ (h2)
  { }

/*  inline
  EdgeValue::operator const EdgeLabel& () const
  {
    return label_;
  }

  template <typename EdgeLabel>
  inline
  EdgeValue<EdgeLabel>::operator EdgeLabel& ()
  {
    return label_;
  }
*/

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
  BOOSTGRAPH::Graph (unsigned initial_number_of_state,
		     unsigned reserve_number_of_edge)
    : initial_bitset_(initial_number_of_state),
      final_bitset_(initial_number_of_state),
      number_of_epsilon_(0),
      number_of_state_(initial_number_of_state)
  { }

  /*------------------.
  | Basic accessors.  |
  `------------------*/

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::states_t
  BOOSTGRAPH::states() const
  {
    return states_t(number_of_state_);
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::edges_t
  BOOSTGRAPH::edges() const
  {
    return graph_;
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
  BOOSTGRAPH::has_state (hstate_t h) const
  {
    return h.value() < number_of_state_;
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::hstate_t
  BOOSTGRAPH::add_state ()
  {
    initial_bitset_.append(false);
    final_bitset_.append(false);
    return hstate_t (++number_of_state_);
  }

  BOOSTGRAPH_TPARAM
  void
  BOOSTGRAPH::del_state (hstate_t h)
  {
    // One removes the state h
    graph_.get<src>().erase(h);
    graph_.get<dst>().erase(h);

    // One picks up the state with the highest ID and changes its ID to
    // h.value().
    // First, one updates its outgoing transitions.
    src_range src_r = graph_.get<src>().equal_range(number_of_state_ - 1);
    src_iterator src_tmp;
    for (src_iterator src_it = src_r.first; src_it != src_r.second;)
    {
      src_tmp = src_it++;
      graph_.get<src>().modify_key(src_tmp, update_state(h.value()));
    }

    // Then, one updates its incoming transition.
    dst_range dst_r = graph_.get<dst>().equal_range(number_of_state_ - 1);
    dst_iterator dst_tmp;
    for (dst_iterator dst_it = dst_r.first; dst_it != dst_r.second;)
    {
      dst_tmp = dst_it++;
      graph_.get<dst>().modify_key(dst_tmp, update_state(h.value()));
    }

    --number_of_state_;
  }

  BOOSTGRAPH_TPARAM
  void
  BOOSTGRAPH::set_initial (hstate_t s,
			   const series_set_elt_value_t& v,
			   const series_set_elt_value_t& z)
  {
    if (z == v)
    {
      initial_.erase (s);
      initial_bitset_[s.value()] = false;
    }
    else
    {
      initial_.insert (InitialValue<series_set_elt_value_t> (s, v));
      initial_bitset_[s.value()] = true;
    }
  }

  BOOSTGRAPH_TPARAM
  const typename BOOSTGRAPH::series_set_elt_value_t&
  BOOSTGRAPH::get_initial(hstate_t state, const series_set_elt_value_t &zero) const
  {
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
  BOOSTGRAPH::set_final(hstate_t s,
		        const series_set_elt_value_t& v,
		        const series_set_elt_value_t& z)
  {
    if (z == v)
    {
      final_.erase (s);
      final_bitset_[s.value()] = false;
    }
    else
    {
      final_.insert (InitialValue<series_set_elt_value_t> (s, v));
      final_bitset_[s.value()] = true;
    }
  }

  BOOSTGRAPH_TPARAM
  const typename BOOSTGRAPH::series_set_elt_value_t&
  BOOSTGRAPH::get_final(hstate_t state, const series_set_elt_value_t &zero) const
  {
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
    succ_range r = graph_.get<succ>().find(boost::make_tuple(h.value()->from_,
					   h.value()->label_));
    succ_iterator it;
    hstate_t to = h.value()->to_;
    for (it = r.begin(); it != r.end() && it->to_ != to; ++it)
      /*Nothing*/;

    return it != graph_.get<succ>().end();
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::hedge_t
  BOOSTGRAPH::add_edge (hstate_t from, hstate_t to, const label_t& l)
  {
    hlabel_t hl = label_container_.insert (l);

    return hedge_t (&*graph_.insert (EdgeValue (from, to, hl)).first);
  }

  BOOSTGRAPH_TPARAM
  void
  BOOSTGRAPH::del_edge (hedge_t h)
  {
    succ_range r = graph_.get<succ>().equal_range(boost::make_tuple(h.value()->from_,
							    h.value()->label_));

    hstate_t to = h.value()->to_;
    succ_iterator it = r.first;
    for (; it != r.second && it->to_ != to; ++it)
      /* NOTHING */;
    if (it != r.second)
    {
      hlabel_t l = h.value()->label_;
      graph_.get<succ>().erase(it);
      label_container_.erase(l);
    }
    /* FIXME: error handling ? */
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::hstate_t
  BOOSTGRAPH::src_of (hedge_t h) const
  {
    return h.value()->from_;
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::hstate_t
  BOOSTGRAPH::dst_of (hedge_t h) const
  {
    return h.value()->to_;
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

  /*------------------.
  | Delta functions.  |
  `------------------*/

# define DEFINE_DELTA_FUNCTION(FunName, DeltaKind, Target, GetElt)		\
  BOOSTGRAPH_TPARAM								\
  template <typename OutputIterator, typename Query>				\
  void										\
  BOOSTGRAPH::FunName(OutputIterator res,					\
		      typename BOOSTGRAPH::hstate_t s,				\
		      const Query& query,					\
		      delta_kind::DeltaKind) const				\
  {										\
    assertion(has_state(s));							\
    Target##_range r = graph_.get<Target>().equal_range(s);			\
    for (Target##_iterator e = r.first; e != r.second; e++)			\
      if (query(hedge_t(&*e)))							\
	*res++ = GetElt;							\
  }

  DEFINE_DELTA_FUNCTION (delta, edges, dst, hedge_t(&*e));
  DEFINE_DELTA_FUNCTION (delta, states, dst, e->to_);
  DEFINE_DELTA_FUNCTION (rdelta, edges, src, hedge_t(&*e));
  DEFINE_DELTA_FUNCTION (rdelta, states, src, e->from_);

# undef DEFINE_DELTA_FUNCTION

# define DEFINE_DELTAF_FUNCTION(FunName, DeltaKind, Target, IsBool, Action)	\
  BOOSTGRAPH_TPARAM								\
  template <typename Functor, typename Query>					\
  void										\
  BOOSTGRAPH::FunName(Functor& f,						\
		      typename BOOSTGRAPH::hstate_t s,				\
		      const Query& query,					\
		      delta_kind::DeltaKind,					\
		      misc::IsBool##_t) const					\
  {										\
    assertion(has_state(s));							\
    Target##_range r = graph_.get<Target>().equal_range(s);			\
    for (Target##_iterator e = r.first; e != r.second; e++)			\
      if (query(htransition_t(&*e)))						\
      {										\
	Action;									\
      }										\
  }

  DEFINE_DELTAF_FUNCTION (deltaf, edges, dst, true, if (not f(hedge_t(&*e))) break);
  DEFINE_DELTAF_FUNCTION (deltaf, edges, dst, false, f(hedge_t(&*e)));
  DEFINE_DELTAF_FUNCTION (deltaf, states, dst, true, if (not f(e->to_)) break);
  DEFINE_DELTAF_FUNCTION (deltaf, states, dst, false, f(e->to_));

  DEFINE_DELTAF_FUNCTION (rdeltaf, edges, src, true, if (not f(hedge_t(&*e))) break);
  DEFINE_DELTAF_FUNCTION (rdeltaf, edges, src, false, f(hedge_t(&*e)));
  DEFINE_DELTAF_FUNCTION (rdeltaf, states, src, true, if (not f(e->from_)) break);
  DEFINE_DELTAF_FUNCTION (rdeltaf, states, src, false, f(e->from_));

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
