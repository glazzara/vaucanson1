// fundamental/element.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

#ifndef FUNDAMENTAL_ELEMENT_HH
# define FUNDAMENTAL_ELEMENT_HH

# include <vaucanson/fundamental/predefs.hh>
# include <vaucanson/fundamental/meta_set.hh>
# include <vaucanson/fundamental/meta_element.hh>
# include <vaucanson/fundamental/default_ops.hh>
# include <vaucanson/fundamental/element_ops.hh>

namespace vcsn
{

  /*--------.
  | Element |
  `--------*/
  //! Element of the set S implemented by T. 
  /*! 
    Element is the center of the design pattern used in Vaucanson to
    have an orthogonal construction of object from two different points of view :
    - Algebraic/Theorical one from the hierarchies of sets ;
    - Implementation one ;

    See: MetaElement
  */

  template<typename S, typename T>
  class Element : public MetaElement<S, T>
  {
  public:
    typedef S	      set_t;
    typedef T	      value_t;
    static const bool dynamic_set    = MetaSet<S>::dynamic_set;
    static const bool dynamic_values = MetaElement<S, T>::dynamic_values;
    static const bool dynamic        = dynamic_set || dynamic_values;
      
    /*-------------.
    | constructors |
    `-------------*/

    Element();

    Element(const Element& other);

    template<typename U>
    Element(const Element<S, U>& other);

    template<typename OtherS, typename U>
    Element(const Element<OtherS, U>& other);

    Element(const T& other);

    template<typename U>
    Element(const U& other);

    explicit Element(const S& set);

    Element(const S& set, const T& other);

    template<typename U>
    Element(const S& set, const U& other);

    template<typename OtherS, typename U>
    Element(const S& set, const Element<OtherS, U>& other);

    /*-----------.
    | Assignment |
    `-----------*/
    Element& operator=(const Element& other);

    template<typename U>
    Element& operator=(const Element<S, U>& other);

    template<typename OtherS, typename U>
    Element& operator=(const Element<OtherS, U>& other);

    template<typename U>
    Element& operator=(const U& other);

    /*--------------------------.
    | Design pattern facilities |
    `--------------------------*/
    const S&	set() const;

    void	attach(const S& set);
    bool	bound() const;

    T&		value();
    const T&	value() const;

    T&		operator()();
    const T&	operator()() const;

    operator const T& () const;

  private : 
    SetSlot<S>		set_;
    ValueSlot<S, T>	value_;
  };

} // vcsn


#include <vaucanson/fundamental/element.hxx>

#endif // FUNDAMENTAL_ELEMENT_HH
