/*-------------------------------------------------------.
| include/kern/objvect.hxx : cppsh kernel / object array |
`-------------------------------------------------------*/
//     Copyright (C) 2002  LRDE.

//     libcppshk is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Lesser General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.

//     libcppshk is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Lesser General Public License for more details.

//     You should have received a copy of the GNU Lesser General Public
//     License along with this library; if not, write to the Free Software
//     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
#ifndef CPPSHK_OBJVECT_HXX
#define CPPSHK_OBJVECT_HXX

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

#endif
