#include "kern/symbol.hh"
#include <iostream>
#include <cassert>

using cppsh::Symbol;

int main()
{
  Symbol s1 = "hello";
  Symbol s2 = std::string("hello");

  assert(VERY_EQUAL_SYMBOLS(s1, s2));

  Symbol s3 = " world";

  Symbol s4 = s1.value() + s3.value();

  Symbol s5 = s4;

  assert(s4 == s5);
  assert(s5 != s2);

  assert(s5.value() == "hello world");

}
