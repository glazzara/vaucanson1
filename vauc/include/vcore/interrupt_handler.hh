#ifndef CORE_INTERRUPT_HANDLER_HH
#define CORE_INTERRUPT_HANDLER_HH

#include <string>

namespace vcsn
{
  namespace vauc
  {
    void init_interrupt_handler(void);
    bool interrupted();
    const std::string& describe_interrupt();
    void interrupt_ack();
  }
}
#endif
