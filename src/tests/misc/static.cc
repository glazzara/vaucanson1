// static.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/config/system.hh>
#include <vaucanson/misc/static.hh>
#include <cassert>

using namespace utility;

void xassert(bool b)
{
  assert(b == true);
}

struct v {};

int main()
{
  int a = -1;
  const int b = -2;
  remove_reference<int>::t x = 0;
  remove_reference<int&>::t y = 1;
  xassert(remove_reference<const int&>::t(2) == 2);

  xassert(static_if<false, int, int>::choose(x, y) == y);
  xassert(static_if<true, int, int>::choose(x, y) == x);
  xassert(static_if<false, int, int>::choose(a, b) == b);
  xassert(static_if<false, int, int>::choose(a, x) == x);
  
  xassert(static_if<true, int, v>::t(3) == 3);
  xassert(static_if<false, v, int>::t(4) == 4);

  xassert(static_eq<int, int>::value);
  xassert(! static_eq<int, v>::value);

  xassert(static_pow<0, 10>::value == 0);
  xassert(static_pow<1, 10>::value == 1);
  xassert(static_pow<2, 16>::value == 1 << 16);
  xassert(static_pow<3, 3>::value == 27);

  xassert(static_pow_minus_one<1, 10>::value == 0);
  xassert(static_pow_minus_one<2, 16>::value == (1 << 16) - 1);
  xassert(static_pow_minus_one<3, 3>::value == 26);

  return 0;
}

