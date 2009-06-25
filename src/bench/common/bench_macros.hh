// bench_macros.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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

#ifndef VCSN_BENCHS_COMMON_BENCH_MACROS_HH
# define VCSN_BENCHS_COMMON_BENCH_MACROS_HH

# include <config.h>
# include <cbs/bench/bench_macros.hh>

# define BENCH_OPENFST_ISYMBOLS VCSN_SRC_DIR "/src/bench/common/alpha.syms"

# define BENCH_OPENFST_DUMP(Name, Automaton)		\
  do {							\
    std::ofstream dumpfile(Name.c_str());		\
    fsm_dump(dumpfile, Automaton);			\
    dumpfile.close();					\
  } while (0)


# define BENCH_VCSN_SAVE_AND_PRINT(Name)				\
  BENCH_SAVE(Name + ".xml", bench::Options());				\
  BENCH_SAVE(Name + ".out", bench::Options(bench::Options::VE_MINIMAL,	\
					   bench::Options::FO_TEXT));	\
  BENCH_SAVE(Name + ".dot", bench::Options(bench::Options::VE_NORMAL,	\
					   bench::Options::FO_DOT));	\
  BENCH_PRINT(bench::Options(bench::Options::VE_NORMAL,			\
			     bench::Options::FO_TEXT,			\
			     0));


#endif // ! VCSN_BENCHS_COMMON_BENCH_MACROS_HH
