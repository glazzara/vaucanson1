#include "kern/object.hh"
#include <iostream>
#include "s.hh"

using cppsh::Object;

extern "C" Object libb2_padding_code()
{
  // some stuff to make liba and libb differ.
  std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	    << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
  return Object();
}

extern "C" Object libb2_LTX_make_b()
{ 
  Object x = S<int>(); 
  std::cout << "make_b : S<int> typeinfo at " << &x.cpp_type() << std::endl;
  return x;
}

static struct Cerberos
{
  Cerberos()
  { 
    std::cout << "libb::Cerberos() @ " << this << " : " ;
    Object x = S<int>();
    std::cout << "S<int> typeinfo at " << &x.cpp_type() << std::endl;
  }

  ~Cerberos()
  { 
    std::cout << "libb::~Cerberos() @ " << this << " : " ; 
    Object x = S<int>();
    std::cout << "S<int> typeinfo at " << &x.cpp_type() << std::endl;
  }

} __libb2_cerberos;
