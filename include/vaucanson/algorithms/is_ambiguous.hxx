// is_ambiguous.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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

#ifndef VCSN_ALGORITHMS_IS_AMBIGUOUS_HXX
# define VCSN_ALGORITHMS_IS_AMBIGUOUS_HXX

# include <vaucanson/algorithms/is_ambiguous.hh>
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/algorithms/product.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <map>
# include <set>

namespace vcsn {

  /*-------------.
  | is_ambiguous |
  `-------------*/
  template <typename A_, typename Auto_>
  bool
  do_is_ambiguous(const AutomataBase<A_>&,
		  const Auto_&	aut)
  {
    typedef typename Auto_::hstate_t hstate_t;

    // This map is used to know which state is created by which two ones.
    std::map<hstate_t, std::pair<hstate_t, hstate_t> >  m;
    const std::set<hstate_t>& s = useful_states (product (aut, aut, m));
    for_all_const_ (std::set<hstate_t>, i, s)
      if (m[*i].first != m[*i].second)
	return true;
    return false;
  }

  template<typename A_, typename Auto_>
  bool
  is_ambiguous(const Element<A_, Auto_>& aut)
  {
    TIMER_SCOPED("is_ambiguous");
    return do_is_ambiguous(aut.structure(), aut);
  }

} // End of namespace vcsn.

#endif // ! VCSN_ALGORITHMS_IS_AMBIGUOUS_HXX
