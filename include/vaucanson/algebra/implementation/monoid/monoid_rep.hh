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

# include <boost/shared_ptr.hpp>

# include <vaucanson/algebra/implementation/monoid/monoid_rep_base.hh>

namespace vcsn
{
  namespace algebra
  {
    template <typename M>
    struct MonoidRep : MonoidRepBase<MonoidRep, M>
    {
    };

    template <typename M>
    bool operator==(boost::shared_ptr<MonoidRep<M> >,
		    boost::shared_ptr<MonoidRep<M> >);

    template <typename M>
    struct MonoidRepDefault
    {
      // Type helpers.
      typedef MonoidRep<M>			monoid_rep_t;
      typedef boost::shared_ptr<monoid_rep_t>	pointer_t;

      // Singleton instance getter.
      static pointer_t get_instance()
      {
	static pointer_t p(new monoid_rep_t());
	return p;
      }
    };

  } // ! algebra

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/monoid/monoid_rep.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_HH
