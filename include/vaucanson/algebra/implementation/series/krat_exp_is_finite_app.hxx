// krat_exp_is_finite_app.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_IS_FINITE_APP_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_IS_FINITE_APP_HXX

# include <utility>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

namespace vcsn {

  template <class Series, class T, class Dispatch>
  class IsFiniteAppMatcher : public algebra::KRatExpMatcher<
    IsFiniteAppMatcher<Series, T, Dispatch>,
    T,
    bool,
    Dispatch
    >
  {
  public:
    typedef IsFiniteAppMatcher<Series, T, Dispatch>	self_t;
    typedef bool				        return_type;
    INHERIT_CONSTRUCTORS(self_t, T, return_type, Dispatch);

    IsFiniteAppMatcher()
    {}

    MATCH__(Product, lhs, rhs)
    {
      return this->match(lhs) && this->match(rhs);
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      return this->match(lhs) && this->match(rhs);
    }
    END

    MATCH_(Star, node)
    {
      return false;
    }
    END

    MATCH__(LeftWeight, w, node)
    {
      (void) w;
      return this->match(node);
    }
    END

    MATCH__(RightWeight, node, w)
    {
      (void) w;
      return this->match(node);
    }
    END

    MATCH_(Constant, m)
    {
      return true;
    }
    END

    MATCH(Zero)
    {
      return true;
    }
    END

    MATCH(One)
    {
      return true;
    }
    END

  };

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_IS_FINITE_APP_HXX
