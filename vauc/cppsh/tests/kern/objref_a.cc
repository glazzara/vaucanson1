#include <iostream>

class A
{
public:
  A();
  A(const A& a);
  ~A();
};

A::A()
{ std::cout << this << "->A()" << std::endl; }

A::A(const A& a)
{ std::cout << this << "->A(" << &a << ")" << std::endl; }

A::~A()
{ std::cout << this << "->~A()" << std::endl; }

void point()
{ std::cout << "mark." << std::endl; }
