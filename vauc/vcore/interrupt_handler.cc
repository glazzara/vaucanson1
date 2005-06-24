// interrupt_handler.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include <vcore/interrupt_handler.hh>
#include <csignal>
#include <iostream>

static bool _interrupted = false;
static std::string _sig = "<no interrupt yet>";

extern "C" void _sighandler(int sig)
{
  _interrupted = true;
  switch(sig)
    {
    case SIGINT:
      _sig = "SIGINT"; break;
    case SIGQUIT:
      _sig = "SIGQUIT"; break;
    default:
      _sig = "<unknown signal>"; break;
    }
}

extern "C" int _init_sigs()
{
  struct sigaction sa;
  int errs = 0;

  sigemptystructure(&sa.sa_mask);
  sigaddstructure(&sa.sa_mask, SIGINT);
  sigaddstructure(&sa.sa_mask, SIGQUIT);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = &_sighandler;
  
  if (sigaction(SIGINT, &sa, NULL))
    ++errs;
  if (sigaction(SIGQUIT, &sa, NULL))
    ++errs;
  if (sigprocmask(SIG_BLOCK, &sa.sa_mask, NULL))
    ++errs;
  return errs;
}

namespace vcsn
{
  namespace vauc
  {
    void init_interrupt_handler(void)
    {
      std::cerr << "Initializing interrupt handler... ";

      if (::_init_sigs())
	std::cerr << "Some errors occured.";
      std::cerr << std::endl;
    }
    bool interrupted()
    {
      return ::_interrupted;
    }

    const std::string& describe_interrupt()
    {
      return ::_sig;
    }
    void interrupt_ack()
    {
      ::_interrupted = false;
    }

  }
}

