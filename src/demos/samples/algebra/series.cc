// series.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#include <vaucanson/algebra/implementation/free_monoid/predefs.hh>
#include <vaucanson/algebra/implementation/semiring/numerical_semiring.hh>
#include <vaucanson/algebra/implementation/series/series.hh>
#include <vaucanson/algebra/implementation/series/polynoms.hh>


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
  
  p1.value_structure("a", 1);
  p1.value_structure("b", 2);
  p1.value_structure("ab", 3);
  p1.value_structure("ba", 4);
  
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

  // FIXME: This is borken.
  /* p1.transpose(); */

  for (polynom<Word::value_t, scalar>::iterator i = p1.value().begin(); 
       i != p1.value().end(); i++)
    cout << i->first << " " << i->second << endl;

  cout << endl;

  
  Element<Series_t, polynom<Word::value_t, scalar> > p2, p3, tmp;

  p2.value_structure("a", -4);
  p2.value_structure("b", -1);

  tmp = p2 + p1;
  
  for (polynom<Word::value_t, scalar>::iterator i = tmp.value().begin(); 
       i != tmp.value().end(); i++)
    cout << i->first << " " << i->second << endl;
  
  cout << endl;

  p3.value_structure("", -1);

  cout << p3.value().size() << endl;

  tmp = p3 * p1;

  for (polynom<Word::value_t, scalar>::iterator i = tmp.value().begin(); 
       i != tmp.value().end(); i++)
    cout << i->first << " " << i->second << endl;
  
  cout << endl;

  return 0;
}

