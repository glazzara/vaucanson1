#include <vaucanson/config/system.hh>
#include <vaucanson/misc/selectors.hh>
#include <typeinfo>

template<typename T>
T foo(int x, SELECTOR(T), int y)
{
  return x + y;
}


int main()
{
  return foo(-1, SELECT(int), 1);
}

