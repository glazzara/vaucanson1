// Sample file for alphabet manipulation inside Vaucanson
//
// alphabet.cc

#include <iostream>

struct basic_alphabet
{
  typedef char letter_t;
  typedef char* iterator;
  typedef const char* const_iterator;

  static const char first = 'a';
  static const char second = 'b';

  size_t size() const
  { 
    return 2; 
  }

  const_iterator begin() const
  {
    static const char tmp = first;
    return &tmp;
  }

  const_iterator end() const
  {
    static const char tmp = second;
    return &tmp;
  }

};



#include <vaucanson/algebra/concrete/alphabets/predefs.hh>


int main(int argc, char** argv)
{
  
  using namespace vcsn;
  using namespace algebra;
//   using namespace small_alpha_letter;
  
  using std::cout;
  using std::endl;
  
//   Alphabet A;
  
//   Letter a('a');

//   A.insert(a);
//   A.insert(Letter('b'));
  
//   cout << "Size of alphabet : "
//        << A.size() << endl;                // return 2
  
  
//   cout << "Is \'a\' inside alphabet ? (0 or 1) : "
//        << A.contains('a') << endl;         //return true

//   cout << "Is \'1\' inside alphabet ? (0 or 1) : "
//        << A.contains('1') << endl;         //return false
  
  
//   cout << "element of alphabet are : ";
//   for (Alphabet::iterator i = A.begin(); i != A.end(); i++)
//     cout << *i << " ";
//   cout << endl;
  
//   cout << "random sequence of 10 symbols of alphabet : ";
//   for (unsigned i = 0; i < 10; i++)
//     cout << A.choose() << " ";
//   cout << endl;
    
   


  typedef const Element<SetAlphabets<char>, basic_alphabet> Alphabet;

  Alphabet a;


  cout << a.size() << endl;

  cout << *a.end() << endl;
  cout << *a.begin() << endl;

  cout << a.is_finite() << endl;
  cout << a.contains('a') << endl;
  cout << a.contains('b') << endl;
  cout << a.contains('d') << endl;

  for (unsigned i = 0; i < 10; i++)
    cout << a.choose() << endl;

  return 0;
}
