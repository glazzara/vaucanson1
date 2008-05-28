// iterator.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef VAUCANSON_AUTOMATA_IMPLEMENTATION_LISTG_ITERATOR_HH
# define VAUCANSON_AUTOMATA_IMPLEMENTATION_LISTG_ITERATOR_HH

# include <set>

namespace vcsn
{
  namespace listg
  {
    class backward_iterator { };
    class forward_iterator { };

    /**
    ** Iterators use to iterate over subsets of successor/predecessor
    ** states or transitions.
    **
    ** Graph is the type of automata implementation.
    ** Handler is the type of handlers it shall return.
    ** Direction indicates if we want successors or predecessors.
    */
    template <typename Graph, typename Handler, typename Direction>
    class DeltaConstIterator
    {
      public:
	/// The type of automata implementation
	typedef Graph						graph_type;
	/// The type of handlers it shall return
	typedef Handler						data_type;
	/// The type of the container it wraps
	typedef std::set<typename graph_type::htransition_t>	container_type;
	/// The type of iterator used on container_type
	typedef typename container_type::iterator		iterator_type;
	/// Indicates if we want successors or predecessors.
	typedef Direction					direction;
	typedef DeltaConstIterator<Graph, Handler, Direction>	self_t;

	/**
	** Initialize the iterator.
	** @param g	the automaton implementation
	** @param s	the starting state
	*/
        DeltaConstIterator(const graph_type& g, typename graph_type::hstate_t s);
        ~DeltaConstIterator();

	/**
	** Step toward the next item.
	*/
	void		next();
	/**
	** Tell if all the items have been visited.
	** Return true if there is no more item to visit and false otherwise.
	*/
	bool		done() const;

	/**
	** Access the current item.
	*/
	data_type	operator*() const;

      private:
	const graph_type&		graph_;
	typename graph_type::hstate_t	s_;
	iterator_type			i_;
	iterator_type			end_;

	/*
	** Internal use
	** Initialize the i_ and end_ based on whether we want to iterate
	** over the successors or the predecessors.
	*/
	void		initialize(const backward_iterator&);
	void		initialize(const forward_iterator&);

    }; // End of class DeltaConstIterator

  } // End of namespace listg

} // End of namespace vcsn

# if !defined VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/automata/implementation/listg/iterator.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VAUCANSON_AUTOMATA_IMPLEMENTATION_LISTG_ITERATOR_HH
