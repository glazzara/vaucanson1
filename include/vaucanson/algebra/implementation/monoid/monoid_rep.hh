// monoid_rep.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_HH

# include <string>

# include <boost/shared_ptr.hpp>

namespace vcsn {

  namespace algebra {

    template <typename Monoid>
    struct monoid_rep
    {
      std::string	empty;

      // Default CTOR
      monoid_rep();

    };

    template <typename M>
    bool operator==(boost::shared_ptr<monoid_rep<M> >,
		    boost::shared_ptr<monoid_rep<M> >);

    template <typename Monoid>
    struct monoid_rep_default
    {
      static boost::shared_ptr<monoid_rep<Monoid> > get_instance()
      {
	static boost::shared_ptr<monoid_rep<Monoid> > p(new monoid_rep<Monoid>);
	return p;
      }
    };

  } // ! algebra

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/monoid/monoid_rep.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_HH
