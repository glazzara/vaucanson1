// ref.hh
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef UTILITY_REF_HH
#define UTILITY_REF_HH

namespace utility
{

  template<typename T>
  class ref
  {
  public:
    typedef T element_type;

    ~ref();

    ref();
    ref(T* p);

    ref(const ref<T>& r);

    template<typename Y>
    ref& operator=(const ref<Y>& r);

//     ref(const ref& r);

    ref& operator=(const ref& r);

    void reset(T* p = 0);

    T& operator*() const;
    T* operator->() const;
    T* get() const;
    
    long& ref_count() const;
    bool unique() const;

    bool bound() const;
    ref& swap(ref& other);

  protected:
    
    T*		data_;
    long*	count_;

    void dispose();
    void share(T* rdata, long *rcount);
    
  };


} // utility


#define REF_OP(Op)						\
template<typename T, typename U>				\
static inline bool operator Op(const utility::ref<T>& a, 	\
			       const utility::ref<U>& b);	


REF_OP(==);  
REF_OP(!=);  
REF_OP(<);  
REF_OP(>);  
REF_OP(<=);  
REF_OP(>=);  

#undef REF_OP

namespace std
{
  template<typename T, typename U>
  void swap(utility::ref<T>& a, utility::ref<U>& b);

  template<typename T>
  void swap(utility::ref<T>& a, utility::ref<T>& b);
} // std

# include <vaucanson/misc/ref.hxx>

#endif
