<<<<<<< .working
<<<<<<< .working
<<<<<<< .working
// krat_exp_derivation.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>

namespace vcsn {

  template <class Series, class T, class Dispatch>
  struct KRatExpDerivation : algebra::KRatExpMatcher<
    KRatExpDerivation<Series, T, Dispatch>,
    T, 
    Element<Series, T>,
    Dispatch
    >
  {
    typedef KRatExpDerivation<Series, T, Dispatch>    self_t;
    typedef Element<Series, T>                        return_type;
    typedef typename Element<Series, T>::weight_t     weight_t;
    typedef typename weight_t::value_t		      weight_value_t;
    typedef typename Element<Series, T>::monoid_elt_t monoid_elt_t;
    typedef typename monoid_elt_t::value_t	      monoid_elt_value_t;
    typedef typename monoid_elt_t::set_t	      monoid_t;
    typedef typename monoid_t::alphabet_t	      alphabet_t;
    typedef typename alphabet_t::letter_t	      letter_t;
    INHERIT_CONSTRUCTORS(self_t, T, weight_t, Dispatch);

    KRatExpDerivation(const Element<Series, T>& exp, 
		   letter_t                  a) :
      undefined(false),
      exp_(exp),
      a_(a)
    {}

    Element<Series, T> series(const T& e)
    {
      return Element<Series, T>(exp_.set(), e);
    }

    MATCH__(Product, lhs, rhs)
    {
      std::pair<weight_t, bool> ret = constant_term(series(lhs));
      if (ret.second == false)
	{
	  undefined = true;
	  return return_type(exp_.set());
	}
      return (match(lhs) * rhs) + ret.first * match(rhs);
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      return match(lhs) + match(rhs);
    }
    END

    MATCH_(Star, e)
    {
      std::pair<weight_t, bool> ret = constant_term(series(e));
      if ((ret.second == false) || (ret.first.stareable() == false))
	{
	  undefined = true;
	  return return_type(exp_.set());
	}
      return ret.first.star() * match(e) * e.clone().star();
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      return weight_t(w) * match(e);
    }
    END

    MATCH__(RightWeight, e, w)
    {
      return match(e) * weight_t(w);
    }
    END

    MATCH_(Constant, m)
    {
      if (m[0] == a_)
	{
	  if (m.length() == 1)
	    return algebra::identity_as<T>::of(exp_.set());
	  else
 	    return Element<Series, T> (exp_.set(), m.substr(1));
	}
      else
	return algebra::zero_as<T>::of(exp_.set());
    }
    END

    MATCH(Zero)
    {
      return algebra::zero_as<T>::of(exp_.set());
    }
    END

    MATCH(One)
    {
      return algebra::zero_as<T>::of(exp_.set());
    }
    END

    bool undefined;
    
  private:
    Element<Series, T>  exp_;
    letter_t		a_;
  };
  
  template <class Series, class T, class Letter>
  std::pair<Element<Series, T>, bool>
  derivate(const Element<Series, T>& exp, 
	   Letter a)
  {
    KRatExpDerivation<Series, T, algebra::DispatchFunction<T> > 
      matcher(exp, a);
    Element<Series, T> ret = matcher.match(exp.value());
    if (matcher.undefined)
      return std::make_pair(ret, false);
    return std::make_pair(ret, true);
  }

