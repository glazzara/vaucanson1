#include <vaucanson/config/system.hh>
#include <string>
#include <cassert>

std::string tag;

namespace a 
{
  template<typename T>
  struct A {};
  
  struct B {};

  template<typename T>
  bool operator==(const A<T>&, const A<T>&)
  { 
    tag += "a";
    return true;
  }

  bool operator==(const B&, const B&)
  {
    tag += "b";
    return true;
  }

}

namespace b
{
  void test()
  {
    a::A<void> a;
    a::B b;
    tag = "";
    assert(a == a);
    assert(b == b);
    assert(tag == "ab");
  }

  template<typename T>
  struct A
  { };

  template<typename T>
  bool operator==(const A<T>&, const A<T>&)
  {
    tag += "c";
    return true;
  }

}

void test()
{
  a::A<void> a;
  a::B b;
  b::A<void> c;
  tag = "";
  assert(a == a);
  assert(b == b);
  assert(c == c);
  assert(tag == "abc");
}

int main()
{
  b::test();
  ::test();
  return 0;
}

