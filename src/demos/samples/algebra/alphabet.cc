// Sample file for alphabet manipulation inside Vaucanson
//
// alphabet.cc

#include <iostream>


#include <vaucanson/algebra/concrete/alphabets/predefs.hh>


int main(int argc, char** argv)
{
  
  using namespace vcsn;
  using namespace algebra;
  using namespace small_alpha_letter;
  
  using std::cout;
  using std::endl;
  
  Alphabet A;
  
  Letter a('a');

  A.insert(a);
  A.insert(Letter('b'));
  
  cout << "Size of alphabet : "
       << A.size() << endl;                // return 2
  
  
  cout << "Is \'a\' inside alphabet ? (0 or 1) : "
       << A.contains('a') << endl;         //return true

  cout << "Is \'1\' inside alphabet ? (0 or 1) : "
       << A.contains('1') << endl;         //return false
  
  
  cout << "element of alphabet are : ";
  for (Alphabet::iterator i = A.begin(); i != A.end(); i++)
    cout << *i << " ";
  cout << endl;
  
  cout << "random sequence of 10 symbols of alphabet : ";
  for (unsigned i = 0; i < 10; i++)
    cout << A.choose() << " ";
  cout << endl;

  return 0;
}
