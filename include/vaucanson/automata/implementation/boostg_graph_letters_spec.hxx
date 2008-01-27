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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_GRAPH_LETTERS_SPEC_HXX_
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_GRAPH_LETTERS_SPEC_HXX_

# include <vaucanson/automata/implementation/boostg_graph_letters_spec.hh>

namespace vcsn
{
  namespace boostg
  {

    /*--------------------.
    | Convenient macros.  |
    `--------------------*/

  # define BOOSTGRAPH_TPARAM						\
    template <class WordValue,						\
              class SeriesValue, class Letter, class Tag, class GeometryCoords>

  # define BOOSTGRAPH							\
    Graph<labels_are_letters, WordValue, bool, SeriesValue, Letter, Tag, GeometryCoords>

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
    BOOSTGRAPH_TPARAM
    BOOSTGRAPH::Graph (unsigned initial_number_of_states,
                      unsigned)
      : initial_bitset_(initial_number_of_states),
        final_bitset_(initial_number_of_states),
        number_of_epsilon_(0),
        number_of_state_(initial_number_of_states),
        states_(initial_number_of_states)
    {
      for (unsigned i = 0; i < initial_number_of_states; ++i)
        states_[i] = new unsigned(i);
    }

    BOOSTGRAPH_TPARAM
    BOOSTGRAPH::Graph (const self_t& g)
    {
      tag_ = g.tag_;
      initial_bitset_ = g.initial_bitset_;
      final_bitset_ = g.final_bitset_;
      number_of_epsilon_ = g.number_of_epsilon_;
      number_of_state_ = g.number_of_state_;

      initial_.clear();
      final_.clear();
      graph_.clear();
      typename geometry_t::transitions_geometry_map_t& map_transitions = geometry_.transitions();
      map_transitions.clear();


      for (states_data_t::iterator i = states_.begin();
          i != states_.end();
          ++i)
        delete *i;
      states_.resize(g.number_of_state_);
      for (unsigned i = 0; i < g.number_of_state_; ++i)
        states_[i] = new unsigned(i);
      for (typename graph_data_t::const_iterator i = g.graph_.begin();
          i != g.graph_.end();
          ++i)
        graph_.insert(edge_data_t(states_[*i->from_],
				  states_[*i->to_],
				  i->label_));
      for (initial_t::iterator it = g.initial_.begin(); it != g.initial_.end(); ++it)
	initial_.insert(states_[**it]);
      for (final_t::iterator it = g.final_.begin(); it != g.final_.end(); ++it)
	final_.insert(states_[**it]);

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
        for (typename geometry_t::transitions_geometry_map_t::const_iterator i = g.geometry_.transitions().begin();
            i != g.geometry_.transitions().end();
            ++i)
        {
          typename graph_data_t::const_iterator tmp = find_edge(states_[*i->first.value()->from_],
                                                                states_[*i->first.value()->to_],
                                                                i->first.value()->label_);
          if (tmp != graph_.end())
            map_transitions[htransition_t(tmp)] = i->second;
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
        delete *i;
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

      initial_.clear();
      final_.clear();
      graph_.clear();
      typename geometry_t::transitions_geometry_map_t& map_transitions = geometry_.transitions();
      map_transitions.clear();


      for (states_data_t::iterator i = states_.begin();
          i != states_.end();
          ++i)
        delete *i;
      states_.resize(g.number_of_state_);
      for (unsigned i = 0; i < g.number_of_state_; ++i)
        states_[i] = new unsigned(i);
      for (typename graph_data_t::const_iterator i = g.graph_.begin();
          i != g.graph_.end();
          ++i)
        graph_.insert(edge_data_t(states_[*i->from_],
				  states_[*i->to_],
				  i->label_));
      for (initial_t::iterator it = g.initial_.begin(); it != g.initial_.end(); ++it)
	initial_.insert(states_[**it]);
      for (final_t::iterator it = g.final_.begin(); it != g.final_.end(); ++it)
	final_.insert(states_[**it]);

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
      for (typename geometry_t::transitions_geometry_map_t::const_iterator i = g.geometry_.transitions().begin();
	  i != g.geometry_.transitions().end();
	  ++i)
      {
	typename graph_data_t::const_iterator tmp = find_edge(states_[*i->first.value()->from_],
	    states_[*i->first.value()->to_],
	    i->first.value()->label_);
	if (tmp != graph_.end())
	  map_transitions[htransition_t(tmp)] = i->second;
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
      return edges_t(graph_);
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
    BOOSTGRAPH::has_state (const hstate_t& s) const
    {
      return s < states_.size();
    }

    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::hstate_t
    BOOSTGRAPH::add_state ()
    {
      initial_bitset_.append(false);
      final_bitset_.append(false);
      state_t h(new unsigned(number_of_state_++));
      states_.push_back(h);
      return hstate_t(h);
    }

    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::hstate_t
    BOOSTGRAPH::get_state (unsigned s) const
    {
      precondition(s < states_.size());
      return hstate_t(states_[s]);
    }

    BOOSTGRAPH_TPARAM
    void
    BOOSTGRAPH::del_state (const hstate_t& s)
    {
      precondition (has_state(s));

      // One removes the state h
      graph_.get<src>().erase(s.value());
      graph_.get<dst>().erase(s.value());

      if (number_of_state_ > 1 && s != (number_of_state_ - 1))
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
      delete s.value();
      initial_bitset_.resize(number_of_state_);
      final_bitset_.resize(number_of_state_);

      //Useless postcondition since the states are renumbered
      //postcondition(!has_state(h));
    }

    BOOSTGRAPH_TPARAM
    void
    BOOSTGRAPH::set_initial (const hstate_t& s,
                             const series_set_elt_value_t& v,
                             const series_set_elt_value_t& z)
    {
      precondition(has_state(s));
      if (z == v)
      {
        initial_.erase (s.value());
        initial_bitset_[s] = false;
      }
      else
      {
        initial_.insert (s.value());
        initial_bitset_[s] = true;
      }
    }

    BOOSTGRAPH_TPARAM
    const typename BOOSTGRAPH::series_set_elt_value_t&
    BOOSTGRAPH::get_initial(const hstate_t& s, const series_set_elt_value_t &) const
    {
      precondition(has_state(s));
      return initial_bitset_[s];
    }

    BOOSTGRAPH_TPARAM
    bool
    BOOSTGRAPH::is_initial(const hstate_t& s, const series_set_elt_value_t&) const
    {
      precondition(has_state(s));
      return initial_bitset_[s];
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
    BOOSTGRAPH::set_final(const hstate_t& s,
                          const series_set_elt_value_t& v,
                          const series_set_elt_value_t& z)
    {
      precondition(has_state(s));
      if (z == v)
      {
        final_.erase (s.value());
        final_bitset_[s] = false;
      }
      else
      {
        final_.insert (s.value());
        final_bitset_[s] = true;
      }
    }

    BOOSTGRAPH_TPARAM
    const typename BOOSTGRAPH::series_set_elt_value_t&
    BOOSTGRAPH::get_final(const hstate_t& s, const series_set_elt_value_t &) const
    {
      precondition(has_state(s));
      return final_bitset_[s];
    }

    BOOSTGRAPH_TPARAM
    bool
    BOOSTGRAPH::is_final(const hstate_t& s, const series_set_elt_value_t&) const
    {
      precondition(has_state(s));
      return final_bitset_[s];
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
    BOOSTGRAPH::has_edge (const hedge_t& h) const
    {
      succ_range r = graph_.equal_range(boost::make_tuple(*h.value()->from_,
                                                    h.value()->label_));
      succ_iterator it;
      state_t to = h.value()->to_;
      for (it = r.first; it != r.second && it->to_ != to; ++it)
        /*Nothing*/;

      return it != r.second;
    }

    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::hedge_t
    BOOSTGRAPH::add_edge (const hstate_t& from, const hstate_t& to, const label_t& l)
    {
      return hedge_t (graph_.insert (edge_data_t (from.value(), to.value(), l)).first);
    }

    BOOSTGRAPH_TPARAM
    void
    BOOSTGRAPH::del_edge (const hedge_t& h)
    {
      precondition (has_edge(h));
      graph_.erase(h.value());

      // h points to an invalid edgeValue since it is already destroyed.
      // We can't check this postcondition anymore!
      //postcondition(!has_edge(h));
    }

    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::hstate_t
    BOOSTGRAPH::src_of (const hedge_t& h) const
    {
      return hstate_t(h.value()->from_);
    }

    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::hstate_t
    BOOSTGRAPH::dst_of (const hedge_t& h) const
    {
      return hstate_t(h.value()->to_);
    }

    BOOSTGRAPH_TPARAM
    const typename BOOSTGRAPH::label_t&
    BOOSTGRAPH::label_of (const hedge_t& h) const
    {
      return h.value()->label_;
    }

    BOOSTGRAPH_TPARAM
    void
    BOOSTGRAPH::update(const hedge_t& h, const label_t& l)
    {
      graph_.modify(h.value(), update_hlabel<label_t>(l));
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

    template <class WordValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    Tag&
    op_tag(const AutomataBase<I>&, BOOSTGRAPH &g)
    {
      return g.tag();
    }

    template <class WordValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    const Tag&
    op_tag(const AutomataBase<I>&, BOOSTGRAPH &g)
    {
      return g.tag();
    }

    template <class WordValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    typename BOOSTGRAPH::geometry_t&
    op_geometry(const AutomataBase<I>&, BOOSTGRAPH &g)
    {
      return g.geometry();
    }

    template <class WordValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    const typename BOOSTGRAPH::geometry_t&
    op_geometry(const AutomataBase<I>&, const BOOSTGRAPH &g)
    {
      return g.geometry();
    }

    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::graph_data_t::const_iterator
    BOOSTGRAPH::find_edge(const state_t& from, const state_t& to,
                          const label_t& label) const
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
  # define DEFINE_DELTA_FUNCTION(FunName, DeltaKind, Target, GetElt)		\
    BOOSTGRAPH_TPARAM								\
    template <typename OutputIterator, typename Query>				\
    void									\
    BOOSTGRAPH::FunName(OutputIterator res,					\
                        const typename BOOSTGRAPH::hstate_t& s,			\
                        const Query& query,					\
                        ::vcsn::delta_kind::DeltaKind) const			\
    {										\
      assertion(has_state(s));							\
      Target##_range r = graph_.get<Target>().equal_range(s.value());		\
      for (Target##_iterator e = r.first; e != r.second; ++e)			\
        if (query(hedge_t(graph_.project<0>(e))))				\
          *res++ = GetElt;							\
    }

    DEFINE_DELTA_FUNCTION (delta, transitions, src, hedge_t(graph_.project<0>(e)));
    DEFINE_DELTA_FUNCTION (delta, states, src, hstate_t(e->to_));
    DEFINE_DELTA_FUNCTION (rdelta, transitions, dst, hedge_t(graph_.project<0>(e)));
    DEFINE_DELTA_FUNCTION (rdelta, states, dst, hstate_t(e->from_));

  # undef DEFINE_DELTA_FUNCTION

  # define DEFINE_DELTAF_FUNCTION(FunName, DeltaKind, Target, IsBool, Action)	\
    BOOSTGRAPH_TPARAM								\
    template <typename Functor, typename Query>					\
    void									\
    BOOSTGRAPH::FunName(Functor& f,						\
                        const typename BOOSTGRAPH::hstate_t& s,			\
                        const Query& query,					\
                        ::vcsn::delta_kind::DeltaKind,				\
                        misc::IsBool##_t) const					\
    {										\
      assertion(has_state(s));							\
      Target##_range r = graph_.get<Target>().equal_range(s.value());		\
      for (Target##_iterator e = r.first; e != r.second; ++e)			\
        if (query(htransition_t(graph_.project<0>(e))))				\
        {									\
          Action;								\
        }									\
    }

    DEFINE_DELTAF_FUNCTION (deltaf, transitions, src, true, if (not f(hedge_t(graph_.project<0>(e)))) break);
    DEFINE_DELTAF_FUNCTION (deltaf, transitions, src, false, f(hedge_t(graph_.project<0>(e))));
    DEFINE_DELTAF_FUNCTION (deltaf, states, src, true, if (not f(hstate_t(e->to_))) break);
    DEFINE_DELTAF_FUNCTION (deltaf, states, src, false, f(hstate_t(e->to_)));

    DEFINE_DELTAF_FUNCTION (rdeltaf, transitions, dst, true, if (not f(hedge_t(graph_.project<0>(e)))) break);
    DEFINE_DELTAF_FUNCTION (rdeltaf, transitions, dst, false, f(hedge_t(graph_.project<0>(e))));
    DEFINE_DELTAF_FUNCTION (rdeltaf, states, dst, true, if (not f(hstate_t(e->from_))) break);
    DEFINE_DELTAF_FUNCTION (rdeltaf, states, dst, false, f(hstate_t(e->from_)));

  # undef DEFINE_DELTAF_FUNCTION

  # define DEFINE_DELTAF_FUNCTION(FunName, DeltaKind, Target, IsBool, Action)	\
    BOOSTGRAPH_TPARAM								\
    template <typename Functor, typename S, typename T>			        \
    void									\
    BOOSTGRAPH::FunName(Functor& f,						\
                        const typename BOOSTGRAPH::hstate_t& s,			\
                        const letter_query<S, T, label_t>& query,		\
                        ::vcsn::delta_kind::DeltaKind,				\
                        misc::IsBool##_t) const					\
    {									        \
      assertion(has_state(s));							\
      Target##_range r = graph_.get<Target>().equal_range(boost::make_tuple(s.value(), query.letter())); \
      for (Target##_iterator e = r.first; e != r.second; ++e)			\
	Action;									\
    }

    DEFINE_DELTAF_FUNCTION (deltaf, transitions, succ, true, if (not f(hedge_t(graph_.project<0>(e)))) break);
    DEFINE_DELTAF_FUNCTION (deltaf, transitions, succ, false, f(hedge_t(graph_.project<0>(e))));
    DEFINE_DELTAF_FUNCTION (deltaf, states, succ, true, if (not f(hstate_t(e->to_))) break);
    DEFINE_DELTAF_FUNCTION (deltaf, states, succ, false, f(hstate_t(e->to_)));

    DEFINE_DELTAF_FUNCTION (rdeltaf, transitions, pred, true, if (not f(hedge_t(graph_.project<0>(e)))) break);
    DEFINE_DELTAF_FUNCTION (rdeltaf, transitions, pred, false, f(hedge_t(graph_.project<0>(e))));
    DEFINE_DELTAF_FUNCTION (rdeltaf, states, pred, true, if (not f(hstate_t(e->from_))) break);
    DEFINE_DELTAF_FUNCTION (rdeltaf, states, pred, false, f(hstate_t(e->from_)));

  # undef DEFINE_DELTAF_FUNCTION
  # define DEFINE_DELTAF_FUNCTION(FunName, DeltaKind, Target, IsBool, Action)	\
    BOOSTGRAPH_TPARAM								\
    template <typename Functor, typename S, typename T>			        \
    void									\
    BOOSTGRAPH::FunName(Functor& f,						\
                        const typename BOOSTGRAPH::hstate_t& s,			\
                        const spontaneous_query<S, T>& query,			\
                        ::vcsn::delta_kind::DeltaKind,				\
                        misc::IsBool##_t) const					\
    {										\
      assertion(has_state(s));							\
      Target##_range r = graph_.get<Target>().equal_range(s.value(), 1);	\
      for (Target##_iterator e = r.first; e != r.second; ++e)			\
	Action;									\
    }

    DEFINE_DELTAF_FUNCTION (deltaf, transitions, succ, true, if (not f(hedge_t(graph_.project<0>(e)))) break);
    DEFINE_DELTAF_FUNCTION (deltaf, transitions, succ, false, f(hedge_t(graph_.project<0>(e))));
    DEFINE_DELTAF_FUNCTION (deltaf, states, succ, true, if (not f(hstate_t(e->to_))) break);
    DEFINE_DELTAF_FUNCTION (deltaf, states, succ, false, f(hstate_t(e->to_)));

    DEFINE_DELTAF_FUNCTION (rdeltaf, transitions, pred, true, if (not f(hedge_t(graph_.project<0>(e)))) break);
    DEFINE_DELTAF_FUNCTION (rdeltaf, transitions, pred, false, f(hedge_t(graph_.project<0>(e))));
    DEFINE_DELTAF_FUNCTION (rdeltaf, states, pred, true, if (not f(hstate_t(e->from_))) break);
    DEFINE_DELTAF_FUNCTION (rdeltaf, states, pred, false, f(hstate_t(e->from_)));

  # undef DEFINE_DELTAF_FUNCTION


    namespace deltaf_helper {
      template <typename T, typename R, typename Arg>
      char is_returning_bool_helper (R (T::*) (Arg));

      template <typename T, typename Arg>
      int is_returning_bool_helper (bool (T::*) (Arg));

  # define is_returning_bool(T)							\
      (sizeof (deltaf_helper::is_returning_bool_helper (T)) == sizeof (int))
    }

  # define DEFINE_DELTAF_HELPER(FunName)					\
    BOOSTGRAPH_TPARAM								\
    template <typename Functor, class Query, typename DeltaKind>		\
    void									\
    BOOSTGRAPH::FunName(Functor& f,						\
                    const typename BOOSTGRAPH::hstate_t& s,			\
                    const Query& query,						\
                    ::vcsn::delta_kind::kind<DeltaKind> k) const		\
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
  } // End of namespace boost
} // End of namespace vcsn

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_GRAPH_IMPL_HXX_ //
