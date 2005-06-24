// streams.cc: this file is part of the Vaucanson project.
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
#include "kern/stdstreams.hh"
#include <cassert>

using namespace cppsh;

int main()
{
  Stream cin = Stream(sslot_of_cin());
  Stream cout = Stream(sslot_of_cout());
  Stream cerr = Stream(sslot_of_cerr());

  assert(cin.kind() == StreamSlot::input);
  assert(cout.kind() == StreamSlot::output);
  assert(cerr.kind() == StreamSlot::output);

  assert(&cin.as_istream() != NULL);
  assert(&cout.as_istream() == NULL);
  
  std::ostream& o = cout.as_ostream();
  o << "hello world" << std::endl;
}

