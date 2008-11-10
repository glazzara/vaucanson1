// series_rep.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_HXX

namespace vcsn {

  namespace algebra {

    template <typename Semiring, typename Monoid>
    series_rep<Semiring, Monoid>::series_rep() :
      open_par("("),
      close_par(")"),
      plus("+"),
      times("."),
      star("*"),
      zero("0"),
      open_weight("{"),
      close_weight("}")
    {
      spaces.push_back(" ");
    }

    template <typename S, typename M>
    bool
    operator==(boost::shared_ptr<series_rep<S, M> > lhs,
	       boost::shared_ptr<series_rep<S, M> > rhs)
    {
      return (lhs->open_par == rhs->open_par &&
	      lhs->close_par == rhs->close_par &&
	      lhs->plus == rhs->plus &&
	      lhs->times == rhs->times &&
	      lhs->star == rhs->star &&
	      lhs->zero == rhs->zero &&
	      lhs->open_weight == rhs->open_weight &&
	      lhs->close_weight == rhs->close_weight &&
	      lhs->spaces == rhs->spaces);
    }

  } // ! algebra

} // ! vcsn

#endif // !VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_HXX
