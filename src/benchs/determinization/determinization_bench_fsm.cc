// determinization_bench_fsm.cc: this file is part of the Vaucanson project.
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
#include <cstdlib>

int main(int argc,  char** argv)
{
  unsigned n = atoi(argv[1]);

  for (unsigned i = 1; i < n; ++i)
    {
      std::cout << i - 1 << " " << i << " 1" << std::endl;
      std::cout << i << " " << i  << " 2" << std::endl;
      std::cout << i << " " << i  << " 3" << std::endl;
      std::cout << i << " " << 0  << " 2" << std::endl;
    }
  std::cout << n-1 << " " << 0 << " 1" << std::endl;
  std::cout << 0 << std::endl;
}

