// semigroup_base.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_CONCEPT_SEMIGROUP_BASE_HXX
# define VCSN_ALGEBRA_CONCEPT_SEMIGROUP_BASE_HXX

# include <vaucanson/design_pattern/design_pattern.hh>

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

#endif // ! VCSN_ALGEBRA_CONCEPT_SEMIGROUP_BASE_HXX
