// semiring_base.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and
//  Regis-Gianas.
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

#ifndef VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HXX
# define VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HXX

# include <vaucanson/algebra/concept/semiring_base.hh>

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
    inline
    bool
    SemiringBase<Self>::can_choose_non_stareable(SELECTOR(T)) const
    {
      return op_can_choose_non_stareable(self(), SELECT(T));
    }

    template <class Self>
    template <class T>
    Element<Self, T>
    SemiringBase<Self>::choose_stareable(SELECTOR(T)) const
    {
      return op_choose_stareable(self(), SELECT(T));
    }
    
    template <class Self>
    template <class T>
    Element<Self, T>
    SemiringBase<Self>::choose_non_stareable(SELECTOR(T)) const
    {
      return op_choose_non_stareable(self(), SELECT(T));
    }
    
  } // algebra


    /*---------------------.
      | MetaElement<Self, T> |
      `---------------------*/

  template <class Self, class T>
  Element<Self, T>& 
  MetaElement<algebra::SemiringBase<Self>, T>::star()
  { 
    op_in_star(this->set(), this->value());
    return self();
  }

  template <class Self, class T>
  bool 
  MetaElement<algebra::SemiringBase<Self>, T>::stareable() const
  { 
    return op_stareable(this->set(), this->value()); 
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
  bool stareable(const Element<S, T>& elt)
  { 
    return op_stareable(elt.set(), elt.value()); 
  }

  template <typename S, typename T>
  bool 
  parse_weight(Element<S, T>& w, const std::string&s , 
	       typename std::string::const_iterator& i)
  {
    return op_parse(w.set(), w.value(), s, i);
  }


  // default implementations:

  template <typename S, typename T>
  inline
  bool
  op_can_choose_non_stareable(const S& set, SELECTOR(T))
  {
    return false;
  }


  template <typename S, typename T>
  inline
  Element<S, T>
  op_choose_stareable(const algebra::SemiringBase<S>& set, SELECTOR(T))
  {
    std::cerr << "WARNING: default implementation of op_choose_stareable "
      "called." << std::endl;
    std::cerr << "RESULT IS NOT RANDOM." << std::endl;
    // Zero is always stareable.
    return T();
  }

  template <typename S, typename T>
  inline
  Element<S, T> 
  op_choose_non_stareable(const algebra::SemiringBase<S>& set, SELECTOR(T))
  {
    assert(! "default implementation of op_choose_non_stareable called");
    return T();
  }

  template <typename S, typename T>
  bool 
  op_parse(const algebra::SemiringBase<S>&, 
	   T&	  				 w, 
	   const std::string&			 s, 
	   typename std::string::const_iterator& i)
  {
    std::string buf;
    if ((i != s.end()) && (*i == '-'))
      {
	buf += *i;
	++i;
      }
    while ((i != s.end()) && (*i >= '0' && *i <= '9'))
      {
	buf += *i;
	++i;
      }
    if (buf == "")
      return false;
    int ret = atoi(buf.c_str());
    w = ret;
    return true;
  }

  template <typename Self, typename T>
  bool op_stareable(const algebra::SemiringBase<Self>& s, const T& v)
  { 
    return op_eq(SELECT(Self), v, zero_value(SELECT(Self), SELECT(T)));
  }

  template <typename Self, typename T>
  void op_in_star(const algebra::SemiringBase<Self>& s, T& v)
  {
    assert(op_eq(SELECT(Self), v, zero_value(SELECT(Self), SELECT(T))));
    v = identity_value(SELECT(Self), SELECT(T));
  } 

  template <typename Self, typename T>
  T op_default(SELECTOR(algebra::SemiringBase<Self>), SELECTOR(T))
  {
    return zero_value(SELECT(Self), SELECT(T)); 
  }

} // vcsn

#endif // VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HXX



