#include <vaucanson/config/system.hh>
#include <vaucanson/misc/static.hh>
#include <cassert>

using namespace utility;

void xassert(bool b)
{
  assert(b == true);
}

struct v {};

int main()
{
  int a = -1;
  const int b = -2;
  remove_reference<int>::t x = 0;
  remove_reference<int&>::t y = 1;
  remove_reference<const int&>::t z = 2;

  xassert(static_if<false, int, int>::choose(x, y) == y);
  xassert(static_if<true, int, int>::choose(x, y) == x);
  xassert(static_if<false, int, int>::choose(a, b) == b);
  xassert(static_if<false, int, int>::choose(a, x) == x);
  
  static_if<true, int, v>::t i = 3;
  static_if<false, v, int>::t j = 4;

  xassert(static_eq<int, int>::value);
  xassert(! static_eq<int, v>::value);

  xassert(static_pow<0, 10>::value == 0);
  xassert(static_pow<1, 10>::value == 1);
  xassert(static_pow<2, 16>::value == 1 << 16);
  xassert(static_pow<3, 3>::value == 27);

  xassert(static_pow_minus_one<1, 10>::value == 0);
  xassert(static_pow_minus_one<2, 16>::value == (1 << 16) - 1);
  xassert(static_pow_minus_one<3, 3>::value == 26);

  return 0;
}
