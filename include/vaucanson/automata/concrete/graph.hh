// graph.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_CONCRETE_GRAPH_HH
# define VCSN_AUTOMATA_CONCRETE_GRAPH_HH

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/transducer_base.hh>
# include <vaucanson/automata/concept/automata_kind.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/concrete/kind_adapter.hh>
# include <vaucanson/misc/support.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <set>
# include <map>
# include <vector>


namespace vcsn {

  // Mixin class to add edge stuff to EdgeLabel.
  // The only precondition is that EdgeLabel must be a class.
  template <class EdgeLabel>
  struct edge_value
  {
    edge_value(const EdgeLabel&, hstate_t, hstate_t);
    edge_value();

    EdgeLabel	label;
    hstate_t    from;
    hstate_t	to;
  };

  // Mixin class to add state stuff to StateLabel.
  // The only precondition is that StateLabel must be a class.
  struct state_value
  {
    typedef std::list<hedge_t> edges_t;
    typedef std::list<hstate_t> states_t;
    edges_t  input_edges;
    edges_t  output_edges;
    states_t successors;
    states_t predecessors;
  };

  typedef utility::SparseInterval<hstate_t, std::set<hstate_t> >
  StateContainer;

  typedef utility::SparseInterval<hedge_t, std::set<hedge_t> >
  EdgeContainer;

  /**
   * @brief Graph class to provide a generic implementation of automaton.
   *
   * This class represents a  classic graph, but provides services and
   * uses a vocabulary which are specific to automata.
   *
   * It may be used as a generic implementation for automata.  This is
   * the  only implementation  in  Vaucanson which  can  be used  with
   * automata for the moment, but there should be other implementation
   * soon.
   *
   * @bug FIXME: This stuff is not sufficiently documented.
   */
  template <
    class K,
    class WordValue,
    class WeightValue,
    class SeriesValue,
    class Letter,
    class Tag>
  class Graph
  {
  public:
    typedef typename LabelOf<K, WordValue, WeightValue, SeriesValue, Letter>
    ::ret label_t;
    typedef Graph<K, WordValue, WeightValue, SeriesValue, Letter, Tag>
    self_t;
    typedef edge_value<label_t>			  edge_value_t;
    typedef SeriesValue				  series_value_t;
    typedef state_value				  state_value_t;
    typedef std::vector<state_value_t>		  state_data_t;
    typedef std::vector<edge_value_t>		  edge_data_t;
    typedef StateContainer			  states_t;
    typedef EdgeContainer			  edges_t;
    typedef std::map<hstate_t, series_value_t>	  initial_t;
    typedef std::map<hstate_t, series_value_t>     final_t;
    typedef utility::Support<initial_t>		  initial_support_t;
    typedef utility::Support<final_t>		  final_support_t;

  public:
    Graph();

    template <class S>
    bool			exists(const AutomataBase<S>& s) const;

    void			safe_del_state(hstate_t);
    
    hstate_t			add_state();
    void			del_state(hstate_t);
    bool			has_state(hstate_t) const;

    hedge_t			add_edge(hstate_t, hstate_t, const label_t&);
    void			del_edge(hedge_t);
    bool			has_edge(hedge_t) const;
    hedge_t			add_spontaneous(hstate_t, hstate_t);
    bool			is_spontaneous(hedge_t) const;
    hstate_t			origin_of(hedge_t) const;
    hstate_t			aim_of(hedge_t) const;
    const label_t&		label_of(hedge_t) const;

    initial_support_t		initial() const;
    void			set_initial(hstate_t, const series_value_t&,
					    const series_value_t&);
    const series_value_t&	get_initial(hstate_t,
					    const series_value_t&) const;
    void			clear_initial();

    final_support_t		final() const;
    void			set_final(hstate_t, const series_value_t&,
					  const series_value_t&);
    const series_value_t&	get_final(hstate_t,
					  const series_value_t&) const;
    void			clear_final();

    self_t&			clone() const;
    states_t			states() const;
    edges_t			edges() const;

    void			update(hedge_t, label_t);

    template <class OutputIterator, class Query>
    void			delta(OutputIterator res,
				      hstate_t from,
				      const Query& q,
				      delta_kind::edges) const;

    template <class OutputIterator, class Query>
    void			delta(OutputIterator res,
				      hstate_t from,
				      const Query& q,
				      delta_kind::states) const;

    template <class OutputIterator, class Query>
    void			rdelta(OutputIterator res,
				       hstate_t from,
				       const Query& q,
				       delta_kind::edges) const;

    template <class OutputIterator, class Query>
    void			rdelta(OutputIterator res,
				       hstate_t from,
				       const Query& q,
				       delta_kind::states) const;

    typedef Tag tag_t;
    tag_t& tag();
    const tag_t& tag() const;

  public:
    state_data_t		states_;
    edge_data_t			edges_;
    std::set<hstate_t>		removed_states_;
    int			        first_state_;
    std::set<hedge_t>		removed_edges_;
    int				first_edge_;
    final_t		        final_;
    initial_t		        initial_;
    tag_t			tag_;
  };

#define TParam \
  template <class S, class WordValue, class WeightValue, class SeriesValue, \
	    class Letter, class Tag>

  TParam
  ADAPT_ADD_LETTER_EDGE_TO_SERIES_LABEL(Graph<labels_are_series,
 					WordValue, WeightValue,
 					SeriesValue, Letter, Tag>);


