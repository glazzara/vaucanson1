//
//
// free_monoid.cc


#include <iostream>
#include <string>
#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>


int main()
{
  
  using namespace vcsn::algebra::char_letter;

  using std::cout;
  using std::endl;
  using std::string;

  Alphabet a;

  a.insert('a');
  a.insert('b');

  Words free_monoid(a);
  Word  str(free_monoid);

  str = "abb";

  for (Word::iterator i = str.begin(); i != str.end(); i++)
    cout << *i << " ";
  cout << endl;

  str.mirror();

  for (Word::iterator i = str.begin(); i != str.end(); i++)
    cout << *i << " ";
  cout << endl;

  for (Word::reverse_iterator i = str.rbegin(); i != str.rend(); i++)
    cout << *i << " ";
  cout << endl;


  string comp = "cdeabbr";
  string::const_iterator i = comp.begin();
  
  parse_word(str, comp, i);

  cout << str << endl;
  
  i = find(comp.begin(), comp.end(), 'a');
  parse_word(str, comp, i);
  
  cout << str << endl;
  
  //======================================//

  Word str1(free_monoid, "abb");
  Word str2(free_monoid, string("bab"));

  str1 *= str1.set().identity(SELECT(string));

  for (Word::iterator i = str1.begin(); i != str1.end(); i++)
    cout << *i << " ";
  cout << endl;
  
  str1 *= str2;

  for (Word::iterator i = str1.begin(); i != str1.end(); i++)
    cout << *i << " ";
  cout << endl;

  return 0;
}
