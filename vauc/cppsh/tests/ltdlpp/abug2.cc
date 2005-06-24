// abug2.cc: this file is part of the Vaucanson project.
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
#include "kern/object.hh"
#include <iostream>
#include "s.hh"
using cppsh::Object;

extern "C" Object liba2_LTX_make_a()
{ 
  Object x = S<int>(); 
  std::cout << "make_a : S<int> typeinfo at " << &x.cpp_type() << std::endl;
  return x;
}

static struct Cerberos
{
  Cerberos()
  { 
    std::cout << "liba::Cerberos() @ " << this << " : " ;
    Object x = S<int>();
    std::cout << "S<int> typeinfo at " << &x.cpp_type() << std::endl;
  }

  ~Cerberos()
  { 
    std::cout << "liba::~Cerberos() @ " << this << " : " ;
    Object x = S<int>();
    std::cout << "S<int> typeinfo at " << &x.cpp_type() << std::endl;
  }

} __liba2_cerberos;

