// krat_exp_constant_term.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_CONSTANT_TERM_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_CONSTANT_TERM_HXX

# include <utility>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>

namespace vcsn {

  /**
   * @brief This is the visitor that really computes the constant term.
   *
   * This class should be used  only in constant_term() and should not
   * be instanciated from elsewhere.
   *
   * @see constant_term()
   */
  template <class Series, class T, class Dispatch>
  class ConstantTermEval : public algebra::KRatExpMatcher<
    ConstantTermEval<Series, T, Dispatch>,
    T,
    typename Element<Series, T>::semiring_elt_t,
    Dispatch
    >
  {
  public:
    typedef ConstantTermEval<Series, T, Dispatch>	self_t;
    typedef typename Element<Series, T>::semiring_elt_t       return_type;
    typedef typename Element<Series, T>::semiring_elt_t       semiring_elt_t;
    typedef typename semiring_elt_t::value_t		        semiring_elt_value_t;
    INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

    ConstantTermEval(const Element<Series, T>& exp) :
      undefined(false),
      exp_(exp)
    {}

    MATCH__(Product, lhs, rhs)
    {
      return match(lhs) * match(rhs);
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      return match(lhs) + match(rhs);
    }
    END

    MATCH_(Star, node)
    {
      semiring_elt_t ret = match(node);
      if (ret.starable())
	return star(ret);
      undefined = true;
      return ret;
    }
    END

    MATCH__(LeftWeight, w, node)
    {
      return w * match(node);
    }
    END

    MATCH__(RightWeight, node, w)
    {
      return match(node) * w;
    }
    END

    MATCH_(Constant, m)
    {
      return exp_.set().semiring().zero(SELECT(semiring_elt_value_t));
    }
    END

    MATCH(Zero)
    {
      return exp_.set().semiring().zero(SELECT(semiring_elt_value_t));
    }
    END

    MATCH(One)
    {
      return exp_.set().semiring().identity(SELECT(semiring_elt_value_t));
    }
    END

    bool undefined;

  private:
    Element<Series, T> exp_;
  };

  template <class Series, class T>
  std::pair<typename Element<Series, T>::semiring_elt_t, bool>
  constant_term(const Element<Series, T>& exp)
  {
    typedef typename Element<Series, T>::semiring_elt_t     semiring_elt_t;
    ConstantTermEval<Series, T, algebra::DispatchFunction<T> > matcher(exp);
    semiring_elt_t v = matcher.match(exp.value());
    if (matcher.undefined)
      return std::make_pair(v, false);
    return std::make_pair(v, true);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_CONSTANT_TERM_HXX
