// exception.cc: this file is part of the Vaucanson project.
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
#include "kern/exception.hh"
#include "kern/exnprint.hh"

using namespace cppsh;

void bar()
{
  failwith("bar", "doing nothing", "jeez!");
}

void foo()
{
  try
    {
      bar();
    }
  catch(Exception& e)
    {
      e.add_trace("foo", "calling bar");
      throw;
    }
}

void baz()
{
  foo();
}

int main()
{
  try
    {
      baz();
    }
  catch(Exception& e)
    {
      std::cout << e << std::endl;
    }
}

