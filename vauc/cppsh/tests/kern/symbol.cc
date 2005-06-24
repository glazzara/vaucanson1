// symbol.cc: this file is part of the Vaucanson project.
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
#include "kern/symbol.hh"
#include <iostream>
#include <cassert>

using cppsh::Symbol;

int main()
{
  Symbol s1 = "hello";
  Symbol s2 = std::string("hello");

  assert(VERY_EQUAL_SYMBOLS(s1, s2));

  Symbol s3 = " world";

  Symbol s4 = s1.value() + s3.value();

  Symbol s5 = s4;

  assert(s4 == s5);
  assert(s5 != s2);

  assert(s5.value() == "hello world");

}

