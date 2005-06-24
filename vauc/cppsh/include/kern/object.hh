// object.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJECT_HH
# define VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJECT_HH

#include "kern/ref.hh"
#include <typeinfo>

namespace cppsh
{
  struct Cell
  {
    virtual const std::type_info& cpp_type() const = 0;
    virtual Cell* clone() const = 0;
    virtual Cell* copy_clone() const = 0;
    virtual ~Cell();
  };
    
  template<typename T>
  struct Cell_ : public Cell
  {
    Cell_();
    Cell_(const T& init);
    Cell_(const ref<T>& r);
    
    virtual const std::type_info& cpp_type() const;
    virtual Cell_* clone() const;
    virtual Cell_* copy_clone() const;
    virtual ~Cell_();
    
    ref<T> r_;
  };

  class Object
  {
  public:
    
    // constructors & destructor
    Object();
    Object(const Object& other);

    template<typename T>
    Object(const T& t);

    template<typename T>
    Object(const ref<T>& r);

    Object(Cell* p);   

    ~Object();

    // swap & assignment

    Object& operator=(const Object& other);
    
    template<typename T>
    Object& operator=(const ref<T>& other);

    Object& swap(Object& other);

    
    /*---------.
    | services |
    `---------*/

    // return true if the reference actually points to something
    bool bound() const;
    
    // give the c++ type of the data pointed to
    const std::type_info& cpp_type() const;

    // get the actual data. The real type is needed
    // to achieve the operation.
    template<typename T>
    T* cast(const T*) const;
    
    // get a smart ref to the actual data. the real type is needed
    // to achieve the operatation
    template<typename T>
    ref<T> ref(const T*) const;

    // data cloning
    Object clone() const;

  protected :
    
    Cell* cell_;
  };

#define OBJECT_IS_A(Obj, Type) ((Obj).cpp_type() == typeid(Type))
#define OBJECT_CAST(Obj, Type) ((Obj).cast((const Type*)0))  
#define OBJECT_AS_REF(Obj, Type) ((Obj).ref((const Type*)0))
  
}

#include "kern/object.hxx"

#endif // ! VCSN_VAUC_CPPSH_INCLUDE_KERN_OBJECT_HH
