// fundamental/element.hxx
//
// $Id$
// VCSN_HEADER
#ifndef FUNDAMENTAL_ELEMENT_HXX
# define FUNDAMENTAL_ELEMENT_HXX

# include <vaucanson/fundamental/element_ops.hh>
# include <vaucanson/fundamental/default_ops.hh>
# include <vaucanson/fundamental/element.hh>

namespace vcsn {

  /*-------------.
  | constructors |
  `-------------*/

  template <class S, class T>
  Element<S,T>::Element() 
    : set_(), 
      value_(op_default(SELECT(S), SELECT(T)))
  {}
    
  template <class S, class T>
  Element<S,T>::Element(const Element& other) :
    MetaElement<S, T>(other),
    set_(other.set_),
    value_(other.value_)
  {}
    
  template <class S, class T>
  template<typename U>
  Element<S,T>::Element(const Element<S, U>& other)
    : set_(other.set_),
      value_(op_convert(SELECT(T), SELECT(S), other.value()))
  {}
    
  template <class S, class T>
  template<typename OtherS, typename U>
  Element<S,T>::Element(const Element<OtherS, U>& other)
    : set_(),
      value_(op_convert(SELECT(T), SELECT(S), 
			SELECT(OtherS), other.value()))
  {}
    
  template <class S, class T>
  Element<S,T>::Element(const T& other)
    : set_(),
      value_(other)
  {}
    
  template <class S, class T>
  template<typename U>
  Element<S,T>::Element(const U& other)
    : set_(),
      value_(op_convert(SELECT(T), SELECT(S), other))
  {}
    
  template <class S, class T>
  Element<S,T>::Element(const S& set)
    : set_(set),
      value_(op_default(SELECT(S), SELECT(T)))
  {}
    
  template <class S, class T>
  Element<S,T>::Element(const S& set, const T& other)
    : set_(set),
      value_(other)
  {}
    
  template <class S, class T>
  template<typename U>
  Element<S,T>::Element(const S& set, const U& other)
    : set_(set),
      value_(op_convert(SELECT(T), SELECT(S), other))
  {}
    
  template <class S, class T>
  template<typename OtherS, typename U>
  Element<S,T>::Element(const S& set, const Element<OtherS, U>& other)
    : set_(set),
      value_(op_convert(SELECT(T), SELECT(S), 
			SELECT(OtherS), other.value()))
  {}
    
  /*-----------.
  | Assignment |
  `-----------*/
    
  template <class S, class T>
  Element<S,T>& 
  Element<S,T>::operator=(const Element& other)
  {
    set_.assign(other.set_);
    value_.assign(other.value_);
    return *this;
  }
    
  template <class S, class T>
  template<typename U>
  Element<S,T>& 
  Element<S,T>::operator=(const Element<S, U>& other)
  {
    set_.assign(other.set_);
    op_assign(set(), other.set(), value(), other.value());
    return *this; 
  }

  template <class S, class T>
  template<typename OtherS, typename U>
  Element<S,T>& Element<S,T>::operator=(const Element<OtherS, U>& other)
  { 
    op_assign(set(), other.set(), value(), other.value());
    return *this; 
  }

  template <class S, class T>
  template<typename U>
  Element<S,T>& Element<S,T>::operator=(const U& other)
  {
    op_assign(set(), value(), other);
    return *this;
  }

  //       ~Element()
  //       { /*/ no way to call a destructor here /*/ }


  /*------.
  | Sugar |
  `------*/

  template <class S, class T>
  void 
  Element<S,T>::attach(const S& set)
  { 
    set_.attach(set); 
  }

  template <class S, class T>
  const S&
  Element<S,T>::set() const 
  { 
    return set_.get(); 
  }

  template <class S, class T>
  bool Element<S,T>::bound() const
  { 
    return set_.bound(); 
  }

  template <class S, class T>
  T&	Element<S,T>::value()       
  { 
    return value_.get(); 
  }

  template <class S, class T>
  const T&	Element<S,T>::value() const 
  { 
    return value_.get(); 
  }

  template <class S, class T>
  T&	Element<S,T>::operator()()	   
  { 
    return value_.get(); 
  }
      
  template <class S, class T>
  const T&	Element<S,T>::operator()() const 
  { 
    return value_.get(); 
  }

  template <class S, class T>
  Element<S,T>::operator const T& () const 
  { 
    return value_.get(); 
  }

  // maintenance (operator helpers)
  template <class S, class T>
  const SetSlot<S>& Element<S,T>::sslot() const 
  { 
    return set_; 
  }

  template <class S, class T>
  const ValueSlot<S, T>& Element<S,T>::vslot() const 
  { 
    return value_; 
  }

} // vcsn


#endif // FUNDAMENTAL_ELEMENT_HXX
