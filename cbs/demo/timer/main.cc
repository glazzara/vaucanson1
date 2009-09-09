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
#include <cbs/bench/timer.hh>

#define WAIT(Duration)				\
  for (int j = 0; j < 10; ++j)			\
    for (int k = 0; k < 270 * Duration; ++k)	\
    {						\
      int* i = new int(4);			\
      delete i;					\
    }

using namespace timer;

Timer global_timer;

void a();
void b(int);
void c(int);
void d(int);
void e();

int main()
{
  global_timer.start();

  a();

  for (int i = 0; i < 100; ++i)
    e();

  global_timer.stop();

  global_timer.dump(std::cout);
  global_timer.export_dot(std::cerr, timer::VERBOSE_MINIMAL);
}

void a()
{
  ScopedTimer s(global_timer, "Task A");

  for (int i = 0; i < 42; ++i)
  {
    b(5);
  }
}

void b(int x)
{
  ScopedTimer s(global_timer, "Task B");

  WAIT(2)

  c(x);
}

void c(int x)
{
  ScopedTimer s(global_timer, "Task C");

  WAIT(1)

  d(x);
}

void d(int x)
{
  ScopedTimer s(global_timer, "Task D");

  WAIT(5)

  if (x > 0)
    b(x - 1);
}

void e()
{
  ScopedTimer s(global_timer, "Task E");

  WAIT(3)

  d(0);
}
