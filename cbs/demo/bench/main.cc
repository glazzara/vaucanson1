// main.cc: this file is part of the CBS project.
//
// CBS, a C++ benchmarking suite.
//
// Copyright (C) 2007, 2009 The CBS Authors.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the Do What The Fuck You Want To
// Public License (WTFPL) version 2.
//
// The complete WTFPL license text can be found as the
// `COPYING' file in the root directory.
//
// The CBS Authors consists of people listed in the `AUTHORS' file.
//

#include <iostream>
#include <sstream>
#include <list>
#include <cbs/bench/bench_macros.hh>

#define WAIT(Duration)				\
  for (int j = 0; j < 10; ++j)			\
    for (int k = 0; k < 270 * Duration; ++k)	\
    {						\
      int* i = new int(4);			\
      delete i;					\
    }

#define CONSUME(Memory)				\
  {						\
    std::list<int> list;			\
    for (int j = 0; j < Memory; ++j)		\
      for (int k = 0; k < 250000; ++k)		\
      {						\
        list.push_back(k);			\
      }						\
    BENCH_MEMPLOT("Memory consumption");	\
    list.clear();				\
  }

void a();
void b(int);
void c(int);
void d(int);
void e();

int main()
{
  for (int n = 1, iter = 0; iter <= 20; n *= 2, ++iter)
  {

    BENCH_START("Bench demo", "A simple benchmark with a single parameter");

    std::cout << "[" << iter << "] Bench for n=" << n << "..." << std::endl;

    a();

    for (int i = 0; i < n; ++i)
      e();

    CONSUME(10 + iter * 10)

    BENCH_STOP();

    BENCH_PARAMETER("iteration", (long) iter);

    BENCH_PARAMETER("n", (long) n);

    std::stringstream name_str;
    name_str << "benchmark_" << n;
    std::string name = name_str.str();

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

void a()
{
  BENCH_TASK_SCOPED("Task A");

  for (int i = 0; i < 42; ++i)
  {
    b(5);
  }
}

void b(int x)
{
  BENCH_TASK_SCOPED("Task B");

  WAIT(2)

  c(x);
}

void c(int x)
{
  BENCH_TASK_SCOPED("Task C");

  WAIT(4)

  d(x);
}

void d(int x)
{
  BENCH_TASK_SCOPED("Task D");

  WAIT(1)

  if (x > 0)
    b(x - 1);
}

void e()
{
  BENCH_TASK_SCOPED("Task E");

  CONSUME(50)
  WAIT(1)

  d(0);
}
