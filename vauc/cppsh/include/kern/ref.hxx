/*-------------------------------------------------------.
| include/kern/ref.hxx : cppsh kernel / smart references |
`-------------------------------------------------------*/
//     Copyright (C) 2002, 2004  LRDE.

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
#ifndef CPPSH_REF_HXX
#define CPPSH_REF_HXX

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

#endif
