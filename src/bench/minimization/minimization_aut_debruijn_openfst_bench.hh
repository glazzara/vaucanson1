// minimization_aut_debruijn_openfst_bench.hh: this file is part of the Vaucanson project.
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

#include <iostream>
#include <cstdio>

#include <sys/types.h>
#include <sys/wait.h>

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/tools/fsm_dump.hh>

using namespace vcsn;
using namespace vcsn::boolean_automaton;
using namespace vcsn::tools;

#include <common/bench_constructs.hh>
#include <common/bench_macros.hh>

static pid_t fork_and_wait()
{
  pid_t forked = fork();
  if (forked < 0)
  {
    std::cerr << "Error: failed to fork and execute OpenFST.  Exiting..."
	      << std::endl;
    exit(-1);
  }
  if (forked > 0)
  {
    waitpid(forked, NULL, 0);
  }
  return forked;
}

void minimization_aut_debruijn_openfst_bench(int n)
{
#ifndef OPENFST_PATH
  return;
#else
  if (not n)
    return;

  automaton_t a = aut_debruijn(n);

  std::string fsmname = "aut_debruijn_openfst/aut_debruijn.fsm";
  std::string fstin = "aut_debruijn_openfst/in.fst";
  std::string fstout = "aut_debruijn_openfst/out.fst";

  BENCH_OPENFST_DUMP(fsmname, a);

  BENCH_START("OpenFST minimization",
	      "Automaton minimization benchmark using OpenFST.\n"
	      "\n"
	      "FIXME (input).\n"
	      "\n"
	      "Process:\n"
	      "\n"
	      "1. Generate the input automaton (with parameter _n_).\n"
	      "2* Run fstcompile on the input automaton (fork() + execl()).\n"
	      "3* Run fstminimize on the result (fork() + execl()).\n");

  {
    pid_t forked = fork_and_wait();
    if (forked == 0)
      execl(std::string(OPENFST_PATH "/fstcompile").c_str(),
	    std::string(OPENFST_PATH "/fstcompile").c_str(),
	    std::string("--isymbols=" BENCH_OPENFST_ISYMBOLS).c_str(),
	    fsmname.c_str(), fstin.c_str(), 0);
  }

  {
    pid_t forked = fork_and_wait();
    if (forked ==0)
      execl(std::string(OPENFST_PATH "/fstminimize").c_str(),
	    std::string(OPENFST_PATH "/fstminimize").c_str(),
	    fstin.c_str(), fstout.c_str(), 0);
  }

  BENCH_STOP();

  BENCH_PARAMETER("_n_", (long) n);
  BENCH_PARAMETER("program", "OpenFST");
  BENCH_PARAMETER("input automaton", "aut_debruijn");

  std::stringstream name;
  name << "aut_debruijn_openfst/bench_minimization_aut_debruijn_openfst_" << n;

  BENCH_VCSN_SAVE_AND_PRINT(name.str());

  remove(fsmname.c_str());
  remove(fstin.c_str());
  remove(fstout.c_str());

#endif // OPENFST_PATH
}
