// monoid_base.hxx
//
//
// $Id$
// VCSN_HEADER

#ifndef ALGEBRA_MONOID_BASE_HXX
# define ALGEBRA_MONOID_BASE_HXX

# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/algebra/concept/semigroup_base.hh>

namespace vcsn {

  namespace algebra {

    /*-----------------.
    | MonoidBase<Self> |
    `-----------------*/
    template<class Self>
    template<typename T>
    Element<Self, T> 
    MonoidBase<Self>::identity(SELECTOR(T)) const
    {
      return Element<Self, T>(self(), 
			      identity_value(SELECT(Self), SELECT(T)));
    }
    
    template<class Self>
    template<typename T>
    Element<Self, T>  MonoidBase<Self>::zero(SELECTOR(T)) const
    {
      return Element<Self, T>(self(), 
			      zero_value(SELECT(Self), SELECT(T)));
    }
    
    template <class Self>
    MonoidBase<Self>::MonoidBase() 
    {}
    
    template <class Self>
    MonoidBase<Self>::MonoidBase(const MonoidBase& other) :
      SemigroupBase<Self>(other)
    {}
    
  } // algebra
  
    /*---------------------------------.
    | MetaElement<MonoidBase<Self>, T> |
    `---------------------------------*/
    
  template<class Self, typename T>
  MetaElement<algebra::MonoidBase<Self>, T>::MetaElement() 
  {}
    
  template<class Self, typename T>
  MetaElement<algebra::MonoidBase<Self>, T>::MetaElement(const MetaElement& other) :
    MetaElement<algebra::SemigroupBase<Self>, T>(other)
  {}

  //! By default, an element of a monoid is the identity.
  template<typename T, typename Self>
  T op_default(SELECTOR(algebra::MonoidBase<Self>), SELECTOR(T))
  { 
    return identity_value(SELECT(Self), SELECT(T)); 
  }

} // vcsn

#endif // ALGEBRA_MONOID_BASE_HXX
