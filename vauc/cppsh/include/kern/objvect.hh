/*------------------------------------------------------.
| include/kern/objvect.hh : cppsh kernel / object array |
`------------------------------------------------------*/
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
#ifndef CPPSH_OBJVECT_HH
#define CPPSH_OBJVECT_HH

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

#endif
