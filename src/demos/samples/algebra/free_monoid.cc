// free_monoid.cc
//
// $Id$

#include <iostream>
#include <string>
#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>

using namespace vcsn;
using namespace vcsn::algebra;

template <class Self>
unsigned free_monoid_alphabet_cardinal(const FreeMonoidBase<Self>& fm)
{
  return fm.alphabet().size();
}


int main()
{
  using namespace small_alpha_letter;
  Alphabet alphabet;
  alphabet.insert('a');
  alphabet.insert('b');
  FreeMonoid<Alphabet> free_monoid(alphabet);
  std::cout << free_monoid_alphabet_cardinal(free_monoid) << std::endl;
  return 0;
}
