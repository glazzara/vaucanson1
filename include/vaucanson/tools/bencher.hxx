// bencher.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_BENCHER_HXX
# define VCSN_TOOLS_BENCHER_HXX

# include <vaucanson/tools/bencher.hh>

# ifdef VCSN_BENCH

namespace vcsn
{

  bencher::bencher() : start_(0), stop_(0)
  {}

  bencher::~bencher()
  {}

  void bencher::start()
  { start_ = dtime(); }


  void bencher::stop()
  { stop_ = dtime(); }


  double bencher::get_time()
  { return stop_ - start_; }

  double	bencher::dtime()
  {
    double		q;
    struct rusage	rusage;

    getrusage(RUSAGE_SELF, &rusage);
    q = (double)(rusage.ru_utime.tv_sec);
    q = q + (double)(rusage.ru_utime.tv_usec) * 1.0e-06;
    return q;
  }
}
# endif // ! VCSN_BENCH
#endif // ! VCSN_TOOLS_BENCHER_HXX
