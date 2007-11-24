// are_equivalent.cc: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include "equivalent_functions.hh"

int
main(int argc, char** argv)
{
  if (argc != 3)
    {
      std::cerr << "Usage: " << argv[0] << " <file1> <file2>" << std::endl;
      return 1;
    }

  return are_equivalent(get_aut(argv[1]), get_aut(argv[2]));
}

