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
#ifndef VAUCANSON_AUTOMATA_IMPLEMENTATION_BMIG_ITERATOR_HH
# define VAUCANSON_AUTOMATA_IMPLEMENTATION_BMIG_ITERATOR_HH

# include <map>

namespace vcsn
{
  namespace bmig
  {
    /**
    ** Iterators use to iterate over subsets of successor/predecessor
    ** transitions.
    **
    ** Graph is the type of automata implementation.
    ** I is the type of iterators used on the subset.
    */
    template <typename Graph, typename I>
    class DeltaConstIterator
    {
      public:
	/// The type of automata implementation
	typedef Graph					graph_type;
	/// The type of iterators used on the subset
	typedef I					iterator_type;
	/// Type of the pair used to define the couple begin/end
	typedef std::pair<I, I>				range_type;
	typedef DeltaConstIterator<Graph, I>		self_t;

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
	typename graph_type::htransition_t	operator*() const;

      private:
	const graph_type&	graph_;
	iterator_type		i_;
	iterator_type		end_;

    }; // End of class DeltaConstIterator

  } // End of namespace bmig

} // End of namespace vcsn

# if !defined VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/automata/implementation/bmig/iterator.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VAUCANSON_AUTOMATA_IMPLEMENTATION_BMIG_ITERATOR_HH
