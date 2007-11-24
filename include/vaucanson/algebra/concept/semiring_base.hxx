// semiring_base.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HXX
# define VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HXX

# include <vaucanson/algebra/concept/semiring_base.hh>

# include <sstream>
# include <string>
# include <iostream>

namespace vcsn {

  namespace algebra {

    /*-------------.
    | SemiringBase |
    `-------------*/

    template <class Self>
    SemiringBase<Self>::SemiringBase()
    {}

    template <class Self>
    SemiringBase<Self>::SemiringBase(const SemiringBase& other) :
      MonoidBase<Self>(other)
    {}

    template <class Self>
    template <class T>
    bool
    SemiringBase<Self>::can_choose_non_starable(SELECTOR(T)) const
    {
      return op_can_choose_non_starable(this->self(), SELECT(T));
    }

    template <class Self>
    template <class T>
    Element<Self, T>
    SemiringBase<Self>::choose_starable(SELECTOR(T)) const
    {
      return op_choose_starable(this->self(), SELECT(T));
    }


    template <class Self>
    template <class T>
    Element<Self, T>
    SemiringBase<Self>::choose_non_starable(SELECTOR(T)) const
    {
      return op_choose_non_starable(this->self(), SELECT(T));
    }



  } // algebra

  /*---------------------.
  | MetaElement<Self, T> |
  `---------------------*/

  template <class Self, class T>
  Element<Self, T>&
  MetaElement<algebra::SemiringBase<Self>, T>::star()
  {
    op_in_star(this->structure(), this->value());
    return this->self();
  }

  template <class Self, class T>
  bool
  MetaElement<algebra::SemiringBase<Self>, T>::starable() const
  {
    return op_starable(this->structure(), this->value());
  }

  template <class Self, class T>
  MetaElement<algebra::SemiringBase<Self>, T>::MetaElement()
  {}

  template <class Self, class T>
  MetaElement<algebra::SemiringBase<Self>, T>::MetaElement
  (const MetaElement& other) :
    MetaElement<algebra::MonoidBase<Self>, T>(other)
  {}

  /*-----.
  | star |
  `-----*/

  template <typename S, typename T>
  typename op_star_traits<S, T>::ret_t
  star(const Element<S, T>& e)
  {
    typename op_star_traits<S, T>::ret_t res(e);
    return res.star();
  }

  template <typename S, typename T>
  bool starable(const Element<S, T>& elt)
  {
    return op_starable(elt.structure(), elt.value());
  }

  template <typename S, typename T>
  bool
  parse_weight(Element<S, T>& w, const std::string&s ,
	       typename std::string::const_iterator& i)
  {
    return op_parse(w.structure(), w.value(), s, i);
  }


  namespace algebra {

    // default implementations:

    template <typename S, typename T>
    bool
    op_can_choose_non_starable(const algebra::SemiringBase<S>& set,
			       SELECTOR(T))
    {
      return false;
    }


    template <typename S, typename T>
    Element<S, T>
    op_choose_starable(const algebra::SemiringBase<S>& set, SELECTOR(T))
    {
      std::cerr << "WARNING: default implementation of op_choose_starable "
	"called." << std::endl;
      std::cerr << "RESULT IS NOT RANDOM." << std::endl;
      // Zero is always starable.
      return T();
    }

    template <typename S, typename T>
    Element<S, T>
    op_choose_non_starable(const algebra::SemiringBase<S>& set, SELECTOR(T))
    {
      pure_service_call ("default implementation of op_choose_non_starable()");
      return T();
    }

    template <typename S, typename T>
    bool
    op_parse(const algebra::SemiringBase<S>&,
	     T&	  				 w,
	     const std::string&			 s,
	     typename std::string::const_iterator& i)
    {
      if (*i != '-' && (*i < '0' || *i > '9'))
	return false;
      T res;
      std::stringstream ret;
      ret << std::string(i, s.end());
      int init = ret.tellg();
      ret >> std::dec >> res;
      if (ret.tellg() < 0)
	return false;
      for (int cur = ret.tellg();
	   (cur - init - 1) && i != s.end(); ++i, ++init)
	;
      if (*i != '.')
	++i;
      w = res;
      return true;
    }

    template <typename Self, typename T>
    bool op_starable(const algebra::SemiringBase<Self>& s, const T& v)
    {
      return op_eq(SELECT(Self), v, zero_value(SELECT(Self), SELECT(T)));
    }

    template <typename Self, typename T>
    void op_in_star(const algebra::SemiringBase<Self>&, T& v)
    {
      assertion(op_eq(SELECT(Self), v, zero_value(SELECT(Self), SELECT(T))));
      v = identity_value(SELECT(Self), SELECT(T));
    }

    template <typename Self, typename T>
    T op_default(SELECTOR(algebra::SemiringBase<Self>), SELECTOR(T))
    {
      return zero_value(SELECT(Self), SELECT(T));
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HXX
