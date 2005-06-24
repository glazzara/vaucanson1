// ref.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_CPPSH_INCLUDE_KERN_REF_HXX
# define VCSN_VAUC_CPPSH_INCLUDE_KERN_REF_HXX

#include "kern/ref.hh"

namespace cppsh
{
  template<typename T>
  inline ref<T>::~ref() { dispose(); }

  template<typename T>
  inline ref<T>::ref(T* p)
    : data_(p)
  { count_ = new long(1); }

  template<typename T>
  inline ref<T>::ref(const ref<T>& r)
    : data_(r.data_)
  { ++*(count_ = r.count_); }

  template<typename T>
  template<typename Y>
  inline ref<T>& 
  ref<T>::operator=(const ref<Y>& r)
  {
    share(r.data_, r.count_);
    return *this;
  }

  template<typename T>
  inline T&
  ref<T>::operator*() const
  { return *data_; }

  template<typename T>
  inline T*
  ref<T>::operator->() const
  { return data_; }

  template<typename T>
  inline T*
  ref<T>::ptr() const
  { return data_; }
  
  template<typename T>
  inline bool
  ref<T>::bound() const
  { return (data_ != 0); }

  template<typename T>
  inline ref<T>&
  ref<T>::swap(ref<T>& other)
  {
    std::swap(data_, other.data_);
    std::swap(count_, other.count_);
    return *this;
  }


  template<typename T>
  inline void
  ref<T>::restructure(T* p)
  {
    if (data_ == p)
      return ;
    if (! --*count_)
      delete data_;
    else
      count_ = new long;
    *count_ = 1;
    data_ = p;
  }

  template<typename T>
  inline void
  ref<T>::dispose()
  {
    if (! --*count_)
      {
	delete data_;
	delete count_;
      }
  }

  template<typename T>
  inline void
  ref<T>::share(T* rdata, long *rcount)
  {
    if (count_ != rcount)
      {
	++*rcount;
	dispose();
	data_ = rdata;
	count_ = rcount;
      }
  }
  
}

#endif // ! VCSN_VAUC_CPPSH_INCLUDE_KERN_REF_HXX
