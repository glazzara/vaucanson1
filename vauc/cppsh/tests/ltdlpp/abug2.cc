#include "kern/object.hh"
#include <iostream>
#include "s.hh"
using cppsh::Object;

extern "C" Object liba2_LTX_make_a()
{ 
  Object x = S<int>(); 
  std::cout << "make_a : S<int> typeinfo at " << &x.cpp_type() << std::endl;
  return x;
}

static struct Cerberos
{
  Cerberos()
  { 
    std::cout << "liba::Cerberos() @ " << this << " : " ;
    Object x = S<int>();
    std::cout << "S<int> typeinfo at " << &x.cpp_type() << std::endl;
  }

  ~Cerberos()
  { 
    std::cout << "liba::~Cerberos() @ " << this << " : " ;
    Object x = S<int>();
    std::cout << "S<int> typeinfo at " << &x.cpp_type() << std::endl;
  }

} __liba2_cerberos;
