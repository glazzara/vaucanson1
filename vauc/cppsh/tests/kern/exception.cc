#include "kern/exception.hh"
#include "kern/exnprint.hh"

using namespace cppsh;

void bar()
{
  failwith("bar", "doing nothing", "jeez!");
}

void foo()
{
  try
    {
      bar();
    }
  catch(Exception& e)
    {
      e.add_trace("foo", "calling bar");
      throw;
    }
}

void baz()
{
  foo();
}

int main()
{
  try
    {
      baz();
    }
  catch(Exception& e)
    {
      std::cout << e << std::endl;
    }
}
