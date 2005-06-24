// koenig.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003 The Vaucanson Group.
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
#include <vaucanson/config/system.hh>
#include <string>
#include <cassert>

std::string tag;

namespace a 
{
  template<typename T>
  struct A {};
  
  struct B {};

  template<typename T>
  bool operator==(const A<T>&, const A<T>&)
  { 
    tag += "a";
    return true;
  }

  bool operator==(const B&, const B&)
  {
    tag += "b";
    return true;
  }

}

namespace b
{
  void test()
  {
    a::A<void> a;
    a::B b;
    tag = "";
    assert(a == a);
    assert(b == b);
    assert(tag == "ab");
  }

  template<typename T>
  struct A
  { };

  template<typename T>
  bool operator==(const A<T>&, const A<T>&)
  {
    tag += "c";
    return true;
  }

}

void test()
{
  a::A<void> a;
  a::B b;
  b::A<void> c;
  tag = "";
  assert(a == a);
  assert(b == b);
  assert(c == c);
  assert(tag == "abc");
}

int main()
{
  b::test();
  ::test();
  return 0;
}

