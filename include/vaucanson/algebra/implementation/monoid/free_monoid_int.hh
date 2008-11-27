// free_monoid_int.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_INT_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_INT_HH

# include <vaucanson/algebra/implementation/monoid/monoid_rep.hh>
# include <vaucanson/algebra/implementation/series/series_rep.hh>
# include <vaucanson/algebra/implementation/monoid/free_monoid.hh>
# include <vaucanson/algebra/implementation/alphabets/alphabet_set.hh>

namespace vcsn
{
  namespace algebra
  {
    /*-------------------------------------------------------------.
    | Specialization of the monoid_rep structure for int letter    |
    | based free monoids.                                          |
    `-------------------------------------------------------------*/

    template <>
    struct monoid_rep<FreeMonoid<Element<AlphabetSet<int>, std::set<int> > > >
    {
      /// The representation of the empty word.
      std::string empty;

      /// The representation of the concatenation operation.
      std::string concat;

      std::vector<std::string> maybe_epsilon;

      monoid_rep();
    };

    /*-------------------------------------------------------------.
    | Specialization of the series_rep structure for int letter    |
    | based free monoids.                                          |
    `-------------------------------------------------------------*/

    template <typename Semiring>
    struct series_rep<Semiring,
		      FreeMonoid<Element<AlphabetSet<int>, std::set<int> > > >
    {
      std::string open_par;
      std::string close_par;
      std::string plus;
      std::string times;
      std::string star;
      std::string zero;
      std::string open_weight;
      std::string close_weight;
      std::vector<std::string> spaces;

      series_rep();
    };

  } // ! algebra

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/monoid/free_monoid_int.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_INT_HH
