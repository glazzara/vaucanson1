// fundamental/element.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

# include <vaucanson/config/system.hh>
# include <vaucanson/fundamental/predefs.hh>
# include <vaucanson/fundamental/meta_set.hh>
# include <vaucanson/fundamental/meta_element.hh>
# include <vaucanson/fundamental/default_ops.hh>
# include <vaucanson/fundamental/element_ops.hh>

namespace vcsn
{

  /*! \addtogroup fundamental
   *  \@{
   */

  /*--------.
  | Element |
  `--------*/
  //! Element of the set S implemented by T. 
  /*! 
    Element is the center of the design pattern used in Vaucanson to
    have an orthogonal construction of object from two different points of view :
    - Algebraic/Theorical one from the hierarchies of sets ;
    - Implementation one ;

    Element proposes a lot of different constructors so as to permit
    the largest set of type conversions. Calling foreign constructors
    assume that there exist compatible "op_convert" functions.

    See: MetaElement
  */

  template<typename S, typename T>
  class Element : public MetaElement<S, T>
  {
  public:
    /*! set_t is the structural element type of the Element. */
    typedef S	      set_t;

    /*! value_t is the implementation type of the Element. */
    typedef T	      value_t;

    /*! dynamic_set determines if the structural element needs dynamic data. */
    static const bool dynamic_set    = MetaSet<S>::dynamic_set;

    /*! dynamic_value determines if the implementation needs dynamic data. */
    static const bool dynamic_values = MetaElement<S, T>::dynamic_values;

    /*! an element is dynamic iff its structural element or its implementation
    is. */
    static const bool dynamic        = dynamic_set || dynamic_values;
      
    /*-------------.
    | constructors |
    `-------------*/

    /*! Default constructor.  */
    Element();

    /*! Copy constructor from element of exactly the same type. */
    Element(const Element& other);

    /*! Copy constructor from element of the same structural element but
    different implementation. */
    template<typename U>
    Element(const Element<S, U>& other);

    /*! Copy constructor from completly different element. */
    template<typename OtherS, typename U>
    Element(const Element<OtherS, U>& other);

    /*! Copy constructor from the implementation. Warning : if the
      structural element is dynamic, the client must handle the
      initialization of it. */
    Element(const T& other);

    /*! Copy constructor from another implementation. Warning : if the
      structural element is dynamic, the client must handle the
      initialization of it. */
    template<typename U>
    Element(const U& other);

    /*! Constructor from the structural element. Warning : the default
      constructor of the implementation is called. */
    explicit Element(const S& set);

    /*! Constructor from the structural element and the implementation. */
    Element(const S& set, const T& other); 

    /*! Constructor from the structural element and another
    implementation type. */
    template<typename U> Element(const S& set,
    const U& other);

    /*! Constructor from other structural element and another
    implementation type. */
    template<typename OtherS, typename U>
    Element(const S& set, const Element<OtherS, U>& other);

    /*-----------.
    | Assignment |
    `-----------*/
    /*! Assignement operator from the same type of Element. */
    Element& operator=(const Element& other);

    /*! Assignement operator from another element type with different
      implementation.   */
    template<typename U>
    Element& operator=(const Element<S, U>& other);

    /*! Assignement operator from another structural element and
      another implementation. */
    template<typename OtherS, typename U>
    Element& operator=(const Element<OtherS, U>& other);

    /*! Assignement operator from another implementation. */
    template<typename U>
    Element& operator=(const U& other);

    /*--------------------------.
    | Design pattern facilities |
    `--------------------------*/
    /*! Structural element accessor. (const) */
    const S&	set() const;

    /*! Post-construction structural element initialization. */
    void	attach(const S& set);

    /*! Consistency check. */
    bool	bound() const;

    /*! Implementation accessor. */
    T&		value();

    /*! Implementation accessor. (const version) */
    const T&	value() const;

    /*! Implementation accessor. */
    T&		operator()();

    /*! Implementation accessor. (const version) */
    const T&	operator()() const;

    /*! Automatic conversion of element to its implementation. */
    operator const T& () const;

  private : 
    SetSlot<S>		set_;
    ValueSlot<S, T>	value_;
  };

  //! @}

} // vcsn


#include <vaucanson/fundamental/element.hxx>

#endif // FUNDAMENTAL_ELEMENT_HH
