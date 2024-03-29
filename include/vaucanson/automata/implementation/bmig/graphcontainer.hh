// graphcontainer.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPHCONTAINER_HH_
# define VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPHCONTAINER_HH_

# include <vaucanson/misc/hash.hh>
# include <vaucanson/automata/implementation/bmig/edge_value.hh>
# include <boost/multi_index_container.hpp>
# include <boost/multi_index/member.hpp>
# include <boost/multi_index/ordered_index.hpp>
# include <boost/multi_index/hashed_index.hpp>
# include <boost/functional/hash/hash.hpp>
# include <boost/multi_index/sequenced_index.hpp>
# include <boost/tuple/tuple.hpp>
# include <boost/multi_index/composite_key.hpp>

namespace vcsn
{
  namespace bmig
  {
    using ::boost::multi_index_container;
    using ::boost::multi_index::hashed_non_unique;
    using ::boost::multi_index::indexed_by;
    using ::boost::multi_index::composite_key;
    using ::boost::multi_index::hashed_non_unique;
    using ::boost::multi_index::tag;
    using ::boost::multi_index::member;
    using ::boost::multi_index::index_iterator;
    using ::boost::multi_index::get;
    using ::boost::multi_index::project;
    using ::boost::multi_index::composite_key_hash;

    /*---------------------------------------------------------\
      | Declaring the Boost multi_index used to store the graph. |
      `---------------------------------------------------------*/

    // Empty structure to name the different keys.
    struct succ {};
    struct pred {};
    struct src {};
    struct dst {};

    // Composite key (source, label)
    template<typename State, typename HLabel, typename EdgeValue>
    struct SuccessorKey : composite_key <
      EdgeValue,
      BOOST_MULTI_INDEX_MEMBER(EdgeValue, State, from_),
      BOOST_MULTI_INDEX_MEMBER(EdgeValue, HLabel, label_)
    > {};

    // Composite key (target, label)
    template<typename State, typename HLabel, typename EdgeValue>
    struct PredecessorKey : composite_key <
      EdgeValue,
      BOOST_MULTI_INDEX_MEMBER(EdgeValue, State, to_),
      BOOST_MULTI_INDEX_MEMBER(EdgeValue, HLabel, label_)
    > {};

    // Use composite keys in hash tables.
    template<typename State, typename HLabel, typename EdgeValue>
    struct SourceAndLabel : public hashed_non_unique <
      tag<succ>,
      SuccessorKey<State, HLabel, EdgeValue>,
      composite_key_hash<
	vcsn::misc::hash_state_handler,
	vcsn::misc::hash_label<HLabel>
	//vcsn::misc::hash_handler<HLabel>
      >
    > {};

    template<typename State, typename HLabel, typename EdgeValue>
    struct DestinationAndLabel : public hashed_non_unique <
      tag<pred>,
      PredecessorKey<State, HLabel, EdgeValue>,
      composite_key_hash<
	vcsn::misc::hash_state_handler,
	vcsn::misc::hash_label<HLabel>
	//vcsn::misc::hash_handler<HLabel>
      >
    > {};


    // Single key (source)
    template<typename State, typename EdgeValue>
    struct Source : public hashed_non_unique <
      tag<src>,
      BOOST_MULTI_INDEX_MEMBER(EdgeValue, State, from_),
      vcsn::misc::hash_state_handler
    > {};


    // Single key (target)
    template<typename State, typename EdgeValue>
    struct Destination : public hashed_non_unique <
      tag<dst>,
      BOOST_MULTI_INDEX_MEMBER(EdgeValue, State, to_),
      vcsn::misc::hash_state_handler
    > {};


    /*!
    ** Actual graph structure.
    **
    ** Provides constant time access to specific data
    ** according the following keys:
    **
    ** - (src), get all transitions from a given state.
    ** - (dst), get all transitions going to a given state.
    ** - (src, label), get all transitions from a given state with a given label.
    ** - (dst, label), get all transitions going to a given state with a given label.
    **
    ** \sa EdgeValue, update_label
    */
    template<typename State, typename HLabel, typename EdgeValue>
    struct GraphContainer
      : public multi_index_container
    <
      EdgeValue,
      indexed_by
      <
	SourceAndLabel<State, HLabel, EdgeValue>,
	DestinationAndLabel<State, HLabel, EdgeValue>,
	Source<State, EdgeValue>,
	Destination<State, EdgeValue>
      >
    > {};

  } // bmig
} // vcsn

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPHCONTAINER_HH_

