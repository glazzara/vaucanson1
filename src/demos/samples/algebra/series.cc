//
//
// series.cc

#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
#include <vaucanson/algebra/concrete/series/series.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>


int main()
{
  using namespace vcsn;
  using namespace algebra;
  using namespace char_letter;

  using std::cout;
  using std::endl;

  Alphabet a;

  a.insert('a');
  a.insert('b');
  
  Words free_monoid(a);

  Word fm = "abb";

  NumericalSemiring ring;

  typedef Series<NumericalSemiring, Words> Series_t;
  typedef int scalar;

  Series_t s(ring, free_monoid);

  Element<Series_t, polynom<Word::value_t, scalar> > p1;
  
  p1.value_set("a", 1);
  p1.value_set("b", 2);
  p1.value_set("ab", 3);
  p1.value_set("ba", 4);
  
  cout << p1.value().size() << endl;

  Word str(free_monoid, "a");
  Element<NumericalSemiring, int> e_semiring = 5;

  p1.assoc(str, e_semiring);
  
  cout << p1.value().size() << endl;

  scalar i = p1.value_get("c");
  cout << i << endl;

  i = p1.value_get("ab");
  cout << i << endl;


  str = "ab";
  e_semiring = p1.get(str);
  cout << e_semiring.value() << endl;


  for (polynom<Word::value_t, scalar>::iterator i = p1.value().begin(); 
       i != p1.value().end(); i++)
    cout << i->first << " " << i->second << endl;

  endl(cout);
  
  p1.transpose();

  for (polynom<Word::value_t, scalar>::iterator i = p1.value().begin(); 
       i != p1.value().end(); i++)
    cout << i->first << " " << i->second << endl;

  cout << endl;

  
  Element<Series_t, polynom<Word::value_t, scalar> > p2, p3, tmp;

  p2.value_set("a", -4);
  p2.value_set("b", -1);

  tmp = p2 + p1;
  
  for (polynom<Word::value_t, scalar>::iterator i = tmp.value().begin(); 
       i != tmp.value().end(); i++)
    cout << i->first << " " << i->second << endl;
  
  cout << endl;

  p3.value_set("", -1);

  cout << p3.value().size() << endl;

  tmp = p3 * p1;

  for (polynom<Word::value_t, scalar>::iterator i = tmp.value().begin(); 
       i != tmp.value().end(); i++)
    cout << i->first << " " << i->second << endl;
  
  cout << endl;

  return 0;
}
