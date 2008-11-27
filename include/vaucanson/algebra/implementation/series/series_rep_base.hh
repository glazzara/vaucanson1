// series_rep_base.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_BASE_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_BASE_HH

# include <vector>
# include <string>

# include <boost/shared_ptr.hpp>

# include <vaucanson/misc/usual_macros.hh>

namespace vcsn
{
  namespace algebra
  {
    template <template <typename, typename> class B, typename S, typename M>
    struct SeriesRepBase
    {
      // The type of the semiring.
      typedef S					semiring_t;

      // The type of the monoid.
      typedef M					monoid_t;

      // The most derived type in the hierarchy.
      typedef B<semiring_t, monoid_t>		self_t;

      // Pointer types.
      typedef boost::shared_ptr<self_t>		pointer_t;

      // Basic structure attributes.
      std::string		open_par;
      std::string		close_par;
      std::string		plus;
      std::string		times;
      std::string		star;
      std::string		zero;
      std::string		open_weight;
      std::string		close_weight;
      std::vector<std::string>	spaces;
      std::vector<std::string>	maybe_zero;

      // Default CTOR
      SeriesRepBase();

      // Disambiguate the tokens w.r.t. a monoid.
      void disambiguate(const monoid_t&, pointer_t&);
    };

    template <template <typename, typename> class B, typename S, typename M>
    bool operator==(boost::shared_ptr<SeriesRepBase<B, S, M> >,
		    boost::shared_ptr<SeriesRepBase<B, S, M> >);

  } // ! algebra

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/series/series_rep_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_BASE_HH
