// objvect.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJVECT_HH
# define VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJVECT_HH

#include "kern/object.hh"

namespace cppsh
{
  class ObjVectBase
  {
  public:
    size_t size() const;

    void ensure_size(size_t expected) const;

    Object& operator[](size_t i);
    const Object& operator[](size_t i) const;

    template<typename T>
    T* at(size_t i, const T*) const;

    template<typename T>
    ref<T> ref_at(size_t i, const T*) const;

    ~ObjVectBase();

    void autoclone() const;

  protected:
    ObjVectBase(size_t N, Object *vec);

    const size_t n_;
    Object *vec_;
  };

  template<size_t N>
  class ObjVect : public ObjVectBase
  {
  public:
    ObjVect();
    ObjVect(const ObjVect& other);

  };

#define OBJVECT_AT(V, T, i) ((V).at((i), (const T*)0))
#define OBJVECT_REF_AT(V, T, i) ((V).ref_at((i), (const T*)0))

}

#include "kern/objvect.hxx"

#endif // ! VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJVECT_HH
