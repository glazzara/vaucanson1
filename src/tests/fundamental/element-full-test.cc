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

}

using namespace vcsn;


int main(int argc, char **argv)
{
  tests::Tester t(1);


  // vcsn::Element<int, int> *tmp = new vcsn::Element<int, int>();


  Element<Natural, int> a2;




 

  // constructors tests
  vcsn::Element<Natural, int > *a1 = 
    new vcsn::Element<Natural, int >();  

  Element<Natural, float> a4(a2);

  vcsn::Element<Natural, int > *a3 = 
    new vcsn::Element<Natural, int >(*a1);  

  //*a3 = *a1;

  a4 = a2;
  


  //a1 = *tmp;
 



//   TEST(t, "Method A::foo()", 
//   { 
//     A::foo(); true; 
//   }); 

  if (t.all_passed())
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

