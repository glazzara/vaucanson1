// main.cc: this file is part of the CBS project.
//
// CBS, a C++ benchmarking suite.
//
// Copyright (C) 2007, 2008, 2009 The CBS authors.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The CBS Authors consists of people listed in the `AUTHORS' file.
//

#include <iostream>
#include <sstream>
#include <list>
#include <cbs/bench/bench_macros.hh>

int main()
{
  BENCH_START("Bench demo", "A simple benchmark with a single parameter");

  int maxn = 6;

  std::cout << "Benchmarking (n = " << maxn << ")..." << std::endl;

  int n = 1;
  for (; n <= maxn; ++n)
  {
    std::list<int> ilist;
    std::list<std::string> slist;

    {
      BENCH_TASK_SCOPED("ilist");
      for (int j = 0; j < n * 100; ++j)
	for (int k = 0; k < 25000; ++k)
	{
	  ilist.push_back(k);
	}
      BENCH_MEMPLOT("ilist filled");
    }
    {
      BENCH_TASK_SCOPED("slist");
      for (int j = 0; j < n * 20; ++j)
	for (int k = 0; k < 25000; ++k)
	{
	  slist.push_back("Memplot test string");
	}
      BENCH_MEMPLOT("slist filled");
    }
    ilist.clear();
    BENCH_MEMPLOT("ilist cleared");
    slist.clear();
    BENCH_MEMPLOT("slist cleared");

  }

  BENCH_STOP();

  BENCH_PARAMETER("n", (long) maxn);

  std::stringstream name_str;
  name_str << "benchmark_" << maxn;
  std::string name = name_str.str();

  BENCH_PRINT(bench::Options(bench::Options::VE_NORMAL,
			     bench::Options::FO_TEXT,
			     0));

  BENCH_SAVE(name + ".out", bench::Options(bench::Options::VE_NORMAL,
					   bench::Options::FO_TEXT));
  BENCH_SAVE(name + ".xml", bench::Options());
  BENCH_SAVE(name + ".dot", bench::Options(bench::Options::VE_MINIMAL,
					   bench::Options::FO_DOT));
  BENCH_SAVE(name + ".plot", bench::Options(bench::Options::VE_NORMAL,
					    bench::Options::FO_GNUPLOT,
					    bench::Options::CO_MEMPLOT));
}
