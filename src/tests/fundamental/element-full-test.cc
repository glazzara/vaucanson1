// element-full-test.cc
//
// $Id$
// VCSN_HEADER

// Goal: 
// - to instantiate all services of element parameterized by empty classes.
//

#include <tests/tests_stuff.hh>
#include <vaucanson/fundamental/fundamental.hh>
#include <set>

namespace vcsn {

 /*template <class T>*/ struct Natural;

  /*template <class T> */ 
struct Natural : public Structure<Natural> 
{ 
  Natural() {}
  bool operator == (const Natural& other) const { return true; }
};

template<typename T>
  struct MetaElement<Natural, T>
    : MetaElement<Structure<Natural>, T>
  {
  protected:
    MetaElement() {};
    MetaElement(const MetaElement& other) {};
  };


  int op_add(const vcsn::Natural& set, int v1, int v2)
  { return v1 + v2; }

  int op_sub(const vcsn::Natural& set, int v1, int v2)
  { return v1 - v2; }

  int op_mul(const vcsn::Natural& set, int v1, int v2)
  { return v1 * v2; }

  int op_div(const vcsn::Natural& set, int v1, int v2)
  { return v1 / v2; }

  int op_mod(const vcsn::Natural& set, int v1, int v2)
  { return v1 % v2; }

  vcsn::Element<Natural, int> op_neg(const vcsn::Natural& set, int v)
  { return Element<Natural, int>(-v); } 

} // vcsn

using namespace vcsn;




int main(int argc, char **argv)
{
  tests::Tester t(1);


  // vcsn::Element<int, int> *tmp = new vcsn::Element<int, int>();


  Element<Natural, int> a;
  Element<Natural, int> b;

  int entier = 42;

  a == b;
  a != b;
  a < b;
  a > b;
  a <= b;
  a >= b;
  a + b;
  a - b;
  a * b;
  a / b;
  a % b;
  -a;
  a == entier;
  entier == a;
  a != entier;
  entier != a;
  a < entier;
  entier < a;
  a > entier;
  entier > a;
  a <= entier;
  entier <= a;
  a >= entier;
  entier >= a;
  std::swap(a,b);

//   TEST(t, "Method A::foo()", 
//   { 
//     A::foo(); true; 
//   }); 

  if (t.all_passed())
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

