// objvect.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

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
#ifndef VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJVECT_HXX
# define VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJVECT_HXX

#include "kern/objvect.hh"
#include <algorithm>
#include <cassert>

namespace cppsh
{
  template<size_t N>
  ObjVect<N>::ObjVect()
    : ObjVectBase(N, new Object[N])
  { }

  template<size_t N>
  ObjVect<N>::ObjVect(const ObjVect<N>& other)
    : ObjVectBase(other.n_, new Object[other.n_])
  { std::copy(other.vec_, other.vec_ + other.n_, vec_); }

  
  inline size_t
  ObjVectBase::size() const
  { return n_; }

  inline Object&
  ObjVectBase::operator[](size_t i)
  { 
    assert(i < n_);
    return vec_[i]; 
  }

  inline const Object&
  ObjVectBase::operator[](size_t i) const
  {
    assert(i < n_);
    return vec_[i];
  }

  template<typename T>
  inline T* 
  ObjVectBase::at(size_t i, const T*) const
  {
    assert(i < n_);
    return OBJECT_CAST(vec_[i], T);
  }

  template<typename T>
  inline ref<T> 
  ObjVectBase::ref_at(size_t i, const T*) const
  {
    assert(i < n_);
    return OBJECT_AS_REF(vec_[i], T);
  }

  inline 
  ObjVectBase::~ObjVectBase()
  { delete[] vec_; }

  inline
  ObjVectBase::ObjVectBase(size_t N, Object* vec)
    : n_(N), vec_(vec)
  { }

}

#endif // ! VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJVECT_HXX
