// alphabet.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#include <iostream>


#include <vaucanson/algebra/concrete/alphabets/predefs.hh>


int main()
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

