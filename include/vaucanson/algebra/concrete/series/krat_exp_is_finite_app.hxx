// krat_exp_is_finite_app.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey 
// and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_ALGORITHMS_KRAT_EXP_IS_FINITE_APP_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_IS_FINITE_APP_HXX

# include <utility>
# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>

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
      return match_(lhs) && match(rhs);
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      return match(lhs) && match(rhs);
    }
    END

    MATCH_(Star, node)
    {
      return false;
    }
    END

    MATCH__(LeftWeight, w, node)
    {
      return match(node);
    }
    END

    MATCH__(RightWeight, node, w)
    {
      return match(node);
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

#endif // VCSN_ALGORITHMS_KRAT_EXP_IS_FINITE_APP_HXX
