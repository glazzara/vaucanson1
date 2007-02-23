// global_timer.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_MISC_GLOBAL_TIMER_HH
# define VCSN_MISC_GLOBAL_TIMER_HH

/*-----------------.
| Use of a Timer.  |
`-----------------*/

# ifdef GLOBAL_TIMER
#  include <vaucanson/misc/timer.hh>
#  define TIMER_START()      GLOBAL_TIMER.start ()
#  define TIMER_PUSH(Task)   GLOBAL_TIMER.push (Task)
#  define TIMER_POP(Task)    GLOBAL_TIMER.pop (Task)
#  define TIMER_STOP()       GLOBAL_TIMER.stop ()
#  define TIMER_SCOPED(Task) vcsn::misc::ScopedTimer stimer (GLOBAL_TIMER, Task)
#  define TIMER_PRINT(Stream) Stream << GLOBAL_TIMER << std::endl
# else
#  define TIMER_START()      ((void) 0)
#  define TIMER_PUSH(Task)   ((void) 0)
#  define TIMER_POP(Task)    ((void) 0)
#  define TIMER_STOP()       ((void) 0)
#  define TIMER_SCOPED(Task) ((void) 0)
#  define TIMER_PRINT(Stream) ((void) 0)
# endif


/*-------------------.
| Use of a Bencher.  |
`-------------------*/

# ifdef GLOBAL_BENCHER
#  include <vaucanson/misc/bencher.hh>

#  define BENCH_DO(Iterations)						\
  for (unsigned i_ = 1;	i_ <= (Iterations);				\
       ++i_, GLOBAL_BENCHER.push(GLOBAL_TIMER), (GLOBAL_TIMER).clear())

# define BENCH_PRINT(Stream)				\
  Stream << GLOBAL_BENCHER << std::endl

# define BENCH_PLOT(Stream)				\
  GLOBAL_BENCHER.plot (Stream)

# define BENCH_SAVE_PLOT(Filename)					\
  do {									\
    if (Filename != "")							\
    {									\
      std::ofstream o (args.plot_output_filename.c_str(),		\
		       std::ofstream::out | std::ofstream::trunc);	\
      BENCH_PLOT(o);							\
      o.close();							\
    }									\
  } while (0)

# else

#  define BENCH_DO(Iterations)		((void) 0)
# define BENCH_PRINT(Stream)		((void) 0)
# define BENCH_PLOT(Stream)		((void) 0)
# define BENCH_SAVE_PLOT(Filename)	((void) 0)

# endif


#endif // ! VCSN_MISC_GLOBAL_TIMER_HH
