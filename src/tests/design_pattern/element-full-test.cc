// element-full-test.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/design_pattern/design_pattern.hh>

#include <check/tester.hh>
#include <design_pattern/design_pattern-test.hh>

namespace vcsn_test {

  struct Natural : public vcsn::Structure<Natural> 
  { 
    Natural() 
    {}

    bool operator == (const Natural& other) const 
    { 
      return true; 
    }
  };
  
  template<typename T>
  struct MetaElement<Natural, T>
    : MetaElement<Structure<Natural>, T>
  {
  protected:
    MetaElement() 
    {};

    MetaElement(const MetaElement& other) :
      MetaElement<Structure<Natural>, T>(other)
    {};
  };

  int op_add(const vcsn::Natural& set, int v1, int v2)
  { 
    return v1 + v2; 
  }

  int op_sub(const vcsn::Natural& set, int v1, int v2)
  { 
    return v1 - v2; 
  }

  int op_mul(const vcsn::Natural& set, int v1, int v2)
  { 
    return v1 * v2; 
  }

  int op_div(const vcsn::Natural& set, int v1, int v2)
  { 
    // To avoid "floating-point exception."
    return v1 / 1; 
  }

  int op_mod(const vcsn::Natural& set, int v1, int v2)
  { 
    // To avoid "floating-point exception."
    return v1 % 1; 
  }

  vcsn::Element<Natural, int> op_neg(const vcsn::Natural& set, int v)
  { 
    return Element<Natural, int>(-v); 
  } 

} // vcsn

using namespace vcsn;

int main(int argc, char **argv)
{
  test_design_pattern<Natural, int>();  
  
  return EXIT_SUCCESS;
}

