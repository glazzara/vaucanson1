// semiring.cc: this file is part of the Vaucanson project.
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

