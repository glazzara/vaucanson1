// objref.cc: this file is part of the Vaucanson project.
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

using namespace cppsh;

class A
{
public:
  A();
  A(const A& a);
  ~A();
};

void point();

int main()
{
  point();
  Object a;
  point();
  {
    ref<A> ra = new A;
    point();
    Object x = ra;
    point();
    Object y = x;
    point();
    Object z = y.clone();
    point();
    ref<A> rz = OBJECT_AS_REF(z, A);
    point();
    ref<A> rw = rz;
    point();
    a = rw;
    point();
  }
  point();
}

