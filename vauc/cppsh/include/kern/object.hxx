// object.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJECT_HXX
# define VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJECT_HXX

#include "kern/object.hh"
#include <algorithm> // for std::swap

namespace cppsh
{

  /*--------------.
  | Cell_ methods |
  `--------------*/
  
  template<typename T>
  Cell_<T>::Cell_(const T& init)
    : r_(new T(init))
  {}
  
  template<typename T>
  Cell_<T>::Cell_(const ref<T>& r)
    : r_(r)
  {}
  
  template<typename T>
  inline const std::type_info&
  Cell_<T>::cpp_type() const
  { return typeid(T); }
  
  template<typename T>
  inline Cell_<T>*
  Cell_<T>::clone() const
  { return new Cell_(r_); }
  
  template<typename T>
  inline Cell_<T>*
  Cell_<T>::copy_clone() const
  { return new Cell_(*r_); }
  
  template<typename T>
  Cell_<T>::~Cell_()
  { }
  
  /*---------------.
  | Object methods |
  `---------------*/

  
  // constructors & destructor
  inline Object::Object() 
    : cell_(0)
  {}
  
  inline Object::Object(const Object& other)
    : cell_(other.cell_ ? other.cell_->clone() : 0)
  { }
  
  template<typename T>
  inline Object::Object(const T& t)
    : cell_(new Cell_<T>(t))
  { }

  template<typename T>
  inline Object::Object(const cppsh::ref<T>& r)
    : cell_(new Cell_<T>(r))
  { }
  
  inline Object::~Object() 
  { delete cell_; }
  
  // swap & assignment
  inline Object& 
  Object::operator=(const Object& other)
  {
    if (cell_ != other.cell_)
      { delete cell_; cell_ = 0; }
    if (other.cell_)
      cell_ = other.cell_->clone();
    return *this;
  }

  template<typename T>
  inline Object&
  Object::operator=(const cppsh::ref<T>& other)
  {
    if (cell_)
      delete cell_;
    if (other.bound())
      cell_ = new Cell_<T>(other);
    else
      cell_ = 0;
    return *this;
  }

  inline Object& 
  Object::swap(Object& other)
  { 
    std::swap(cell_, other.cell_);
    return *this;
  }
    
  
  /*---------.
  | services |
  `---------*/
  
  // return true if the reference actually points to something
  inline bool 
  Object::bound() const
  { return (cell_ != 0); }

  // give the c++ type of the data pointed to
  inline const std::type_info& 
  Object::cpp_type() const
  { return cell_ ? cell_->cpp_type() : typeid(void); }
    
  // get the actual data. The real type is needed
  // to achieve the operation.
  template<typename T>
  inline T* 
  Object::cast(const T*) const
  {
    if (!cell_ || (cell_->cpp_type() != typeid(T)))
      return 0;
    return static_cast<Cell_<T>*>(cell_)->r_.ptr();
  }

  template<typename T>
  inline ref<T>
  Object::ref(const T*) const
  {
    if (!cell_ || (cell_->cpp_type() != typeid(T)))
      return 0;
    return static_cast<Cell_<T>*>(cell_)->r_;
  }

  inline Object 
  Object::clone() const 
  { 
    Cell* p = cell_;
      
    if (p != 0)
      p = p->copy_clone();
	
    return Object(p);
  }

        
  /*----------------.
  | Using Cell |
  `----------------*/
  inline Object::Object(Cell* p)
    : cell_(p)
  {}
    
}


namespace std
{

  template<>
  inline void 
  swap(cppsh::Object& a, cppsh::Object& b)
  { 
    (void)a.swap(b); 
  }

}

#endif // ! VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJECT_HXX
