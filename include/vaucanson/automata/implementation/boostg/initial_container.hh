// initial_container.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_INITIAL_CONTAINER_HH_
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_INITIAL_CONTAINER_HH_

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
  namespace boostg
  {

    /*!
    ** Multi_index used to store initial and final states information.
    **
    ** It is ordered and indexed by the state.
    */
    template <typename U, typename HState>
    struct InitialContainer
    {

      typedef boost::multi_index_container
	<
	U,
      boost::multi_index::indexed_by
	<
	boost::multi_index::ordered_non_unique<
	BOOST_MULTI_INDEX_MEMBER(U, HState, first)
	>
	>
	> Type;
    };

  } //boostg
} //vcsn

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_INITIAL_CONTAINER_HH_

