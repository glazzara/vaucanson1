// monoid_rep_base.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_BASE_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_BASE_HH

# include <vector>
# include <string>

# include <boost/shared_ptr.hpp>

# include <vaucanson/misc/usual_macros.hh>

namespace vcsn
{
  namespace algebra
  {
    template <template <typename> class S, typename T>
    struct MonoidRepBase
    {
      // The type of the monoid.
      typedef T					monoid_t;

      // The most derived type in the hierarchy.
      typedef S<monoid_t>			self_t;

      // Pointer types.
      typedef boost::shared_ptr<self_t>		pointer_t;

      // Basic structure attributes.
      std::string		empty;
      std::string		concat;
      std::vector<std::string>	maybe_epsilon;

      // Default CTOR.
      MonoidRepBase();

      // Disambiguate the tokens w.r.t. a monoid.
      void disambiguate(const monoid_t&, pointer_t&);
    };

    template <template <typename> class S, typename T>
    bool operator==(boost::shared_ptr<MonoidRepBase<S, T> >,
		    boost::shared_ptr<MonoidRepBase<S, T> >);

  } // ! algebra

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/monoid/monoid_rep_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_BASE_HH
