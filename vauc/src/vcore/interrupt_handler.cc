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

  sigemptyset(&sa.sa_mask);
  sigaddset(&sa.sa_mask, SIGINT);
  sigaddset(&sa.sa_mask, SIGQUIT);
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

