#include "kern/object.hh"

using namespace cppsh;

class A
{
public:
  A();
  A(const A& a);
  ~A();
};

void point();

int main()
{
  point();
  Object a;
  point();
  {
    ref<A> ra = new A;
    point();
    Object x = ra;
    point();
    Object y = x;
    point();
    Object z = y.clone();
    point();
    ref<A> rz = OBJECT_AS_REF(z, A);
    point();
    ref<A> rw = rz;
    point();
    a = rw;
    point();
  }
  point();
}


