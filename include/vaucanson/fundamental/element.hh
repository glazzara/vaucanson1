/*********************************************************
 * <vaucanson/algebra/element.hh>: the wizard's workshop *
 *********************************************************/
// $Id$

/* this file is part of the Vaucanson project. */
#ifndef FUNDAMENTAL_ELEMENT_HH
# define FUNDAMENTAL_ELEMENT_HH

#include <vaucanson/fundamental/struct_decl.hh>

namespace vcsn
{

  /*--------.
  | Element |
  `--------*/

  template<typename S, typename T>
  class Element : public MetaElement<S, T>
  {
  public:
    typedef S	      	set_t;
    typedef T		value_t;
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

    //       ~Element()
    //       { /*/ no way to call a destructor here /*/ }


    /*------.
    | Sugar |
    `------*/

    void 
    attach(const S& set);

    const S&
    set() const;

    bool bound() const;

    T&	value();

    const T&	value() const;

    T&	operator()();
      
    const T&	operator()() const;

    operator const T& () const;

    // maintenance (operator helpers)
    const SetSlot<S>& sslot() const;

    const ValueSlot<S, T>& vslot() const;

  public : 
    SetSlot<S>		set_;
    ValueSlot<S, T>	value_;
  };

} // vcsn


#include <vaucanson/fundamental/element.hxx>

#endif // FUNDAMENTAL_ELEMENT_HH
