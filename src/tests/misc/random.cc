#include <vaucanson/misc/random.hh>
#include <cassert>
#include <climits>
#include <iostream>

#define MAXITER 1000

int main()
{
#define TEST_TYPE(Type, MAX)					\
  for (int i = 0; i < MAXITER; ++i)				\
    {								\
      Type c = utility::random::generate< Type >();		\
      Type min = utility::random::generate< Type >(0, MAX);	\
      Type max = utility::random::generate< Type >(min, MAX);	\
      c = utility::random::generate< Type >(min, max);		\
      if (!(min <= c && max >= c)) \
      { \
  std::cerr << "random failed: min = " << min \
            << ", max = " << max \
            << ", val = " << c << std::endl; \
        exit(1); \
      } \
    }
  TEST_TYPE(char, CHAR_MAX);
  TEST_TYPE(int, INT_MAX);
  for (int i = 0; i < MAXITER; ++i)
    {
      bool b = utility::random::generate<bool>();
      assert(b || !b);
    }
  for (int i = 0; i < MAXITER; ++i)
    {
      float f = utility::random::generate<float>();
      assert(f >= 0. && f <= 1.);
    }
}
