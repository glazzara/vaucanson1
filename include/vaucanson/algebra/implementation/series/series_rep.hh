// series_rep.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_HH

# include <string>
# include <vector>

# include <boost/shared_ptr.hpp>

namespace vcsn {

  namespace algebra {

    template <typename Semiring, typename Monoid>
    struct series_rep
    {
      std::string		open_par;
      std::string		close_par;
      std::string		plus;
      std::string		times;
      std::string		star;
      std::string		zero;
      std::string		open_weight;
      std::string		close_weight;
      std::vector<std::string>	spaces;

      // Default CTOR
      series_rep();
    };

    template <typename S, typename M>
    bool operator==(boost::shared_ptr<series_rep<S, M> >,
		    boost::shared_ptr<series_rep<S, M> >);

    template <typename Semiring, typename Monoid>
    struct series_rep_default
    {
      static boost::shared_ptr<series_rep<Semiring, Monoid> > get_instance()
      {
	static boost::shared_ptr<series_rep<Semiring, Monoid> > p(new series_rep<Semiring, Monoid>);
	return p;
      }
    };

  } // ! algebra

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/series/series_rep.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_HH
