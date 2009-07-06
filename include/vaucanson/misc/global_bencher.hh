// global_bencher.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#ifndef VCSN_MISC_GLOBAL_BENCHER_HH
# define VCSN_MISC_GLOBAL_BENCHER_HH

/*-------------------.
| Use of a Bencher.  |
`-------------------*/

# ifdef GLOBAL_BENCHER

#  include <cbs/bench/bench.hh>
#  include <cbs/bench/bench_internals.hh>

#  ifdef VAUCANSON
#   include <vaucanson/misc/bencher.hh>
#  else
#   include "bencher.hh"
#  endif

#  define BENCHER_DO(Iterations)					\
  for (unsigned i_ = 1;	i_ <= (Iterations);				\
       ++i_, GLOBAL_BENCHER.push(bench::current_timer()), bench::restart())

# define BENCHER_PRINT(Stream)				\
  Stream << GLOBAL_BENCHER << std::endl

# define BENCHER_PLOT(Stream)				\
  GLOBAL_BENCHER.plot (Stream)

# define BENCHER_SAVE_PLOT(Filename)					\
  do {									\
    std::ofstream o (Filename,						\
	             std::ofstream::out | std::ofstream::trunc);	\
    BENCHER_PLOT(o);							\
    o.close();								\
  } while (0)

# else

# define BENCHER_DO(Iterations)		((void) 0)
# define BENCHER_PRINT(Stream)		((void) 0)
# define BENCHER_PLOT(Stream)		((void) 0)
# define BENCHER_SAVE_PLOT(Filename)	((void) 0)

# endif


#endif // ! VCSN_MISC_GLOBAL_BENCHER_HH
