// krat_exp_flatten.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//

#ifndef VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HXX

# include <vaucanson/algorithms/krat_exp_flatten.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>

namespace vcsn
{
  /** @addtogroup algorithms */ /** @{ */

  template <class Series, class T, class Dispatch>
  struct KRatExpFlatten : algebra::KRatExpMatcher<
    KRatExpFlatten<Series, T, Dispatch>,
    T,
    std::list<typename Series::monoid_t::alphabet_t::letter_t>,
    Dispatch
    >
  {
    typedef KRatExpFlatten<Series, T, Dispatch>		self_t;
    typedef typename Element<Series, T>::semiring_elt_t	semiring_elt_t;
    typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
    typedef typename Element<Series, T>::monoid_elt_t	monoid_elt_t;
    typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
    typedef typename monoid_elt_t::set_t		monoid_t;
    typedef typename monoid_t::alphabet_t		alphabet_t;
    typedef typename alphabet_t::letter_t		letter_t;
    typedef std::list<typename Series::monoid_t::alphabet_t::letter_t>
							return_type;
    INHERIT_CONSTRUCTORS(self_t, T, return_type, Dispatch);

    KRatExpFlatten(const Element<Series, T>& exp) : exp_(exp), res_ ()
    {
    }

    return_type
    flatten()
    {
      return match(exp_.value());
    }

    MATCH__(Product, lhs, rhs)
    {
      match(lhs);
      match(rhs);
      return res_;
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      match(lhs);
      match(rhs);
      return res_;
    }
    END

    MATCH_(Star, e)
    {
      match(e);
      return res_;
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      w = w; // Dirty trick to avoid warinings.
      match(e);
      return res_;
    }
    END

    MATCH__(RightWeight, e, w)
    {
      w = w; // Dirty trick to avoid warinings.
      match(e);
      return res_;
    }
    END

    MATCH_(Constant, m)
    {
      for (size_t i = 0; i < m.length(); ++i)
	res_.push_back(m[i]);
      return res_;
    }
    END

    MATCH(Zero)
    {
      return res_;
    }
    END

    MATCH(One)
    {
      return res_;
    }
    END

  private:
    Element<Series, T>	exp_;
    return_type		res_;
  };

  template <class Series, class T>
  std::list<typename Series::monoid_t::alphabet_t::letter_t>
  flatten(const Element<Series, T>& exp)
  {
    KRatExpFlatten< Series, T, algebra::DispatchFunction<T> > matcher(exp);
    return matcher.flatten();
  }

  /** @} */

} // end of namepsace vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HXX

