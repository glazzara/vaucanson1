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

# define EXACT_TYPE FreeMonoid<Element<AlphabetSet<int>, std::set<int> > >

    inline
    MonoidRep<EXACT_TYPE>::MonoidRep()
    {
      // Discard any initialization by the parent class.
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
    SeriesRep<Semiring, EXACT_TYPE>::SeriesRep()
    {
      // Discard any initialization by the parent class.
      this->maybe_zero.clear();
      this->spaces.clear();

      // Sane defaults.
      this->maybe_zero.push_back("z");
      this->maybe_zero.push_back("0");

      // Trying with more than one char.
      this->maybe_zero.push_back("_z");
      this->maybe_zero.push_back("zero");

      this->zero = *(this->maybe_zero.begin());
      this->open_par = "(";
      this->close_par = ")";
      this->plus = "+";
      this->times = ".";
      this->star = "*";
      this->open_weight = "{";
      this->close_weight = "}";
      this->spaces.push_back(" ");
    }

# undef EXACT_TYPE

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_INT_HXX
