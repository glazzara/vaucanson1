#include <iostream>
#include <cassert>


/*
 * Some people run the testsuite with -DNDEBUG, which is plain
 * stupid. Check it.
 */
int main()
{
  assert(false);
  std::cerr << "assert() does not work or is disabled." << std::endl;
  return 0;
}
