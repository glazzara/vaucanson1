// dlbug32.cc: this file is part of the Vaucanson project.
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
#include <ltdlpp.hh>
#include <exception>
#include <iostream>

typedef cppsh::Object (*maker_ptr_t)();

int main()
{
  using namespace ltdl;

  try {

    std::cout << "Getting loader instance..." << std::endl;
    Loader& ld = loader_instance();

    std::cout << "Loading liba..." << std::endl;
    Module liba = ld.open("liba2");

    std::cout << "Loading libb..." << std::endl;
    Module libb = ld.open("libb2");

    {
    std::cout << "Retrieving make_a..." << std::endl;
    maker_ptr_t make_a = (maker_ptr_t)liba.sym("make_a");
    std::cout << "Creating X = make_a()..." << std::endl;
    cppsh::Object X = make_a();
    std::cout << "X.type_info@" << &X.cpp_type() << std::endl;
    std::cout << "X.type_info.name = " << X.cpp_type().name() << std::endl;


    std::cout << "Retrieving make_b..." << std::endl;
    maker_ptr_t make_b = (maker_ptr_t)libb.sym("make_b");
    std::cout << "Creating Y = make_b()..." << std::endl;
    cppsh::Object Y = make_b();
    std::cout << "Y.type_info@" << &Y.cpp_type() << std::endl;
    std::cout << "Y.type_info.name = " << Y.cpp_type().name() << std::endl;

    std::cout << std::endl
	      << "If you have the chance to see this message, check the messages" << std::endl
	      << " ** below or above this message **" << std::endl
	      << "for calls to Cerberos and ~Cerberos. You should see exactly one" << std::endl
	      << "liba::Cerberos(), one liba::~Cerberos(), one libb::Cerberos(), " << std::endl
	      << "and one libb::~Cerberos(), even if not in order."  << std::endl
	      << "If there are more, or less, or one ore more of the 4 is missing," << std::endl
	      << "then dlopen() support for C++ modules is broken." << std::endl
	      << std::endl;

    }

    std::cout << "Unloading libb..." << std::endl;
    libb.close();
    std::cout << "Unloading liba..." << std::endl;
    liba.close();

  } 
  catch (std::exception& x) {
    std::cout << "Exception: " << x.what() << std::endl;
  }

}

