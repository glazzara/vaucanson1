/*------------------------------------------------------.
| include/kern/ref.hh : cppsh kernel / smart references |
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
#ifndef CPPSHK_REF_HH
#define CPPSHK_REF_HH

#include <algorithm>

namespace cppsh
{

  template<typename T>
  class ref
  {
  public:
    typedef T element_type;
    
    ~ref();
    ref(T* p = 0);
    ref(const ref<T>& r);

    template<typename Y>
    ref& operator=(const ref<Y>& r);

    T& operator*() const;

    T* operator->() const;
    T* ptr() const;

    void reset(T* p = 0);
    bool bound() const;
    ref& swap(ref& other);

    template<typename U>
    bool operator==(const ref<U>& other) const
    { return other.data_ == data_; }
    
  protected:
    
    T*		data_;
    long*	count_;
    
    void dispose();
    void share(T* rdata, long *rcount);

  };

}

namespace std
{
  template<typename T, typename U>
  void swap(cppsh::ref<T>& a, cppsh::ref<U>& b)
  { (void)a.swap(b); }

  template<typename T>
  void swap(cppsh::ref<T>& a, cppsh::ref<T>& b)
  { (void)a.swap(b); }
}

#include "kern/ref.hxx"



#endif
