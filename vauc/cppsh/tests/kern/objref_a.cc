// objref_a.cc: this file is part of the Vaucanson project.
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
#include <iostream>

class A
{
public:
  A();
  A(const A& a);
  ~A();
};

A::A()
{ std::cout << this << "->A()" << std::endl; }

A::A(const A& a)
{ std::cout << this << "->A(" << &a << ")" << std::endl; }

A::~A()
{ std::cout << this << "->~A()" << std::endl; }

void point()
{ std::cout << "mark." << std::endl; }

