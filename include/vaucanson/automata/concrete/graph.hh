// graph.hh
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

#ifndef VCSN_AUTOMATA_CONCRETE_GRAPH_HH
# define VCSN_AUTOMATA_CONCRETE_GRAPH_HH

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/automata_kind.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/concrete/kind_adapter.hh>
# include <vaucanson/misc/support.hh>
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
    std::set<hedge_t>  input_edges;
    std::set<hedge_t>  output_edges;
    std::set<hstate_t> successors;
    std::set<hstate_t> predecessors;
  };

  typedef SparseInterval<hstate_t, std::set<hstate_t> > StateContainer;
  typedef SparseInterval<hedge_t, std::set<hedge_t> > EdgeContainer;

  template <
    class K,
    class WordValue,
    class WeightValue,
    class SerieValue,
    class Letter,
    class Tag>
  class Graph
  {
  public:
    typedef typename LabelOf<K, WordValue, WeightValue, SerieValue, Letter>
    ::ret label_t;
    typedef Graph<K, WordValue, WeightValue, SerieValue, Letter, Tag>
    self_t;
    typedef edge_value<label_t>			  edge_value_t;
    typedef SerieValue				  serie_value_t;
    typedef state_value				  state_value_t;
    typedef std::vector<state_value_t>		  state_data_t;
    typedef std::vector<edge_value_t>		  edge_data_t;
    typedef StateContainer			  states_t;
    typedef EdgeContainer			  edges_t;
    typedef std::map<hstate_t, serie_value_t>	  initial_t;
    typedef std::map<hstate_t, serie_value_t>     final_t;
    typedef Support<initial_t>			  initial_support_t;
    typedef Support<final_t>			  final_support_t;

  public:      
    Graph();

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
    void			set_initial(hstate_t, const serie_value_t&,
					    const serie_value_t&);
    const serie_value_t&	get_initial(hstate_t,
					    const serie_value_t&) const;
    void			clear_initial();

    final_support_t		final() const;
    void			set_final(hstate_t, const serie_value_t&,
					  const serie_value_t&);
    const serie_value_t&	get_final(hstate_t, 
					  const serie_value_t&) const;
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

  protected:
    state_data_t		states_;
    edge_data_t			edges_;
    std::set<hstate_t>		removed_states_;
    int			        first_state_;
    std::set<hedge_t>		removed_edges_;
    int				first_edge_;
    final_t		        final_;
    initial_t		        initial_;
  };

#define TParam \
  template <class S, class WordValue, class WeightValue, class SerieValue, \
	    class Letter, class Tag>

  TParam
  ADAPT_ADD_LETTER_EDGE_TO_SERIES_LABEL(Graph<labels_are_series,
 					WordValue, WeightValue,
 					SerieValue, Letter, Tag>);


  TParam
  ADAPT_LETTER_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				  WordValue, WeightValue,
				  SerieValue, Letter, Tag>);

  TParam
  ADAPT_WORD_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				WordValue, WeightValue,
				SerieValue, Letter, Tag>);
#undef TParam

  // This implementation can be used as an implementation of automaton.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SerieValue,
	    class Letter,
	    class Tag>
  struct automaton_traits<Graph<Kind, 
				WordValue, 
				WeightValue, 
				SerieValue, 
				Letter,
				Tag>  >
  {
    typedef SerieValue				     serie_value_t;
    typedef WordValue				     word_value_t;
    typedef WeightValue				     weight_value_t;
    typedef Letter				     letter_t;
    typedef typename LabelOf<Kind, WordValue, WeightValue, SerieValue, Letter>
    ::ret					     label_t;
    typedef Tag					     tag_t;
    typedef StateContainer			     states_t;

    typedef typename StateContainer::iterator	     state_iterator;
    typedef EdgeContainer			     edges_t;
    typedef typename EdgeContainer::iterator	     edge_iterator;
    typedef std::map<hstate_t, serie_value_t>	     initial_t;
    typedef std::map<hstate_t, serie_value_t>        final_t;
    typedef Support<initial_t>			     initial_support_t;
    typedef Support<final_t>			     final_support_t;
    typedef typename Support<initial_t>::iterator    initial_iterator;

    typedef typename Support<final_t>::iterator	     final_iterator;
    typedef edge_value<label_t>			     edge_value_t;
    typedef state_value				     state_value_t;
    typedef std::vector<state_value_t>		     state_data_t;
    typedef std::vector<edge_value_t>		     edge_data_t;
  };

  // This implementation can be used as a transducer one.
//   template <class Kind,
// 	    class WordValue,
// 	    class WeightValue,
// 	    class SerieValue,
// 	    class Letter,
// 	    class Tag>
//   struct transducer_traits<Graph<Kind, 
// 				 WordValue, 
// 				 WeightValue, 
// 				 SerieValue, 
// 				 Letter,
// 				 Tag>  > 
//   {
//     typedef WordValue			input_monoid_elt_value_t;
//     typedef typename series_traits<WeightValue>::monoid_elt_value_t 
//     output_monoid_elt_value_t;
//     typedef typename series_traits<WeightValue>::weight_value_t
//     output_weight_value_t;
//   };

} // vcsn

# include <vaucanson/automata/concrete/graph.hxx>

#endif // VCSN_AUTOMATA_CONCRETE_GRAPH_HH
