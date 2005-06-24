// ref.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_CPPSH_INCLUDE_KERN_REF_HH
# define VCSN_VAUC_CPPSH_INCLUDE_KERN_REF_HH

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

    void restructure(T* p = 0);
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



#endif // ! VCSN_VAUC_CPPSH_INCLUDE_KERN_REF_HH
