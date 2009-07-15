// bench_macros.hh: this file is part of the CBS project.
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

#ifndef BENCH_BENCH_MACROS_HH
# define BENCH_BENCH_MACROS_HH

/**
 *  \file src/bench_macros.hh
 *  \brief Convenient macros to equip C++ code with benchmarking measures.
 */

# ifndef BENCH_DISABLED

#  include <cbs/bench/bench.hh>

#  define BENCH_START(Name, Description)  bench::start(Name, Description)
#  define BENCH_STOP()                    bench::stop()
#  define BENCH_PARAMETER(Name, Value)    bench::parameter(Name, Value)
#  define BENCH_RESULT(Name, Value)       bench::result(Name, Value)

#  ifndef BENCH_CALLGRAPH_DISABLED
#   define BENCH_TASK_START(Name)         bench::task_start(Name)
#   define BENCH_TASK_STOP()              bench::task_stop()
#   define BENCH_TASK_SCOPED(Name)        bench::ScopedTask bench_task(Name)
#  else
#   define BENCH_TASK_START(Name)         void(0)
#   define BENCH_TASK_STOP()              void(0)
#   define BENCH_TASK_SCOPED(Name)        void(0)
#  endif //!BENCH_CALLGRAPH_DISABLED

#  ifndef BENCH_MEMPLOT_DISABLED
#   define BENCH_MEMPLOT(Description)     bench::memplot(Description)
#  else
#   define BENCH_MEMPLOT(Decription)      void(0)
#  endif //!BENCH_MEMPLOT_DISABLED

#  define BENCH_PRINT(Options)            bench::print(Options)
#  define BENCH_DUMP(Stream, Options)     bench::dump(Stream, Options)
#  define BENCH_SAVE(Filename, Options)   bench::save(Filename, Options)

# else

#  define BENCH_START(Name, Description)  void(0)
#  define BENCH_STOP()                    void(0)
#  define BENCH_PARAMETER(Name, Value)    void(0)
#  define BENCH_RESULT(Name, Value)       void(0)
#  define BENCH_TASK_START(Name)          void(0)
#  define BENCH_TASK_STOP()               void(0)
#  define BENCH_TASK_SCOPED(Name)         void(0)
#  define BENCH_MEMPLOT(Description)      void(0)
#  define BENCH_PRINT(Options)            void(0)
#  define BENCH_DUMP(Stream, Options)     void(0)
#  define BENCH_SAVE(Filename, Options)   void(0)

# endif //!BENCH_DISABLED

#endif //!BENCH_MACROS_HH
