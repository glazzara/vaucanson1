// random.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/misc/random.hh>
#include <cassert>
#include <climits>
#include <iostream>

#define MAXITER 1000

int main()
{
#define TEST_TYPE(Type, MAX)					\
  for (int i = 0; i < MAXITER; ++i)				\
    {								\
      Type c = utility::random::generate< Type >();		\
      Type min = utility::random::generate< Type >(0, MAX);	\
      Type max = utility::random::generate< Type >(min, MAX);	\
      c = utility::random::generate< Type >(min, max);		\
      if (!(min <= c && max >= c)) \
      { \
  std::cerr << "random failed: min = " << min \
            << ", max = " << max \
            << ", val = " << c << std::endl; \
        exit(1); \
      } \
    }
  TEST_TYPE(char, CHAR_MAX);
  TEST_TYPE(int, INT_MAX);
  for (int i = 0; i < MAXITER; ++i)
    {
      bool b = utility::random::generate<bool>();
      assert(b || !b);
    }
  for (int i = 0; i < MAXITER; ++i)
    {
      float f = utility::random::generate<float>();
      assert(f >= 0. && f <= 1.);
    }
}

