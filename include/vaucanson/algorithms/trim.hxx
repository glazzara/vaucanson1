// trim.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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


#ifndef ALGORITHMS_TRIM_HXX
# define ALGORITHMS_TRIM_HXX

# include <vaucanson/algorithms/trim.hh>

# include <iterator>
# include <algorithm>
# include <set>
# include <queue>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algorithms/extract.hh>
# include <vaucanson/algorithms/reachable.hh>

namespace vcsn {

  /*---------------------.
  | do_start_trim_states |
  `---------------------*/
  // preconditions :
  //
  //
  template <class A_, typename Auto_>
  std::set<hstate_t>
  do_useful_states(const AutomataBase<A_>& a_set,
		   const Auto_&		   a)
  {
    std::set<hstate_t> start = start_reachable_states(a);
    std::set<hstate_t> final = final_reachable_states(a);
    std::set<hstate_t> result;
    std::insert_iterator<std::set<hstate_t> > i(result, result.begin());

    set_intersection(start.begin(), start.end(), final.begin(), final.end(), i);
    return result;
  }

  template<typename A, typename T>
  std::set<hstate_t>
  useful_states(const Element<A, T>& a)
  {
    return do_useful_states(a.set(), a);
  }

  template<typename A, typename T>
  Element<A, T>
  trim(const Element<A, T>& a)
  {
    return auto_extract(a, useful_states(a));
  }

} // vcsn

#endif // ALGORITHMS_TRIM_HXX
