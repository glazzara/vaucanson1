// Sample file for alphabet manipulation inside Vaucanson
//
// decorated_alphabet.cc

#include <iostream>

// #include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/alphabets/predefs.hh>


int main(int argc, char** argv)
{
  
  using namespace vcsn;
  using namespace algebra;
  using namespace char_letter;
  
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

  DAlphabetImpl alphabet_decorator(A.value());
  DAlphabet DA(alphabet_decorator);

  std::cout << DA.letter_equality('a', 'b') << std::endl;
  std::cout << DA.letter_equality('a', DA.joker()) << std::endl;
  std::cout << DA.letter_equality('a', DA.other()) << std::endl;
  std::cout << DA.letter_equality('c', DA.joker()) << std::endl;
  std::cout << DA.letter_equality('c', DA.other()) << std::endl;
}
