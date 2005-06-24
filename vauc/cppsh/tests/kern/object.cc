// object.cc: this file is part of the Vaucanson project.
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
#include "kern/objvect.hh"
#include <cassert>
#include <stdexcept>
#include <iostream>

void object_test()
{
  cppsh::Object o;

  assert(!o.bound());
  assert(OBJECT_IS_A(o, void));

  o = 123;

  assert(o.bound());
  assert(OBJECT_IS_A(o, int));

  assert(OBJECT_AS_REF(o, int) == OBJECT_AS_REF(o, int));
  assert(OBJECT_AS_REF(o, char).ptr() == 0);
  assert(OBJECT_AS_REF(o, float).ptr() == 0);

  assert(*OBJECT_AS_REF(o, int) == 123);
  assert(*OBJECT_CAST(o, int) == 123);

  o = 42;

  assert(*OBJECT_CAST(o, int) == 42);
  assert(*OBJECT_AS_REF(o, int) == 42);
  
  cppsh::Object o2 = 43;

  assert(!(OBJECT_AS_REF(o, int) == OBJECT_AS_REF(o2, int)));

  o.swap(o2);

  assert(*OBJECT_AS_REF(o2, int) == 42);
  assert(*OBJECT_CAST(o2, int) == 42);

}

void vtest(const cppsh::ObjVectBase& v)
{
  v.ensure_size(2);

  try
    {
      v.ensure_size(3);
    }
  catch(std::logic_error& e)
    { }

  assert(OBJECT_IS_A(v[1], int));
  assert(OBJECT_IS_A(v[0], float));

  assert(OBJECT_AS_REF(v[1], float).ptr() == 0);
  assert(OBJECT_AS_REF(v[0], int).ptr() == 0);

  assert(OBJECT_AS_REF(v[1], int) == OBJVECT_REF_AT(v, int, 1));
  assert(OBJECT_AS_REF(v[0], float) == OBJVECT_REF_AT(v, float, 0));
  assert(*OBJVECT_AT(v, int, 1) == 42);
  assert(*OBJVECT_AT(v, float, 0) == 0.);
}

void objvect_test()
{
  cppsh::ObjVect<2> v;

  v[1] = 42;
  v[0] = (float)0.;

  assert(v.size() == 2);

  vtest(v);

  cppsh::ObjVect<2> v2(v);

  vtest(v2);

  //  assert(v[1] == v2[1]);
  v2.autoclone();
  //  assert(v[1] != v2[1]);

  vtest(v2);

}

int main()
{
  object_test();
  objvect_test();

}

