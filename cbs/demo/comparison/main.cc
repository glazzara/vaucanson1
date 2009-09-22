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
#include <fstream>
#include <list>
#include <cbs/bench/bench_macros.hh>

void parent(int);
void new_integer(int);
void list_push_back(int, std::list<int>& list);
void file_io(int);

int main(int argc, char** argv)
{
  BENCH_START("Profiler comparison",
	      "A simple program that consumes time and memory\n"
	      "The parameter n defines the program complexity,\n"
	      "i.e. the time and memory taken.");

  int n;

  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " <int benchmark_depth>" << std::endl;
    return -1;
  }

  std::stringstream n_str(argv[1]);
  n_str >> n;

  if (n < 0 || n > 100)
  {
    std::cerr << "<benchmark_depth> must be between 0 and 100." << std::endl;
    return -1;
  }

  std::cout << "Bench for n=" << n << "..." << std::endl;

  parent(n);

  std::cout << "Completed." << std::endl;

  std::string name = "bench_" + std::string(argv[1]);

  BENCH_PARAMETER("n", (long) n);

  BENCH_STOP();

  BENCH_PRINT(bench::Options(bench::Options::VE_NORMAL,
			     bench::Options::FO_TEXT,
			     0));

  BENCH_SAVE(name + ".out", bench::Options(bench::Options::VE_FULL,
					   bench::Options::FO_TEXT));
  BENCH_SAVE(name + ".xml", bench::Options());
  BENCH_SAVE(name + ".dot", bench::Options(bench::Options::VE_FULL,
					   bench::Options::FO_DOT));
  BENCH_SAVE(name + "_simple.dot", bench::Options(bench::Options::VE_MINIMAL,
						  bench::Options::FO_DOT));
  BENCH_SAVE(name + ".plot", bench::Options(bench::Options::VE_NORMAL,
					    bench::Options::FO_GNUPLOT,
					    bench::Options::CO_MEMPLOT));

}

void parent(int n)
{
  BENCH_TASK_SCOPED("parent()");

  std::list<int> list;
  for (int i = 0; i < n; ++i)
  {
    new_integer(n);
    list_push_back(n, list);
    list.clear();

    std::stringstream i_str;
    i_str << i;

    BENCH_MEMPLOT("parent(" + i_str.str() + ")");
  }
}

void new_integer(int n)
{
  BENCH_TASK_SCOPED("new_integer()");

  for (int i = 0; i < n * 100000; ++i)
  {
    int* a = new int(4);
    ++(*a);
    delete a;
  }

  file_io(n);
}

void list_push_back(int n, std::list<int>& list)
{
  BENCH_TASK_SCOPED("list_push_back()");

  for (int i = 0; i < n * 100000; ++i)
  {
    list.push_back(i);
  }

  if (n > 0)
    list_push_back(n - 1, list);
}

void file_io(int n)
{
  BENCH_TASK_SCOPED("file_io()");

  std::ofstream file;

  for (int i = 0; i < n * 1000; ++i)
  {
    file.open("_dummy");
    file.close();
  }

  if (n > 0)
    new_integer(n - 1);
}
