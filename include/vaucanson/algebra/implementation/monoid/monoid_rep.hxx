// monoid_rep.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_HXX

# include <vaucanson/algebra/implementation/monoid/monoid_rep.hh>

namespace vcsn {

  namespace algebra {

    template <typename Monoid>
    monoid_rep<Monoid>::monoid_rep()
    {
      maybe_epsilon.clear();

      // Sane defaults.
      maybe_epsilon.push_back("1");
      maybe_epsilon.push_back("e");

      // Trying with more than one char.
      maybe_epsilon.push_back("_e");
      maybe_epsilon.push_back("eps");

      empty = *(maybe_epsilon.begin());
      concat = "";
    }

    template <typename M>
    bool
    operator==(boost::shared_ptr<monoid_rep<M> > lhs,
	       boost::shared_ptr<monoid_rep<M> > rhs )
    {
      return (lhs->empty == rhs->empty &&
	      lhs->concat == rhs->concat);
    }

  } // ! algebra

} // ! vcsn

#endif // !VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_HXX
