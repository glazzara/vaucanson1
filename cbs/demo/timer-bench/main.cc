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

Timer global_timer;

void recursion(int n)
{
  BENCH_TASK_START("recursion");
  if (n > 0)
    recursion(--n);
  BENCH_TASK_STOP();
}

int main()
{
  int n;

  for (n = 100000; n < 5000000; n *= 2)
  {
    BENCH_START("timer-scoped", "Empty scoped tasks.");

    for (int i = 0; i < n; ++i)
    {
      BENCH_TASK_SCOPED("Scoped");
    }

    {
      BENCH_STOP();

      std::stringstream parameter;
      parameter << n;

      BENCH_PARAMETER("empty scopes", parameter.str());
      BENCH_PARAMETER("tasks", "1");

      std::string name = "timer-scoped_" + parameter.str();


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

  for (n = 100000; n < 5000000; n *= 2)
  {
    BENCH_START("timer-start-stop", "Empty tasks started and stopped.");

    for (int i = 0; i < n; ++i)
    {
      BENCH_TASK_START("Task");
      BENCH_TASK_STOP();
    }

    {
      BENCH_STOP();

      std::stringstream parameter;
      parameter << n;

      BENCH_PARAMETER("empty scopes", parameter.str());
      BENCH_PARAMETER("tasks", "1");

      std::string name = "timer-start-stop_" + parameter.str();


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

  for (n = 10; n < 100; n += 20)
  {
    BENCH_START("timer-many-tasks", "Many empty tasks (started and stopped).");

    global_timer.start();

    BENCH_TASK_START("init");
    for (int i = 0; i < n; ++i)
    {
      std::stringstream parameter;
      parameter << i;
      global_timer.push("task_" + parameter.str());
      global_timer.pop();
    }
    BENCH_TASK_STOP();

    BENCH_TASK_START("test");
    for (int i = 0, j = 0; i < 1000000; ++i, ++j)
    {
      if (j == n)
	j = 0;
      std::stringstream parameter;
      parameter << j;
      global_timer.push("task_" + parameter.str());
      global_timer.pop();
    }
    BENCH_TASK_STOP();

    BENCH_TASK_START("compute results");
    {
      global_timer.stop();
    }
    BENCH_TASK_STOP();

    {
      BENCH_STOP();

      std::stringstream parameter;
      parameter << n;

      BENCH_PARAMETER("tasks", parameter.str());
      BENCH_PARAMETER("empty scopes", "1000000");

      std::string name = "timer-many-tasks_" + parameter.str();


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

  for (n = 10000; n < 100000; n += 20000)
  {
    BENCH_START("timer-many-tasks", "Many empty tasks (started and stopped).");

    global_timer.start();

    BENCH_TASK_START("init");
    for (int i = 0; i < n; ++i)
    {
      std::stringstream parameter;
      parameter << i;
      global_timer.push("task_" + parameter.str());
      global_timer.pop();
    }
    BENCH_TASK_STOP();

    BENCH_TASK_START("test");
    for (int i = 0, j = 0; i < 1000000; ++i, ++j)
    {
      if (j == n)
	j = 0;
      std::stringstream parameter;
      parameter << j;
      global_timer.push("task_" + parameter.str());
      global_timer.pop();
    }
    BENCH_TASK_STOP();

    BENCH_TASK_START("compute results");
    {
      global_timer.stop();
    }
    BENCH_TASK_STOP();

    {
      BENCH_STOP();

      std::stringstream parameter;
      parameter << n;

      BENCH_PARAMETER("tasks", parameter.str());
      BENCH_PARAMETER("empty scopes", "1000000");

      std::string name = "timer-many-tasks_" + parameter.str();


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

  for (n = 1; n < 100000; n *= 2)
  {
    BENCH_START("timer-recursion", "Many nested tasks.");

    recursion(n);

    {
      BENCH_STOP();

      std::stringstream parameter;
      parameter << n;

      BENCH_PARAMETER("depth", parameter.str());

      std::string name = "timer-recursion_" + parameter.str();


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

