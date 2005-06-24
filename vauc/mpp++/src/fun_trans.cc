// fun_trans.cc: this file is part of the Vaucanson project.
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
#include "transformer/fun_transformer.hh"
# include "parse/libparse.hh"
#include "transformer/funs.hh"
#include <fstream>


using namespace spec;


int main(int argc, char* argv[])
{
  if (argc < 2)
    {
      std::cerr << "must give the fun spec to use as argument" << std::endl;
      return 1;
    }


  std::cerr << "reading file " << argv[1] << std::endl;
  spec::FunSpec *fs =
    fun_parse(std::string(argv[1])+".fun");
  if (fs == 0)
    {
      std::cerr << "error loading file" << std::endl;
      return 2;
    }

  std::string outfname = lower(norm(std::string(argv[1])))+".fxx";
  std::cerr << "output to file " << outfname << std::endl;

  std::ofstream of(outfname.c_str());

  fun_transformer(of, *fs);
}

