// element-full-test.cc
//
// $Id$
// VCSN_HEADER

// Goal: 
// - to instantiate all services of element parameterized by empty classes.
//

#include <tests/tests_stuff.hh>
#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>

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


template <class Tset, class Tvalue> void test_design_pattern(const Tvalue& sample)
{
  vcsn::Element<Tset, Tvalue> a;
  vcsn::Element<Tset, Tvalue> b;
  
  a == b;
  a != b;
  a < b;
  a > b;
  a <= b;
  a >= b;
  //  a + b;
  //a - b;
//   a * b;
//   a / b;
//   a % b;
//   -a;
 a == sample;
 sample == a;
 a != sample;
 sample != a;
 a < sample;
   sample < a;
   a > sample;
  sample > a;
  a <= sample;
  sample <= a;
  a >= sample;
  sample >= a;
  // swap(a,a);
  // ambigu
}

int main(int argc, char **argv)
{
  tests::Tester t(1);
  
  test_design_pattern<Natural, int>(42);
  
  test_design_pattern<algebra::Alphabets<char>, std::set<char> >(std::set<char>());
  
//   TEST(t, "Method A::foo()", 
//   { 
//     A::foo(); true; 
//   }); 

  if (t.all_passed())
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

