// semigroup_base.hxx
//
// 
// $Id$
// VCSN_HEADER

#ifndef ALGEBRA_SEMIGROUP_BASE_HXX
# define ALGEBRA_SEMIGROUP_BASE_HXX

# include <vaucanson/fundamental/fundamental.hh>

namespace vcsn {

  namespace algebra {
    
    template<class Self> 
    SemigroupBase<Self>::SemigroupBase() 
    {}

    template<class Self> 
    SemigroupBase<Self>::SemigroupBase(const SemigroupBase& other) :
      Structure<Self>(other)
    {}
        
  } // algebra
  
  template<class Self, typename T>
  MetaElement<algebra::SemigroupBase<Self>, T>::MetaElement() 
  {}
  
  template<class Self, typename T>
  MetaElement<algebra::SemigroupBase<Self>, T>::MetaElement(const MetaElement& other) :
    MetaElement<Structure<Self>, T>(other)
  {}
    
} // vcsn

#endif // ALGEBRA_SEMIGROUP_BASE_HXX