  template <class Series, class T, class Word>
  std::pair<Element<Series, T>, bool>
  word_derivate(const Element<Series, T>& exp, 
		Word w)
  {
    Element<Series, T> ret(exp);
    for (typename Word::reverse_iterator a = w.rbegin();
	 a != w.rend(); ++a)
      {
	KRatExpDerivation<Series, T, algebra::DispatchFunction<T> > 
	  matcher(exp, *a);
	ret = matcher.match(ret.value());
	if (matcher.undefined)
	  return std::make_pair(ret, false);
      }
    return std::make_pair(ret, true);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX
=======
// krat_exp_derivation.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>

namespace vcsn {

  template <class Series, class T, class Dispatch>
  struct KRatExpDerivation : algebra::KRatExpMatcher<
    KRatExpDerivation<Series, T, Dispatch>,
    T, 
    Element<Series, T>,
    Dispatch
    >
  {
    typedef KRatExpDerivation<Series, T, Dispatch>    self_t;
    typedef Element<Series, T>                        return_type;
    typedef typename Element<Series, T>::weight_t     weight_t;
    typedef typename weight_t::value_t		      weight_value_t;
    typedef typename Element<Series, T>::monoid_elt_t monoid_elt_t;
    typedef typename monoid_elt_t::value_t	      monoid_elt_value_t;
    typedef typename monoid_elt_t::set_t	      monoid_t;
    typedef typename monoid_t::alphabet_t	      alphabet_t;
    typedef typename alphabet_t::letter_t	      letter_t;
    INHERIT_CONSTRUCTORS(self_t, T, weight_t, Dispatch);

    KRatExpDerivation(const Element<Series, T>& exp, 
		   letter_t                  a) :
      undefined(false),
      exp_(exp),
      a_(a)
    {}

    Element<Series, T> series(const T& e)
    {
      return Element<Series, T>(exp_.set(), e);
    }

    MATCH__(Product, lhs, rhs)
    {
      std::pair<weight_t, bool> ret = constant_term(series(lhs));
      if (ret.second == false)
	{
	  undefined = true;
	  return lhs;
	}
      return (match(lhs) * rhs) + ret.first * match(rhs);
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      return match(lhs) + match(rhs);
    }
    END

    MATCH_(Star, e)
    {
      std::pair<weight_t, bool> ret = constant_term(series(e));
      if ((ret.second == false) || (ret.first.stareable() == false))
	{
	  undefined = true;
	  return e;
	}
      return ret.first.star() * match(e) * e.clone().star();
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      return weight_t(w) * match(e);
    }
    END

    MATCH__(RightWeight, e, w)
    {
      return match(e) * weight_t(w);
    }
    END

    MATCH_(Constant, m)
    {
      if (m[0] == a_)
	{
	  if (m.length() == 1)
	    return algebra::identity_as<T>::of(exp_.set());
	  else
	    return Element<Series, T> (exp_.set(), m.substr(1));
	}
      else
	return algebra::zero_as<T>::of(exp_.set());
    }
    END

    MATCH(Zero)
    {
      return algebra::zero_as<T>::of(exp_.set());
    }
    END

    MATCH(One)
    {
      return algebra::zero_as<T>::of(exp_.set());
    }
    END

    bool undefined;
    
  private:
    Element<Series, T>  exp_;
    letter_t		a_;
  };
  
  template <class Series, class T, class Letter>
  std::pair<Element<Series, T>, bool>
  derivate(const Element<Series, T>& exp, 
	   Letter a)
  {
    KRatExpDerivation<Series, T, algebra::DispatchFunction<T> > 
      matcher(exp, a);
    Element<Series, T> ret = matcher.match(exp.value());
    if (matcher.undefined)
      return std::make_pair(ret, false);
    return std::make_pair(ret, true);
  }

  template <class Series, class T, class Word>
  std::pair<Element<Series, T>, bool>
  word_derivate(const Element<Series, T>& exp, 
		Word w)
  {
    Element<Series, T> ret(exp);
    for (typename Word::reverse_iterator a = w.rbegin();
	 a != w.rend(); ++a)
      {
	KRatExpDerivation<Series, T, algebra::DispatchFunction<T> > 
	  matcher(exp, *a);
	ret = matcher.match(ret.value());
	if (matcher.undefined)
	  return std::make_pair(ret, false);
      }
    return std::make_pair(ret, true);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX
>>>>>>> .merge-right.r335
=======
// krat_exp_derivation.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>

namespace vcsn {

  template <class Series, class T, class Dispatch>
  struct KRatExpDerivation : algebra::KRatExpMatcher<
    KRatExpDerivation<Series, T, Dispatch>,
    T, 
    Element<Series, T>,
    Dispatch
    >
  {
    typedef KRatExpDerivation<Series, T, Dispatch>    self_t;
    typedef Element<Series, T>                        return_type;
    typedef typename Element<Series, T>::weight_t     weight_t;
    typedef typename weight_t::value_t		      weight_value_t;
    typedef typename Element<Series, T>::monoid_elt_t monoid_elt_t;
    typedef typename monoid_elt_t::value_t	      monoid_elt_value_t;
    typedef typename monoid_elt_t::set_t	      monoid_t;
    typedef typename monoid_t::alphabet_t	      alphabet_t;
    typedef typename alphabet_t::letter_t	      letter_t;
    INHERIT_CONSTRUCTORS(self_t, T, weight_t, Dispatch);

    KRatExpDerivation(const Element<Series, T>& exp, 
		   letter_t                  a) :
      undefined(false),
      exp_(exp),
      a_(a)
    {}

    Element<Series, T> series(const T& e)
    {
      return Element<Series, T>(exp_.set(), e);
    }

    MATCH__(Product, lhs, rhs)
    {
      std::pair<weight_t, bool> ret = constant_term(series(lhs));
      if (ret.second == false)
	{
	  undefined = true;
	  return return_type(exp_.set());
	}
      return (match(lhs) * rhs) + ret.first * match(rhs);
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      return match(lhs) + match(rhs);
    }
    END

    MATCH_(Star, e)
    {
      std::pair<weight_t, bool> ret = constant_term(series(e));
      if ((ret.second == false) || (ret.first.stareable() == false))
	{
	  undefined = true;
	  return return_type(exp_.set());
	}
      return ret.first.star() * match(e) * e.clone().star();
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      return weight_t(w) * match(e);
    }
    END

    MATCH__(RightWeight, e, w)
    {
      return match(e) * weight_t(w);
    }
    END

    MATCH_(Constant, m)
    {
      if (m[0] == a_)
	{
	  if (m.length() == 1)
	    return algebra::identity_as<T>::of(exp_.set());
	  else
 	    return Element<Series, T> (exp_.set(), m.substr(1));
	}
      else
	return algebra::zero_as<T>::of(exp_.set());
    }
    END

    MATCH(Zero)
    {
      return algebra::zero_as<T>::of(exp_.set());
    }
    END

    MATCH(One)
    {
      return algebra::zero_as<T>::of(exp_.set());
    }
    END

    bool undefined;
    
  private:
    Element<Series, T>  exp_;
    letter_t		a_;
  };
  
  template <class Series, class T, class Letter>
  std::pair<Element<Series, T>, bool>
  derivate(const Element<Series, T>& exp, 
	   Letter a)
  {
    KRatExpDerivation<Series, T, algebra::DispatchFunction<T> > 
      matcher(exp, a);
    Element<Series, T> ret = matcher.match(exp.value());
    if (matcher.undefined)
      return std::make_pair(ret, false);
    return std::make_pair(ret, true);
  }

  template <class Series, class T, class Word>
  std::pair<Element<Series, T>, bool>
  word_derivate(const Element<Series, T>& exp, 
		Word w)
  {
    Element<Series, T> ret(exp);
    for (typename Word::reverse_iterator a = w.rbegin();
	 a != w.rend(); ++a)
      {
	KRatExpDerivation<Series, T, algebra::DispatchFunction<T> > 
	  matcher(exp, *a);
	ret = matcher.match(ret.value());
	if (matcher.undefined)
	  return std::make_pair(ret, false);
      }
    return std::make_pair(ret, true);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX
>>>>>>> .merge-right.r339
=======
// krat_exp_derivation.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>

namespace vcsn {

  template <class Series, class T, class Dispatch>
  struct KRatExpDerivation : algebra::KRatExpMatcher<
    KRatExpDerivation<Series, T, Dispatch>,
    T, 
    Element<Series, T>,
    Dispatch
    >
  {
    typedef KRatExpDerivation<Series, T, Dispatch>    self_t;
    typedef Element<Series, T>                        return_type;
    typedef typename Element<Series, T>::weight_t     weight_t;
    typedef typename weight_t::value_t		      weight_value_t;
    typedef typename Element<Series, T>::monoid_elt_t monoid_elt_t;
    typedef typename monoid_elt_t::value_t	      monoid_elt_value_t;
    typedef typename monoid_elt_t::set_t	      monoid_t;
    typedef typename monoid_t::alphabet_t	      alphabet_t;
    typedef typename alphabet_t::letter_t	      letter_t;
    INHERIT_CONSTRUCTORS(self_t, T, weight_t, Dispatch);

    KRatExpDerivation(const Element<Series, T>& exp, 
		   letter_t                  a) :
      undefined(false),
      exp_(exp),
      a_(a)
    {}

    Element<Series, T> series(const T& e)
    {
      return Element<Series, T>(exp_.set(), e);
    }

    MATCH__(Product, lhs, rhs)
    {
      std::pair<weight_t, bool> ret = constant_term(series(lhs));
      if (ret.second == false)
	{
	  undefined = true;
	  return return_type(exp_.set());
	}
      return (match(lhs) * rhs) + ret.first * match(rhs);
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      return match(lhs) + match(rhs);
    }
    END

    MATCH_(Star, e)
    {
      std::pair<weight_t, bool> ret = constant_term(series(e));
      if ((ret.second == false) || (ret.first.stareable() == false))
	{
	  undefined = true;
	  return return_type(exp_.set());
	}
      return ret.first.star() * match(e) * e.clone().star();
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      return weight_t(w) * match(e);
    }
    END

    MATCH__(RightWeight, e, w)
    {
      return match(e) * weight_t(w);
    }
    END

    MATCH_(Constant, m)
    {
      if (m[0] == a_)
	{
	  if (m.length() == 1)
	    return algebra::identity_as<T>::of(exp_.set());
	  else
 	    return Element<Series, T> (exp_.set(), m.substr(1));
	}
      else
	return algebra::zero_as<T>::of(exp_.set());
    }
    END

    MATCH(Zero)
    {
      return algebra::zero_as<T>::of(exp_.set());
    }
    END

    MATCH(One)
    {
      return algebra::zero_as<T>::of(exp_.set());
    }
    END

    bool undefined;
    
  private:
    Element<Series, T>  exp_;
    letter_t		a_;
  };
  
  template <class Series, class T, class Letter>
  std::pair<Element<Series, T>, bool>
  derivate(const Element<Series, T>& exp, 
	   Letter a)
  {
    KRatExpDerivation<Series, T, algebra::DispatchFunction<T> > 
      matcher(exp, a);
    Element<Series, T> ret = matcher.match(exp.value());
    if (matcher.undefined)
      return std::make_pair(ret, false);
    return std::make_pair(ret, true);
  }

  template <class Series, class T, class Word>
  std::pair<Element<Series, T>, bool>
  word_derivate(const Element<Series, T>& exp, 
		Word w)
  {
    Element<Series, T> ret(exp);
    for (typename Word::reverse_iterator a = w.rbegin();
	 a != w.rend(); ++a)
      {
	KRatExpDerivation<Series, T, algebra::DispatchFunction<T> > 
	  matcher(exp, *a);
	ret = matcher.match(ret.value());
	if (matcher.undefined)
	  return std::make_pair(ret, false);
      }
    return std::make_pair(ret, true);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_DERIVATION_HXX
>>>>>>> .merge-right.r340
