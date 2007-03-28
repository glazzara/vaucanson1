// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2006, 2007 The Vaucanson Group.
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

#include <iostream>

#include <vaucanson/tools/bencher.hh>
#define BENCHNAME		eps_removal
#include "eps_removal/eps_removal_bench.hh"
#define BENCHFUN		BENCHFUN_layer1(BENCHNAME)
#define BENCHFUN_layer1(NAME)	BENCHFUN_layer2(NAME)
#define BENCHFUN_layer2(NAME)	NAME ## _bench

#define BENCHTEXT		BENCHTEXT_layer1(BENCHNAME)
#define BENCHTEXT_layer1(NAME)	BENCHTEXT_layer2(NAME)
#define BENCHTEXT_layer2(NAME)  # NAME

int main(int argc, char* argv[])
{
  std::cerr << BENCHTEXT << ":" << std::endl;
  if (argc == 2)
    BENCHFUN(atoi(argv[1]));
}
