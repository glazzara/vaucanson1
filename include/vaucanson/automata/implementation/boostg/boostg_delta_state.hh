// graphcontainer.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_DELTA_STATE_HH_
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_DELTA_STATE_HH_

# include <vaucanson/automata/implementation/boostg/boostg_functors.hh>
# include <boost/multi_index_container.hpp>
# include <boost/multi_index/member.hpp>
# include <boost/multi_index/ordered_index.hpp>

namespace vcsn
{
  namespace boostg
  {
    using ::boost::multi_index_container;
    using ::boost::multi_index::indexed_by;
    using ::boost::multi_index::const_mem_fun;
    using ::boost::multi_index::ordered_non_unique;

    template<typename HState>
    struct DeltaState
      : public multi_index_container<
	    HState,
	    indexed_by<
	        ordered_non_unique<
		  const_mem_fun<HState, unsigned*, &HState::value>,
		  state_less_op<HState>
		>
	    >
	> {};

  } // boostg
} // vcsn

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_DELTA_STATE_HH_

