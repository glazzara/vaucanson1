// unique.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/misc/unique.hh>
#include <cassert>
#include <set>
#include <string>

#define MAXITER 10000

struct I : public utility::unique::unifiable
{
  I(int x) : x_(x) {}

  int x_;
};
bool operator==(const I& i1, const I& i2)
{ return i1.x_ == i2.x_; }

struct A : public utility::unique::unifiable 
{ };

std::string tag;
bool operator==(const A&, const A&)
{
  tag += "A";
  return true;
}

int main()
{
  std::set<const I*> s;
  
  for (int i = 0; i < MAXITER; ++i)
    {
      const I *p = & utility::unique::get(I(i));
      assert(s.find(p) == s.end());
      s.insert(p);
    }

  const A *p1 = & utility::unique::get(A());
  const A *p2 = & utility::unique::get(A());
  const A *p3 = & utility::unique::get(A());
  assert(tag.size() != 0);
  assert(p1 == p2 && p2 == p3);
  return 0;
}

