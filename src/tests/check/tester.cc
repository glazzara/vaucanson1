// tester.cc: this file is part of the Vaucanson project.
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
#include <iomanip>
#include <string>
#include "tester.hh"

namespace tests {

  const unsigned Tester::nb_col_msg = 50;

  Tester::Tester() :
    passed_(0),
    failed_(0),
    verbose_(none)
  {
    std::string s = getenv("VERBOSE");
    if (s == "x" || s == "high")
      verbose_ = high;
    else if (s != "")
      verbose_ = medium;  
  }

  Tester::Tester(verbose_level v) : 
    passed_ (0),
    failed_(0),
    verbose_(v)
  {
  }

  bool 
  Tester::all_passed() 
  {
    return (failed_ == 0);
  }

  void 
  Tester::ok(std::string test_label)
  {
    if (verbose_ != none)
      std::cout << "TEST: [OK]   " << test_label << std::endl;
    passed_++;
  }

  void 
  Tester::ko(std::string test_label)
  {
    if (verbose_ != none)
      std::cout << "TEST: [KO]   " << test_label << std::endl;
    failed_++;
  }
  
  verbose_level Tester::verbose() const
  {
    return verbose_;
  }

  // FIXME: Add statistics stuff.

} // tests

