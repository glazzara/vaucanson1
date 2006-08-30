// bencher.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_BENCHER_HH
# define VCSN_TOOLS_BENCHER_HH

# ifdef VCSN_BENCH

#  include <sys/time.h>
#  include <sys/resource.h>
#  include <cstdio>
#  include <cstring>
#  include <cstdlib>
#  include <ctime>
#  include <iostream>
#  include <vector>
#  include <string>
#  include <utility>

namespace vcsn
{
  class bencher {
    public:
      bencher();
      ~bencher();

    public:
      void	start();
      void	stop();
      double	get_time();

    private:
      double	dtime();

      double	start_;
      double	stop_;
  };

  unsigned int					n_bench_indent;
  std::vector<bencher*>				v_benchers;
  std::vector< std::pair<int, bencher*> >	v_old_benchers;

#  define VCSN_BENCH_START_QUIET					\
  {									\
    v_benchers.push_back(new bencher);					\
    v_benchers.back()->start();						\
  }

#  define VCSN_BENCH_START						\
  {									\
    v_benchers.push_back(new bencher);					\
    v_benchers.back()->start();						\
    std::cerr << std::string(n_bench_indent, ' ') <<			\
      "Start bench in " << __FUNCTION__ << "..." << std::endl;		\
    n_bench_indent += 3;						\
  }

#  define VCSN_BENCH_STOP_QUIET(Result)					\
  {									\
    v_benchers.back()->stop();						\
    Result = v_benchers.back()->get_time();				\
    delete v_benchers.back();						\
    v_benchers.pop_back();						\
  }

#  define VCSN_BENCH_STOP						\
  {									\
    v_benchers.back()->stop();						\
    v_old_benchers.insert(v_old_benchers.begin(),			\
			  std::pair<int, bencher*>(n_bench_indent,	\
						   v_benchers.back()));	\
    n_bench_indent -= 3;						\
    std::cerr << std::string(n_bench_indent, ' ') <<			\
      "Stop bench in " << __FUNCTION__ << "..." << std::endl;		\
    v_benchers.pop_back();						\
  }

#  define VCSN_BENCH_PRINT						\
  {									\
    std::cerr << std::string(v_old_benchers.back().first, ' ') <<	\
      __FUNCTION__ << ": " <<						\
      v_old_benchers.back().second->get_time() << std::endl;		\
    delete v_old_benchers.back().second;				\
    v_old_benchers.pop_back();						\
  }

#  define VCSN_BENCH_STOP_AND_PRINT					\
  {									\
    v_benchers.back()->stop();						\
    std::cerr << std::string(n_bench_indent, ' ') <<			\
      __FUNCTION__ << ": " <<						\
      v_benchers.back()->get_time() << std::endl;			\
    n_bench_indent -= 3;						\
    std::cerr << std::string(n_bench_indent, ' ') <<			\
      "Stop bench in " << __FUNCTION__ << "..." << std::endl;		\
    delete v_benchers.back();						\
    v_benchers.pop_back();						\
  }

} // vcsn



#  ifndef VCSN_USE_INTERFACE_ONLY
#   include <vaucanson/tools/bencher.hxx>
#  endif // VCSN_USE_INTERFACE_ONLY

# else // VCSN_BENCH

#  define VCSN_BENCH_START
#  define VCSN_BENCH_STOP
#  define VCSN_BENCH_PRINT
#  define VCSN_BENCH_STOP_AND_PRINT
#  define VCSN_BENCH_START_QUIET
#  define VCSN_BENCH_STOP_QUIET

# endif // ! VCSN_BENCH
#endif // ! VCSN_TOOLS_BENCHER_HH