  TParam
  ADAPT_LETTER_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				  WordValue, WeightValue,
				  SeriesValue, Letter, Tag>);

  TParam
  ADAPT_WORD_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				WordValue, WeightValue,
				SeriesValue, Letter, Tag>);

  TParam
  ADAPT_WORD_OF_TO_LETTERS_LABEL(Graph<labels_are_letters,
				 WordValue, WeightValue,
				 SeriesValue, Letter, Tag>);

  TParam
  ADAPT_SERIE_OF_TO_LETTERS_LABEL(Graph<labels_are_letters,
				  WordValue, WeightValue,
				  SeriesValue, Letter, Tag>);

  TParam
  ADAPT_ADD_SERIE_EDGE_TO_LETTERS_LABEL(Graph<labels_are_letters,
					WordValue, WeightValue,
					SeriesValue, Letter, Tag>);

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
    const edges_t& edges =
      v.states_[from].output_edges;
    for_each_const_(edges_t, e, edges)
      if (v.edges_[*e].label == letter)
	*res++ = v.edges_[*e].to;
  }

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
	    class Letter, class Tag, class I>
  Tag& op_tag(const AutomataBase<I>&,
	      Graph<Kind, WordValue, WeightValue,
		    SerieValue, Letter, Tag>&);
  
  template <class Kind, class WordValue, class WeightValue, class SerieValue,
            class Letter, class Tag, class I>
  const Tag& op_tag(const AutomataBase<I>&,
                    const Graph<Kind, WordValue, WeightValue,
                                SerieValue, Letter, Tag>&);

#undef TParam

  // This implementation can be used as an implementation of automaton.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag>
  struct automaton_traits<Graph<Kind,
				WordValue,
				WeightValue,
				SeriesValue,
				Letter,
				Tag>  >
  {
    typedef SeriesValue				     series_value_t;
    typedef WordValue				     word_value_t;
    typedef WordValue				     monoid_elt_value_t;
    typedef WeightValue				     semiring_elt_value_t;
    typedef Letter				     letter_t;
    typedef typename LabelOf<Kind, WordValue, WeightValue, SeriesValue, Letter>
    ::ret					     label_t;
    typedef Tag					     tag_t;
    typedef StateContainer			     states_t;

    typedef typename StateContainer::iterator	     state_iterator;
    typedef EdgeContainer			     edges_t;
    typedef typename EdgeContainer::iterator	     edge_iterator;
    typedef std::map<hstate_t, series_value_t>	     initial_t;
    typedef std::map<hstate_t, series_value_t>        final_t;
    typedef utility::Support<initial_t>		     initial_support_t;
    typedef utility::Support<final_t>		     final_support_t;
    typedef typename initial_support_t::iterator     initial_iterator;
    typedef typename final_support_t::iterator	     final_iterator;
    typedef edge_value<label_t>			     edge_value_t;
    typedef state_value				     state_value_t;
    typedef std::vector<state_value_t>		     state_data_t;
    typedef std::vector<edge_value_t>		     edge_data_t;
  };

  // This implementation can be used as a transducer one.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag>
  struct transducer_traits<Graph<Kind,
				 WordValue,
				 WeightValue,
				 SeriesValue,
				 Letter,
				 Tag>  >
  {
    typedef WordValue			input_monoid_elt_value_t;
    typedef typename algebra::series_traits<WeightValue>::monoid_value_t
    output_monoid_elt_value_t;
    typedef typename algebra::series_traits<WeightValue>::semiring_elt_value_t
    output_semiring_elt_value_t;
  };

  // Explain how to project type of transducer into input automaton type.
  template <class S,
	    class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag>
  struct projection_traits<S, Graph<Kind,
				    WordValue,
				    WeightValue,
				    SeriesValue,
				    Letter,
				    Tag>  >
  {
    typedef Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag>
    self_t;
    typedef typename transducer_traits<self_t>::output_semiring_elt_value_t
    semiring_elt_value_t;
    typedef typename transducer_traits<self_t>::input_monoid_elt_value_t
    monoid_value_t;
    typedef typename algebra::mute_series_impl<SeriesValue,
					      semiring_elt_value_t,
					      monoid_value_t>
    ::ret series_value_t;

    typedef
    Graph<Kind,
	  monoid_value_t,
	  semiring_elt_value_t,
	  series_value_t,
	  Letter,
	  Tag>
    ret;
  };

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag>
  struct output_projection_traits<Graph<Kind,
					   WordValue,
					   WeightValue,
					   SeriesValue,
					   Letter,
					   Tag>  >
  {
    typedef Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag>
    self_t;

    typedef typename automaton_traits<self_t>::semiring_elt_value_t
    series_elt_value_t;

    typedef typename
    algebra::series_traits<series_elt_value_t>::monoid_value_t
    monoid_value_t;

    typedef typename
    algebra::series_traits<series_elt_value_t>::semiring_elt_value_t
    semiring_elt_value_t;

    typedef
    Graph<Kind,
	  monoid_value_t,
	  semiring_elt_value_t,
	  series_elt_value_t,
	  Letter,
	  Tag>
    ret;
  };

  // Explain how to extend an input automaton into a transducer.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag>
  struct extension_traits<Graph<Kind,
				WordValue,
				WeightValue,
				SeriesValue,
				Letter,
				Tag>  >
  {
    typedef Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag>
    self_t;
    typedef typename automaton_traits<self_t>::monoid_elt_value_t
    monoid_value_t;
    typedef typename algebra::mute_series_impl<SeriesValue, SeriesValue, monoid_value_t>
    ::ret series_value_t;

    typedef
    Graph<Kind,
	  monoid_value_t,
	  SeriesValue,
	  series_value_t,
	  Letter,
	  Tag>
    ret;
  };

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/automata/concrete/graph.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_AUTOMATA_CONCRETE_GRAPH_HH
