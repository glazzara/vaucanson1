// limits.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/misc/limits.hh>
#include "check/tester.hh"

#define NATTR(Attr)  \
std::cout << #Attr "\t:" << utility::limits<T>::Attr << std::endl

template<typename T>
void test_limits()
{
  TEST_GROUP(std::string("numeric limits for ") + typeid(T).name());
  NATTR(digits);
  NATTR(digits10);
  NATTR(is_specialized);
  NATTR(min());
  NATTR(max());
  NATTR(has_infinity);
  NATTR(has_quiet_NaN);
  NATTR(is_signed);
  NATTR(is_integer);
  NATTR(is_exact);
  NATTR(radix);
  NATTR(is_iec559);
  NATTR(is_bounded);
  NATTR(is_modulo);
}

int main()
{
  test_limits<bool>();
  test_limits<signed char>();
  test_limits<unsigned char>();
  test_limits<int>();
  test_limits<unsigned int>();
  test_limits<float>();
}

