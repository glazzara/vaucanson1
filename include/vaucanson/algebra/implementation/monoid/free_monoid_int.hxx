// free_monoid_int.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_INT_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_INT_HXX

# include <vaucanson/algebra/implementation/monoid/free_monoid_int.hh>

namespace vcsn
{
  namespace algebra
  {
    inline
    monoid_rep<FreeMonoid<Element<AlphabetSet<int>, std::set<int> > > >::monoid_rep()
    {
      maybe_epsilon.clear();

      // Sane defaults.
      maybe_epsilon.push_back("e");
      maybe_epsilon.push_back("1");

      // Trying with more than one char.
      maybe_epsilon.push_back("_e");
      maybe_epsilon.push_back("eps");

      empty = *(maybe_epsilon.begin());
      concat = "#";
    }

    template <typename Semiring>
    series_rep<Semiring, FreeMonoid<Element<AlphabetSet<int>, std::set<int> > > >::series_rep() :
      open_par("("),
      close_par(")"),
      plus("+"),
      times("."),
      star("*"),
      zero("z"),
      open_weight("{"),
      close_weight("}")
    {
      spaces.push_back(" ");
    }

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_INT_HXX
