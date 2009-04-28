// main.cc: this file is part of the CBS project.
//
// CBS, a C++ benchmarking suite.
//
// Copyright (C) 2007, 2009 Florent D'Halluin.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//

#include <iostream>
#include <cbs/bench/timer.hh>
#include <cbs/bench/bench_macros.hh>

using namespace timer;

int main()
{
  int n;

  for (n = 10000; n < 500000; n *= 2)
  {
    BENCH_START("memplot", "Empty tasks.");

    for (int i = 0; i < n; ++i)
    {
      BENCH_MEMPLOT("Empty task");
    }

    {
      BENCH_STOP();

      std::stringstream parameter;
      parameter << n;

      BENCH_PARAMETER("empty tasks", parameter.str());

      std::string name = "memplot_" + parameter.str();


      BENCH_PRINT(bench::Options(bench::Options::VE_NORMAL,
				 bench::Options::FO_TEXT,
				 0));

      BENCH_SAVE(name + ".out", bench::Options(bench::Options::VE_NORMAL,
					       bench::Options::FO_TEXT,
					       0));
      BENCH_SAVE(name + ".xml", bench::Options());
      BENCH_SAVE(name + ".dot", bench::Options(bench::Options::VE_MINIMAL,
					       bench::Options::FO_DOT));
    }
  }
}

