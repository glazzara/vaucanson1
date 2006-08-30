// tester.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2006 The Vaucanson Group.
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
#include <iomanip>
#include <string>
#include <cassert>
#include "tests/check/tester.hh"

namespace tests {

  const unsigned Tester::nb_col_msg = 50;
  const unsigned Tester::seed_time = static_cast <unsigned> (-1);

  Tester::Tester() :
    passed_(0),
    failed_(0),
    verbose_(none),
    seed_ (0)
  {
    std::string s = getenv("VERBOSE");
    if (s == "x" || s == "high")
      verbose_ = high;
    else if (s != "")
      verbose_ = medium;
    finalize_initialization ();
  }

  Tester::Tester(const Tester& t) :
    passed_ (0),
    failed_(0),
    verbose_(t.verbose ()),
    seed_ (t.seed ())
  {
    finalize_initialization ();
  }

  Tester::Tester(int argc, char **argv)
    : passed_ (0),
      failed_(0),
      verbose_(none),
      seed_(seed_time)
  {
    process_options (argc, argv);
    finalize_initialization ();
  }

  void
  Tester::finalize_initialization ()
  {
    if (seed_ == seed_time)
      seed_ = time (0);
    if (verbose (low))
      std::cerr << "Random seed is: " << seed_ << std::endl;
    srand (seed_);
  }

  void
  Tester::process_option (const std::string& arg)
  {
    // --verbose=[no, low, high]
    if (arg == "--verbose=no")
      verbose_ = none;
    else if (arg == "--verbose=low")
      verbose_ = low;
    else if (arg == "--verbose=medium")
      verbose_ = medium;
    else if (arg == "--verbose=high")
      verbose_ = high;
    // --seed=[time, SEED]
    else if (arg == "--seed=time")
      seed_ = seed_time;
    else if (arg.substr (0, strlen ("--seed=")) == "--seed=")
      {
	unsigned long res =
	  strtoul (arg.substr (strlen ("--seed=")).c_str (), 0, 0);
	assert (res <= static_cast <unsigned long> (UINT_MAX));
	seed_ = static_cast <unsigned> (res);
      }
    else
      std::cerr << "ignored unrecognized option: " << arg << std::endl;
  }

  void
  Tester::process_options (int argc, char **argv)
  {
    for (int i = 1; i < argc; ++i)
      process_option (argv[i]);
  }


  Tester::verbose_level
  Tester::verbose() const
  {
    return verbose_;
  }

  bool Tester::verbose(verbose_level l) const
  {
    return verbose_ <= l;
  }


  unsigned
  Tester::seed() const
  {
    return seed_;
  }


  unsigned
  Tester::test_num() const
  {
    // There is no need for a big number here, as the test suite was
    // already run for quite a while, and is still frequently run
    // anyway.
    return 5;
  }



  bool
  Tester::all_passed()
  {
    return failed_ == 0;
  }

  void
  Tester::ok_or_ko(std::string test_label, bool pass)
  {
    if (verbose (low))
      std::cerr << (pass ? "PASS" : "FAIL")
		<< ": " << test_label << std::endl;
    if (pass)
      passed_++;
    else
      failed_++;
  }

  void
  Tester::ok(std::string test)
  {
    ok_or_ko (test, true);
  }

  void
  Tester::ko(std::string test)
  {
    ok_or_ko (test, false);
  }

  // FIXME: Add statistics stuff.

} // tests
