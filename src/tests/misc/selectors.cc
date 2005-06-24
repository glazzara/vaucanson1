// selectors.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/misc/selectors.hh>
#include <typeinfo>

template<typename T>
T foo(int x, SELECTOR(T), int y)
{
  return x + y;
}


int main()
{
  return foo(-1, SELECT(int), 1);
}

