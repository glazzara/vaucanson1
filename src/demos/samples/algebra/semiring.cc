
#include <iostream>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
#include <vaucanson/algebra/concrete/semiring/tropical_semiring.hh>

int main()
{
  using namespace vcsn;
  using namespace algebra;

  using std::cout;
  using std::endl;

  Element<NumericalSemiring, int> e1 = 1;
  Element<NumericalSemiring, int> e2 = 2;

  
  // zero is neutral element for addition ...
  cout << e1 + e1.set().zero(SELECT(int)) << endl;
  // zero is absorbant element for multiplication
  cout << e1 * e1.set().zero(SELECT(int)) << endl;

  cout << e1 + e1.set().identity(SELECT(int)) << endl;
  // 1 (identity) is neutral element for multiplication
  cout << e1 * e1.set().identity(SELECT(int)) << endl;


  cout << e1 + e2 << endl;
  cout << e1 * e2 << endl;
  
  cout << e1 + 3 << endl;
  cout << e1 * 3 << endl;
 
  cout << endl; 

  Element<TropicalSemiring<TropicalMax>, int> e4 = 2;
  Element<TropicalSemiring<TropicalMax>, int> e5 = 3;
  Element<TropicalSemiring<TropicalMax>, int> e6 = 0;
 
  cout << e4 + e4.set().zero(SELECT(int)) << endl;
  cout << e4 * e4.set().zero(SELECT(int)) << endl;
  
  cout << e4 + e4.set().identity(SELECT(int)) << endl;
  cout << e4 * e4.set().identity(SELECT(int)) << endl;

  // big surprise !!!
  cout << e5 + e6 << endl;
  cout << e5 * e6 << endl;
  
//   cout << e4 + 3 << endl;
//   cout << e4 * 3 << endl;
  
  return 0;
}
