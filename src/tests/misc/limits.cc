#include <vaucanson/misc/limits.hh>
#include "check/tester.hh"

#define NATTR(Attr)  \
std::cout << #Attr "\t:" << utility::limits<T>::Attr << std::endl

template<typename T>
void test_limits()
{
  TEST_GROUP(std::string("numeric limits for ") + typeid(T).name());
  NATTR(digits);
  NATTR(digits10);
  NATTR(is_specialized);
  NATTR(min());
  NATTR(max());
  NATTR(has_infinity);
  NATTR(has_quiet_NaN);
  NATTR(is_signed);
  NATTR(is_integer);
  NATTR(is_exact);
  NATTR(radix);
  NATTR(is_iec559);
  NATTR(is_bounded);
  NATTR(is_modulo);
}

int main()
{
  test_limits<bool>();
  test_limits<signed char>();
  test_limits<unsigned char>();
  test_limits<int>();
  test_limits<unsigned int>();
  test_limits<float>();
}


